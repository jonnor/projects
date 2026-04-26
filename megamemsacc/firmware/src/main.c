/*
 * Capacitive Comb Accelerometer — Synchronized Differential Drive
 * Seeed XIAO nRF52840 — Zephyr RTOS
 *
 * Signal chain:
 *   PWM0 CH0 (D0, P0.02) → excitation +   10 kHz, 50% duty
 *   PWM0 CH1 (D1, P0.03) → excitation −   10 kHz, inverted
 *   SAADC AIN4 (A2, P0.28) ← proof mass TIA output (biased to 1.65V)
 *   D9 (P0.29) → debug strobe
 *
 * Sampling: nrfx SAADC + PPI + TIMER1
 *   TIMER1 compare → PPI → SAADC sample trigger → EasyDMA buffer
 *   SAADC DONE event → saadc_event_handler ISR
 *   Double buffering: DMA fills buf[0] while CPU processes buf[1] and vice versa
 *   Zero CPU involvement in sampling — no k_timer, no blocking adc_read()
 *
 * Demodulation: software lock-in amplifier in SAADC ISR
 *   Multiply each sample by ±1 reference locked to excitation phase
 *   Accumulate DECIMATE_BY samples → post average to main at OUTPUT_HZ
 *
 * Main loop: IIR low-pass filter + UART print at 10 Hz
 *
 * Fixes applied vs original:
 *   1. nrfx_saadc_start() called after mode_trigger() so SAADC is running
 *      before the first PPI-triggered TASKS_SAMPLE arrives.
 *   2. PPI task address uses nrfx_saadc_sample_task_get() instead of a raw
 *      &NRF_SAADC->TASKS_SAMPLE dereference (same address, but portable and
 *      guaranteed correct by the driver).
 *   3. BUF_REQ handler: buf_idx is toggled BEFORE calling buffer_set so DMA
 *      always receives the idle buffer, not the one about to be processed.
 *   4. DONE handler: reads from saadc_buf[buf_idx ^ 1] — the buffer that DMA
 *      just finished — not the one now being filled.
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include <nrfx_saadc.h>
#include <nrfx_timer.h>
#include <helpers/nrfx_gppi.h>
#if defined(DPPI_PRESENT)
#include <nrfx_dppi.h>
#else
#include <nrfx_ppi.h>
#endif

LOG_MODULE_REGISTER(comb_readout, LOG_LEVEL_INF);

/* ── Parameters ──────────────────────────────────────────────────────────────*/
#define EXCITATION_HZ    10000U
#define OVERSAMPLE       4U
#define SAMPLE_HZ        (EXCITATION_HZ * OVERSAMPLE)  /* 40 kHz            */
#define OUTPUT_HZ        200U
#define DECIMATE_BY      (SAMPLE_HZ / OUTPUT_HZ)       /* 200               */

/* nRF52840 SAADC with gain 1/6, internal ref (0.6V):
 * full-scale input = 0.6 / (1/6) = 3.6V → 12-bit = 4096 counts
 * Vbias = 1.65V → ADC_MID ≈ 1.65 / 3.6 * 4096 ≈ 1878
 * Use 2048 as approximation; calibrate if needed.                        */
#define ADC_MID          2048

/* IIR α for 32 Hz cutoff at 200 Hz: 1 − e^(−2π·32/200) ≈ 0.632          */
#define IIR_ALPHA        0.632f

/* ── PWM pins ────────────────────────────────────────────────────────────────*/
#define PWM_CH_POS       0U   /* P0.02 = D0 */
#define PWM_CH_NEG       1U   /* P0.03 = D1 */

/* ── Debug pin ───────────────────────────────────────────────────────────────*/
#define DEBUG_PIN        29U  /* P0.29 = D9 */
static const struct device *debug_gpio_dev;

/* ── SAADC / TIMER instances ─────────────────────────────────────────────────*/
/* TIMER1: used for SAADC triggering via PPI.
 * TIMER0 is reserved by Zephyr kernel. TIMER2 may conflict with PWM.     */
#define TIMER_INST_IDX   1
static const nrfx_timer_t timer_inst = NRFX_TIMER_INSTANCE(TIMER_INST_IDX);

/* Double buffering: DMA fills one buffer while ISR processes the other.
 * Must be > 1: with DMA_BUF_SIZE=1 at 40 kHz the BUF_REQ ISR fires every
 * 25 µs — too fast for reliable buffer handoff. 8 samples = 200 µs slack. */
#define DMA_BUF_SIZE     8
static int16_t saadc_buf[2][DMA_BUF_SIZE];
static uint8_t buf_idx = 0;

/* ── Demodulator state (ISR only) ────────────────────────────────────────────*/
static volatile uint8_t phase = 0;

/* ── Message queue: ISR → main ───────────────────────────────────────────────*/
K_MSGQ_DEFINE(raw_msgq, sizeof(int32_t), 16, 4);

/* ── SAADC event handler (ISR context) ───────────────────────────────────────
 *
 * Called by nrfx_saadc on two events:
 *   NRFX_SAADC_EVT_DONE    — buffer full, p_buffer contains fresh samples
 *   NRFX_SAADC_EVT_BUF_REQ — new buffer needed; assign idle buffer to DMA
 *
 * Architecture:
 *   Excitation (D0):  ___     ___
 *                    |   |   |   |
 *                 ___|   |___|   |___   10 kHz
 *   Excitation (D1): ‾‾‾|___|‾‾‾       (inverted)
 *
 *   Samples:   ^  ^  ^  ^              40 kHz, 4 per cycle
 *   phase:     0  1  2  3
 *   ref:      +1 +1 -1 -1             locked to excitation
 *
 *   At rest:     net sum → 0
 *   Displaced:   net sum → DC ∝ displacement
 *   Noise/EMI:   averages to zero (lock-in rejection)
 */
static void saadc_event_handler(nrfx_saadc_evt_t const *p_event)
{
    switch (p_event->type) {

    case NRFX_SAADC_EVT_BUF_REQ:
        /* FIX 3: Toggle buf_idx FIRST so DMA receives the truly idle buffer.
         * Original code set the buffer then toggled — DMA got the buffer
         * that DONE was about to read, causing a data race.               */
        buf_idx ^= 1;
        nrfx_saadc_buffer_set(saadc_buf[buf_idx], DMA_BUF_SIZE);
        break;

    case NRFX_SAADC_EVT_DONE: {
        /* FIX 4: Read from buf_idx ^ 1 — the buffer DMA just completed.
         * Loop over all DMA_BUF_SIZE samples; demodulate each one.        */
        int16_t *done_buf = saadc_buf[buf_idx ^ 1];

        static int32_t  accum = 0;
        static uint32_t count = 0;

        for (int i = 0; i < DMA_BUF_SIZE; i++) {
            int32_t adc = (int32_t)done_buf[i] - ADC_MID;
            int8_t  ref = (phase < (OVERSAMPLE / 2U)) ? 1 : -1;
            phase = (phase + 1U) % OVERSAMPLE;

            accum += adc * ref;
            if (++count >= DECIMATE_BY) {
                int32_t avg = accum / (int32_t)DECIMATE_BY;
                accum = 0;
                count = 0;
                k_msgq_put(&raw_msgq, &avg, K_NO_WAIT);
            }
        }
        break;
    }

    default:
        LOG_DBG("SAADC evt type=%d", p_event->type);
        break;
    }
}

/* ── SAADC + TIMER + PPI init ────────────────────────────────────────────────*/
static int saadc_dma_init(void)
{
    nrfx_err_t err;

    /* Connect SAADC IRQ — must be done before nrfx_saadc_init */
    IRQ_CONNECT(DT_IRQN(DT_NODELABEL(adc)),
                DT_IRQ(DT_NODELABEL(adc), priority),
                nrfx_isr, nrfx_saadc_irq_handler, 0);
    irq_enable(DT_IRQN(DT_NODELABEL(adc)));

    /* start_on_end=true: SAADC automatically re-arms after each conversion.
     * Combined with PPI triggering, this gives gapless continuous sampling. */
    nrfx_saadc_adv_config_t adv_cfg = {
        .oversampling      = NRF_SAADC_OVERSAMPLE_DISABLED,
        .burst             = NRF_SAADC_BURST_DISABLED,
        .internal_timer_cc = 0,
        .start_on_end      = true,
    };
    err = nrfx_saadc_init(DT_IRQ(DT_NODELABEL(adc), priority));
    if (err != NRFX_SUCCESS) {
        LOG_ERR("nrfx_saadc_init: 0x%08x", err);
        return -EIO;
    }

    /* Configure channel: AIN4 = P0.28 = XIAO A2, single-ended */
    nrfx_saadc_channel_t channel =
        NRFX_SAADC_DEFAULT_CHANNEL_SE(NRF_SAADC_INPUT_AIN4, 0);
    channel.channel_config.gain      = NRF_SAADC_GAIN1_6;
    channel.channel_config.reference = NRF_SAADC_REFERENCE_INTERNAL;
    channel.channel_config.acq_time  = NRF_SAADC_ACQTIME_3US;
    err = nrfx_saadc_channels_config(&channel, 1);
    if (err != NRFX_SUCCESS) {
        LOG_ERR("nrfx_saadc_channels_config: 0x%08x", err);
        return -EIO;
    }

    /* Advanced mode: non-blocking, hardware-triggered via PPI */
    err = nrfx_saadc_advanced_mode_set(
        BIT(0),                      /* channel mask */
        NRF_SAADC_RESOLUTION_12BIT,
        &adv_cfg,
        saadc_event_handler);
    if (err != NRFX_SUCCESS) {
        LOG_ERR("nrfx_saadc_advanced_mode_set: 0x%08x", err);
        return -EIO;
    }

    /* Pre-queue BOTH buffers before mode_trigger so the SAADC never stalls
     * waiting for a buffer during the initial BUF_REQ that fires immediately
     * inside mode_trigger(). buf_idx starts at 0; BUF_REQ will flip it to 1
     * and assign buf[1], so DMA starts on buf[0] and the first DONE delivers
     * buf[0] while buf[1] is already queued.                               */
    err = nrfx_saadc_buffer_set(saadc_buf[0], DMA_BUF_SIZE);
    if (err != NRFX_SUCCESS) { LOG_ERR("buffer_set[0]: 0x%08x", err); return -EIO; }
    err = nrfx_saadc_buffer_set(saadc_buf[1], DMA_BUF_SIZE);
    if (err != NRFX_SUCCESS) { LOG_ERR("buffer_set[1]: 0x%08x", err); return -EIO; }

    /* Arm SAADC — transitions it to the SAMPLE state, ready for triggers */
    err = nrfx_saadc_mode_trigger();
    if (err != NRFX_SUCCESS) {
        LOG_ERR("mode_trigger: 0x%08x", err);
        return -EIO;
    }
    LOG_INF("SAADC mode_trigger OK");

    /* FIX 1: Start the SAADC peripheral so it accepts TASKS_SAMPLE from PPI.
     * Without this, PPI fires TASKS_SAMPLE but the SAADC is not running and
     * silently ignores every trigger — nothing ever appears in the buffers.
     * nrfx_saadc_start() does not exist in this nrfx version — write the
     * register directly.                                                    */
    NRF_SAADC->TASKS_START = 1;
    LOG_INF("SAADC started");

    /* ── TIMER1: fires at SAMPLE_HZ, triggers SAADC via PPI ─────────────── */
    IRQ_CONNECT(NRFX_IRQ_NUMBER_GET(NRF_TIMER1),
                DT_IRQ(DT_NODELABEL(adc), priority),
                nrfx_isr, nrfx_timer_1_irq_handler, 0);
    irq_enable(NRFX_IRQ_NUMBER_GET(NRF_TIMER1));

    nrfx_timer_config_t timer_cfg = {
        .frequency          = 1000000UL,   /* 1 MHz → 1 µs resolution */
        .mode               = NRF_TIMER_MODE_TIMER,
        .bit_width          = NRF_TIMER_BIT_WIDTH_32,
        .interrupt_priority = DT_IRQ(DT_NODELABEL(adc), priority),
        .p_context          = NULL,
    };
    err = nrfx_timer_init(&timer_inst, &timer_cfg, NULL);  /* no CPU callback */
    if (err != NRFX_SUCCESS) { LOG_ERR("timer_init: 0x%08x", err); return -EIO; }

    uint32_t ticks = nrfx_timer_us_to_ticks(&timer_inst, 1000000U / SAMPLE_HZ);
    nrfx_timer_extended_compare(&timer_inst,
                                NRF_TIMER_CC_CHANNEL0,
                                ticks,
                                NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
                                false);  /* no CPU interrupt — PPI only */

    /* ── PPI: connect TIMER compare event → SAADC sample task ──────────── */
    uint8_t ppi_channel;
    err = nrfx_gppi_channel_alloc(&ppi_channel);
    if (err != NRFX_SUCCESS) { LOG_ERR("ppi_alloc: 0x%08x", err); return -EIO; }

    uint32_t evt_addr  = nrfx_timer_compare_event_address_get(&timer_inst,
                                                               NRF_TIMER_CC_CHANNEL0);

    /* FIX 2: Use the register address directly — nrfx_saadc_sample_task_get()
     * does not exist in this nrfx version. Cast to uint32_t (not a pointer
     * dereference) so PPI gets the address of the task register, not its
     * contents.                                                             */
    uint32_t task_addr = (uint32_t)&NRF_SAADC->TASKS_SAMPLE;

    LOG_INF("PPI ch %u: event=0x%08x task=0x%08x", ppi_channel, evt_addr, task_addr);

    nrfx_gppi_channel_endpoints_setup(ppi_channel, evt_addr, task_addr);
    nrfx_gppi_channels_enable(BIT(ppi_channel));

    /* Start timer — SAADC now samples autonomously at SAMPLE_HZ */
    nrfx_timer_enable(&timer_inst);

    LOG_INF("SAADC DMA started: %u Hz sample rate", SAMPLE_HZ);
    return 0;
}

/* ── PWM complementary excitation ────────────────────────────────────────────*/
static int pwm_excitation_init(void)
{
    const struct device *pwm_dev = DEVICE_DT_GET(DT_NODELABEL(pwm0));
    if (!device_is_ready(pwm_dev)) {
        LOG_ERR("PWM not ready");
        return -ENODEV;
    }

    const uint32_t period_ns = NSEC_PER_SEC / EXCITATION_HZ;
    const uint32_t pulse_ns  = period_ns / 2U;

    int ret = pwm_set(pwm_dev, PWM_CH_POS, period_ns, pulse_ns,
                      PWM_POLARITY_NORMAL);
    if (ret < 0) { LOG_ERR("PWM CH0: %d", ret); return ret; }

    ret = pwm_set(pwm_dev, PWM_CH_NEG, period_ns, pulse_ns,
                  PWM_POLARITY_INVERTED);
    if (ret < 0) { LOG_ERR("PWM CH1: %d", ret); return ret; }

    LOG_INF("PWM excitation: %u Hz differential", EXCITATION_HZ);
    return 0;
}

/* ── Main ────────────────────────────────────────────────────────────────────*/
int main(void)
{
    /* Debug GPIO */
    debug_gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));
    if (!device_is_ready(debug_gpio_dev)) {
        LOG_ERR("GPIO not ready");
        return -ENODEV;
    }
    gpio_pin_configure(debug_gpio_dev, DEBUG_PIN, GPIO_OUTPUT_INACTIVE);

    /* PWM excitation */
    if (pwm_excitation_init() < 0) return -EIO;

    /* SAADC + TIMER + PPI */
    if (saadc_dma_init() < 0) return -EIO;

    LOG_INF("Comb readout started — %u Hz excitation, %u Hz output, 32 Hz LPF",
            EXCITATION_HZ, OUTPUT_HZ);

    /* ── Main loop: IIR + print ──────────────────────────────────────────────*/
    float    iir_state   = 0.0f;
    uint32_t print_count = 0;

    while (1) {
        int32_t raw;
        if (k_msgq_get(&raw_msgq, &raw, K_SECONDS(2)) != 0) {
            LOG_ERR("No samples — SAADC/TIMER/PPI not running");
            continue;
        }

        /* IIR low-pass: α=0.632 → 32 Hz cutoff at 200 Hz */
        iir_state += IIR_ALPHA * ((float)raw - iir_state);

        /* Print at 10 Hz (every 20th sample at 200 Hz) */
        if (++print_count >= 20U) {
            print_count = 0;
            printk("filtered: %.2f\n", (double)iir_state);
        }
    }

    return 0;
}
