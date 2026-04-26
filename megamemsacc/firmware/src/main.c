/*
 * Capacitive Comb Accelerometer — Synchronized Differential Drive
 * Seeed XIAO nRF52840 — Zephyr RTOS
 *
 * Signal chain:
 *   PWM0 CH0 (D0, P0.02) → excitation +   10 kHz, 50% duty
 *   PWM0 CH1 (D1, P0.03) → excitation −   10 kHz, inverted (PWM_POLARITY_INVERTED)
 *   ADC SAADC AIN4 (A2, P0.28) ← proof mass TIA output (biased to Vdd/2 = 1.65V)
 *   D9 (P0.29) → debug strobe, pulses HIGH around each ADC sample
 *
 * Two PWM channels on the same PWM peripheral share the same counter,
 * so CH0 and CH1 are inherently phase-locked — equivalent to complementary
 * outputs on STM32, achieved here via PWM_POLARITY_INVERTED on CH1.
 *
 * Sampling: k_timer fires at 40 kHz (OVERSAMPLE=4 × 10 kHz excitation)
 * Each ISR callback demodulates and decimates to 200 Hz via accumulation.
 * Main loop runs IIR low-pass at 200 Hz, prints at 10 Hz.
 *
 * TIA (TL072):
 *   Proof mass → TIA input, feedback 1MΩ || 10pF
 *   Virtual ground at 1.65V (10kΩ/10kΩ divider from 3.3V)
 *   TIA output biased to 1.65V at rest → stays within 0–3.3V ADC range
 *
 * Wiring:
 *   D0 (P0.02) ──[100Ω]──> comb fingers set A  (excitation +)
 *   D1 (P0.03) ──[100Ω]──> comb fingers set B  (excitation −)
 *   A2 (P0.04) <── TIA output (proof mass)
 *   D9 (P0.29)  ──> scope CH2 (ADC strobe)
 *   Scope CH1   ──> D0 (excitation +)
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(comb_readout, LOG_LEVEL_INF);

/* ── Parameters ──────────────────────────────────────────────────────────────*/
#define EXCITATION_HZ   2000U
#define OVERSAMPLE      4U
#define SAMPLE_HZ       (EXCITATION_HZ * OVERSAMPLE)   /* 40 kHz            */
#define OUTPUT_HZ       200U
#define DECIMATE_BY     (SAMPLE_HZ / OUTPUT_HZ)        /* 200 counts        */

/* nRF52840 SAADC is 12-bit, VDD reference (3.3V), midpoint = 2048 */
#define ADC_MID         2048

/* IIR α for 32 Hz cutoff at 200 Hz: α = 1 − e^(−2π·32/200) ≈ 0.632 */
#define IIR_ALPHA       0.632f

/* ── Devicetree bindings ─────────────────────────────────────────────────────*/
/*
 * Access pwm0 directly as a device. Both excitation channels are on
 * pwm0, sharing one hardware counter — guaranteed phase-locked.
 * CH0 (P0.02 = D0): normal polarity  → excitation +
 * CH1 (P0.03 = D1): inverted polarity → excitation − (exact antiphase)
 */
#define PWM_NODE        DT_NODELABEL(pwm0)
#define PWM_CH_POS      0U                      /* CH0 → P0.02 = D0 */
#define PWM_CH_NEG      1U                      /* CH1 → P0.03 = D1 */

/* ADC: SAADC channel 4 on AIN4 (P0.28 = A2 on XIAO) */
#define ADC_NODE        DT_NODELABEL(adc)
#define ADC_CHANNEL     4               /* AIN4 = P0.28 = XIAO A2          */
#define ADC_RESOLUTION  12

static const struct device *adc_dev;

static const struct adc_channel_cfg adc_ch_cfg = {
    .gain             = ADC_GAIN_1_6,   /* nRF SAADC: gain 1/6, ref VDD/6   */
    .reference        = ADC_REF_INTERNAL,
    .acquisition_time = ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 10),
    .channel_id       = ADC_CHANNEL,
    .input_positive   = SAADC_CH_PSELP_PSELP_AnalogInput4,
};

static int16_t adc_buf;
static struct adc_sequence adc_seq = {
    .channels    = BIT(ADC_CHANNEL),
    .buffer      = &adc_buf,
    .buffer_size = sizeof(adc_buf),
    .resolution  = ADC_RESOLUTION,
};

/* ── Debug strobe pin ────────────────────────────────────────────────────────
 * D9 = P0.29 on XIAO nRF52840. Pulses HIGH for the duration of adc_read().
 * Access gpio0 directly — it is always present on nRF52840 and does not
 * Pin 29 = P0.29.
 * Probe on scope CH2 alongside CH1 (D0 excitation) to verify phase alignment.
 * Expected: 4 evenly spaced pulses per 10 kHz excitation cycle, fixed offset. */
#define DEBUG_GPIO_NODE  DT_NODELABEL(gpio0)
#define DEBUG_PIN        29U

/* ── Message queue: ISR → main loop ─────────────────────────────────────────
 * Decimated demodulated samples at 200 Hz.
 * Depth 16 = 80 ms headroom if main loop is briefly delayed.             */

/* ── Debug GPIO device pointer (set in main before timer starts) ─────────────*/
static const struct device *debug_gpio_dev;
static uint8_t phase = 0;

/* ── Sampling semaphore — timer signals, main thread reads ADC ───────────────
 *
 * adc_read() on nRF52840 SAADC uses k_sem internally and must run in a
 * thread context, not a work queue callback. The k_timer callback only
 * gives a semaphore; all ADC work happens in main().
 *
 * Demodulation principle (software lock-in amplifier):
 *
 *   Excitation (D0):  ___     ___     ___
 *                    |   |   |   |   |   |
 *                 ___|   |___|   |___|   |___   10 kHz
 *
 *   Excitation (D1): ‾‾‾|___|‾‾‾|___|‾‾‾      (inverted, PWM CH1)
 *
 *   ADC samples:   ^  ^  ^  ^                  4 per excitation cycle
 *   phase:         0  1  2  3
 *   ref (×±1):    +1 +1 -1 -1                  locked to excitation
 */
K_SEM_DEFINE(sample_sem, 0, 1);

static void sampling_timer_cb(struct k_timer *timer)
{
    /* Signal main thread to take an ADC sample — never block */
    k_sem_give(&sample_sem);
}

K_TIMER_DEFINE(sampling_timer, sampling_timer_cb, NULL);

/* ── Main ────────────────────────────────────────────────────────────────────*/
int main(void)
{
    /* ── Hardware UART console — no init needed, Zephyr handles it ──────────*/
    int ret;

    /* ── ADC init ────────────────────────────────────────────────────────────*/
    adc_dev = DEVICE_DT_GET(ADC_NODE);
    if (!device_is_ready(adc_dev)) {
        LOG_ERR("ADC not ready");
        return -ENODEV;
    }
    ret = adc_channel_setup(adc_dev, &adc_ch_cfg);
    if (ret < 0) {
        LOG_ERR("ADC channel setup failed: %d", ret);
        return ret;
    }

    const struct device *debug_gpio = DEVICE_DT_GET(DT_NODELABEL(gpio0));
    if (!device_is_ready(debug_gpio)) {
        LOG_ERR("GPIO not ready");
        return -ENODEV;
    }
    gpio_pin_configure(debug_gpio, DEBUG_PIN, GPIO_OUTPUT_INACTIVE);
    debug_gpio_dev = debug_gpio;  /* make available to ISR */

    /* ── PWM excitation ──────────────────────────────────────────────────────
     * Both channels on pwm0 share one counter — hardware phase-locked.
     * CH1 PWM_POLARITY_INVERTED gives exact antiphase with zero skew.
     *
     * Period = 1,000,000,000 ns / 10,000 Hz = 100,000 ns
     * Pulse  = 50,000 ns (50% duty)                                      */
    const struct device *pwm_dev = DEVICE_DT_GET(DT_NODELABEL(pwm0));
    if (!device_is_ready(pwm_dev)) {
        LOG_ERR("PWM device not ready");
        return -ENODEV;
    }

    const uint32_t period_ns = NSEC_PER_SEC / EXCITATION_HZ;
    const uint32_t pulse_ns  = period_ns / 2U;

    /* CH0: excitation + (normal polarity) */
    ret = pwm_set(pwm_dev, PWM_CH_POS, period_ns, pulse_ns,
                  PWM_POLARITY_NORMAL);
    if (ret < 0) { LOG_ERR("PWM CH0 set failed: %d", ret); return ret; }

    /* CH1: excitation − (inverted = exact 180° antiphase) */
    ret = pwm_set(pwm_dev, PWM_CH_NEG, period_ns, pulse_ns,
                  PWM_POLARITY_INVERTED);
    if (ret < 0) { LOG_ERR("PWM CH1 set failed: %d", ret); return ret; }

    /* ── Start 40 kHz sampling timer ────────────────────────────────────────*/
    k_timer_start(&sampling_timer,
                  K_USEC(1000000U / SAMPLE_HZ),
                  K_USEC(1000000U / SAMPLE_HZ));

    LOG_INF("Comb readout started — 10 kHz excitation, 200 Hz output, 32 Hz LPF");

    /* ── Main loop: sample, demodulate, IIR filter, print ───────────────────*/
    float    iir_state   = 0.0f;
    uint32_t print_count = 0;
    int32_t  accum       = 0;
    uint32_t count       = 0;

    while (1) {
        /* Wait for timer signal — blocks until next 40 kHz tick */
        if (k_sem_take(&sample_sem, K_SECONDS(2)) != 0) {
            LOG_ERR("No timer signal — sampling timer not running");
            continue;
        }

        /* ADC read in thread context (required by nRF52840 SAADC driver) */
        gpio_pin_set(debug_gpio_dev, DEBUG_PIN, 1);
        adc_read(adc_dev, &adc_seq);
        gpio_pin_set(debug_gpio_dev, DEBUG_PIN, 0);
        int32_t adc = (int32_t)adc_buf - ADC_MID;

        /* Demodulate: multiply by reference square wave */
        int8_t ref = (phase < (OVERSAMPLE / 2U)) ? 1 : -1;
        phase = (phase + 1U) % OVERSAMPLE;

        /* Accumulate and decimate to OUTPUT_HZ */
        accum += adc * ref;
        if (++count >= DECIMATE_BY) {
            int32_t avg = accum / (int32_t)DECIMATE_BY;
            accum = 0;
            count = 0;

            /* IIR low-pass: α=0.632 → 32 Hz cutoff at 200 Hz */
            iir_state += IIR_ALPHA * ((float)avg - iir_state);

            if (++print_count >= 20U) {
                print_count = 0;
                printk("filtered: %.2f\n", (double)iir_state);
            }
        }
    }

    return 0;
}
