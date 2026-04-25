/*
 * Capacitive Comb Accelerometer — Synchronized Differential Drive
 * Seeed XIAO nRF52840 — Zephyr RTOS
 *
 * Signal chain:
 *   PWM0 CH0 (D0, P0.02) → excitation +   10 kHz, 50% duty
 *   PWM0 CH1 (D1, P0.03) → excitation −   10 kHz, inverted (PWM_POLARITY_INVERTED)
 *   ADC SAADC AIN2 (A2, P0.04) ← proof mass TIA output (biased to Vdd/2 = 1.65V)
 *   D3 (P0.28) → debug strobe, pulses HIGH around each ADC sample
 *
 * Two PWM channels on the same PWM peripheral share the same counter,
 * so CH0 and CH1 are inherently phase-locked — equivalent to complementary
 * outputs on STM32, achieved here via PWM_POLARITY_INVERTED on CH1.
 *
 * Sampling: k_timer fires at 40 kHz (OVERSAMPLE=4 × 10 kHz excitation).
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
 *   D3 (P0.28)  ──> scope CH2 (ADC strobe)
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
#define EXCITATION_HZ   10000U
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

/* ADC: SAADC channel 2 on AIN2 (P0.04 = A2 on XIAO) */
#define ADC_NODE        DT_NODELABEL(adc)
#define ADC_CHANNEL     2               /* AIN2 = P0.04 = XIAO A2           */
#define ADC_RESOLUTION  12

static const struct device *adc_dev;

static const struct adc_channel_cfg adc_ch_cfg = {
    .gain             = ADC_GAIN_1_6,   /* nRF SAADC: gain 1/6, ref VDD/6   */
    .reference        = ADC_REF_INTERNAL,
    .acquisition_time = ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 10),
    .channel_id       = ADC_CHANNEL,
    .input_positive   = SAADC_CH_PSELP_PSELP_AnalogInput2,
};

static int16_t adc_buf;
static struct adc_sequence adc_seq = {
    .channels    = BIT(ADC_CHANNEL),
    .buffer      = &adc_buf,
    .buffer_size = sizeof(adc_buf),
    .resolution  = ADC_RESOLUTION,
};

/* ── Debug strobe pin ────────────────────────────────────────────────────────
 * D3 = P0.28 on XIAO nRF52840. Pulses HIGH for the duration of adc_read().
 * Access gpio0 directly — it is always present on nRF52840 and does not
 * need a custom DTS node. Pin 28 = P0.28.
 * Probe on scope CH2 alongside CH1 (D0 excitation) to verify phase alignment.
 * Expected: 4 evenly spaced pulses per 10 kHz excitation cycle, fixed offset. */
#define DEBUG_GPIO_NODE  DT_NODELABEL(gpio0)
#define DEBUG_PIN        28U

/* ── Message queue: ISR → main loop ─────────────────────────────────────────
 * Decimated demodulated samples at 200 Hz.
 * Depth 16 = 80 ms headroom if main loop is briefly delayed.             */
K_MSGQ_DEFINE(raw_msgq, sizeof(int32_t), 16, 4);

/* ── Debug GPIO device pointer (set in main before timer starts) ─────────────*/
static const struct device *debug_gpio_dev;
static uint8_t phase = 0;

/* ── 40 kHz sampling timer ───────────────────────────────────────────────────
 *
 * k_timer fires every 25 µs. This is the sampling and demodulation engine.
 *
 * Demodulation principle (software lock-in amplifier):
 *
 *   Excitation (D0):  ___     ___     ___
 *                    |   |   |   |   |   |
 *                 ___|   |___|   |___|   |___   10 kHz
 *
 *   Excitation (D1):  ___     ___     ___        (exact inverse via PWM CH1)
 *                 ‾‾‾   ‾‾‾‾‾   ‾‾‾‾‾   ‾‾‾
 *
 *   ADC samples:   ^  ^  ^  ^  ^  ^  ^          40 kHz (4 per cycle)
 *   phase:         0  1  2  3  0  1  2  3
 *   ref (×±1):    +1 +1 -1 -1 +1 +1 -1 -1      locked to excitation
 *
 *   At rest (balanced):
 *     Proof mass sees equal charge from both comb sets → zero net current.
 *     TIA output = Vbias = 1.65V → ADC = 2048 → adc - ADC_MID = 0.
 *     Demodulated sum → 0.
 *
 *   Displaced (e.g. Cx+ > Cx−):
 *     More charge on positive half-cycle → TIA swings positive.
 *     Multiplying by ref makes both half-cycles contribute same sign.
 *     Accumulated sum → positive DC proportional to displacement.
 *
 *   Noise rejection:
 *     Any signal not phase-coherent with the 10 kHz reference averages
 *     to zero over the accumulation window. Mechanical vibration, 1/f
 *     noise, and EMI are all suppressed by this mechanism.
 *
 *   Decimation:
 *     DECIMATE_BY = 200 samples are accumulated then averaged, posting
 *     one value at 200 Hz. The averaging acts as a boxcar pre-filter
 *     before the IIR LPF in the main loop.
 */
static void sampling_timer_cb(struct k_timer *timer)
{
    /* Strobe debug pin HIGH: scope can now see exact ADC sample timing */
    gpio_pin_set(debug_gpio_dev, DEBUG_PIN, 1);

    /* Step 1: sample proof mass TIA output, remove DC bias */
    adc_read(adc_dev, &adc_seq);
    int32_t adc = (int32_t)adc_buf - ADC_MID;

    gpio_pin_set(debug_gpio_dev, DEBUG_PIN, 0);

    /* Step 2: multiply by reference square wave (demodulate).
     * phase 0,1 → excitation D0 is HIGH → reference = +1
     * phase 2,3 → excitation D0 is LOW  → reference = −1
     * The k_timer and PWM share the same Zephyr clock but are started
     * sequentially, so there is a small fixed phase offset. This is
     * constant across all samples and only affects overall scale, not
     * linearity. Adjust the OVERSAMPLE/2 boundary if polarity is inverted. */
    int8_t ref = (phase < (OVERSAMPLE / 2U)) ? 1 : -1;
    phase = (phase + 1U) % OVERSAMPLE;

    /* Step 3: accumulate demodulated samples */
    static int32_t  accum = 0;
    static uint32_t count = 0;

    accum += adc * ref;

    /* Step 4: decimate — post boxcar average at OUTPUT_HZ (200 Hz) */
    if (++count >= DECIMATE_BY) {
        int32_t avg = accum / (int32_t)DECIMATE_BY;
        accum = 0;
        count = 0;
        /* K_NO_WAIT: never block timer callback; drop if main loop is behind */
        k_msgq_put(&raw_msgq, &avg, K_NO_WAIT);
    }
}

K_TIMER_DEFINE(sampling_timer, sampling_timer_cb, NULL);

/* ── Main ────────────────────────────────────────────────────────────────────*/
int main(void)
{
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
                  K_USEC(1000000U / SAMPLE_HZ),    /* first fire: 25 µs    */
                  K_USEC(1000000U / SAMPLE_HZ));    /* period:     25 µs    */

    LOG_INF("Comb readout started — 10 kHz excitation, 200 Hz output, 32 Hz LPF");

    /* ── Main loop: IIR filter + print ──────────────────────────────────────*/
    float    iir_state   = 0.0f;
    uint32_t print_count = 0;

    while (1) {
        int32_t raw;
        /* Block until ISR posts a decimated sample (~every 5 ms at 200 Hz) */
        k_msgq_get(&raw_msgq, &raw, K_FOREVER);

        /* Single-pole IIR low-pass: y[n] = α·x[n] + (1−α)·y[n−1]
         * α = 0.632 → 32 Hz cutoff at 200 Hz sample rate.
         * Attenuates residual demodulation artefacts and mechanical
         * resonances above 32 Hz before output.                          */
        iir_state += IIR_ALPHA * ((float)raw - iir_state);

        /* Print at 10 Hz (every 20th sample at 200 Hz) */
        if (++print_count >= 20U) {
            print_count = 0;
            printk("filtered: %.2f\n", (double)iir_state);
        }
    }

    return 0;
}
