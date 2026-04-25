/*
 * Capacitive Comb Accelerometer — Synchronized Differential Drive
 * STM32F411 Black Pill — Zephyr RTOS
 *
 * TIM1 CH1/CH1N: complementary 10 kHz excitation (HAL direct)
 * TIM2:          40 kHz sampling interrupt (HAL direct)
 * ADC:           Zephyr ADC driver on PA0 (AIN0)
 *
 * Signal chain:
 *   TIM1 CH1/CH1N → differential 10 kHz square wave drives comb fingers
 *   Proof mass current → TIA → PA0 ADC
 *   TIM2 ISR @ 40 kHz:
 *     1. Sample ADC
 *     2. Multiply by reference square wave (lock-in demodulation)
 *     3. Accumulate + decimate to 200 Hz, post average to msgq
 *   Main loop @ 200 Hz:
 *     4. Single-pole IIR low-pass (32 Hz cutoff)
 *     5. Print at 10 Hz
 *
 * Wiring:
 *   PA8  → TIM1 CH1  → comb fingers set A (excitation +)
 *   PB13 → TIM1 CH1N → comb fingers set B (excitation −)
 *   PA0  → ADC IN0   ← proof mass TIA output (biased to 1.65V)
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/logging/log.h>

#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_tim.h>
#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_rcc.h>

LOG_MODULE_REGISTER(comb_readout, LOG_LEVEL_INF);

/* ── Parameters ──────────────────────────────────────────────────────────────*/
#define EXCITATION_HZ   10000U
#define OVERSAMPLE      4U
#define SAMPLE_HZ       (EXCITATION_HZ * OVERSAMPLE)   /* 40 kHz            */
#define OUTPUT_HZ       200U
#define DECIMATE_BY     (SAMPLE_HZ / OUTPUT_HZ)        /* 200 counts         */
#define ADC_MID         2048

/* IIR alpha for 32 Hz cutoff at 200 Hz sample rate:
 * α = 1 - e^(-2π·fc/fs) = 1 - e^(-2π·32/200) ≈ 0.632               */
#define IIR_ALPHA       0.632f

/* ── Message queue ───────────────────────────────────────────────────────────*/
/* ISR → main loop: decimated demodulated samples at 200 Hz
 * Depth 16: ~80 ms headroom if main loop is briefly busy              */
K_MSGQ_DEFINE(raw_msgq, sizeof(int32_t), 16, 4);

/* ── ADC ─────────────────────────────────────────────────────────────────────*/
#define ADC_NODE        DT_NODELABEL(adc1)
#define ADC_CHANNEL     0
#define ADC_RESOLUTION  12

static const struct device *adc_dev;

static const struct adc_channel_cfg adc_ch_cfg = {
    .gain             = ADC_GAIN_1,
    .reference        = ADC_REF_INTERNAL,
    .acquisition_time = ADC_ACQ_TIME_DEFAULT,
    .channel_id       = ADC_CHANNEL,
    .differential     = 0,
};

static int16_t adc_buf;
static struct adc_sequence adc_seq = {
    .channels    = BIT(ADC_CHANNEL),
    .buffer      = &adc_buf,
    .buffer_size = sizeof(adc_buf),
    .resolution  = ADC_RESOLUTION,
};

/* ── Debug pin (scope trigger around ADC sample) ─────────────────────────────
 * PA9: driven HIGH just before adc_read(), LOW immediately after.
 * Pulse width = ADC conversion time (~1 µs at 12-bit, ADCCLK/8).
 * Probe PA9 on CH2, PA8 (excitation) on CH1 to verify phase alignment.    */
#define DEBUG_PORT      GPIOA
#define DEBUG_PIN       GPIO_PIN_9

static void debug_pin_init(void)
{
    /* GPIOA clock already enabled by tim1_complementary_pwm_init() */
    GPIO_InitTypeDef gpio = {
        .Pin   = DEBUG_PIN,
        .Mode  = GPIO_MODE_OUTPUT_PP,
        .Pull  = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_HIGH,
    };
    HAL_GPIO_Init(DEBUG_PORT, &gpio);
    HAL_GPIO_WritePin(DEBUG_PORT, DEBUG_PIN, GPIO_PIN_RESET);
}

/* ── Demodulator state (ISR only) ────────────────────────────────────────────*/
static volatile uint8_t phase = 0;

/*
 * TIM1 CH1 / CH1N — complementary differential excitation
 *
 * Using a single timer with complementary outputs guarantees that the
 * two excitation signals are perfectly antiphase with zero skew. This
 * means the differential comb always sees equal and opposite drive
 * voltages, so any common-mode signal (power supply noise, vibration
 * coupling) cancels at the proof mass and never enters the signal chain.
 *
 * CH1  (PA8)  → comb fingers set A:  _|‾|_|‾|_  (10 kHz, 50% duty)
 * CH1N (PB13) → comb fingers set B:  ‾|_|‾|_|‾  (exact inverse, hardware)
 *
 * Dead-time is set to zero — safe here because we are driving capacitors,
 * not a power half-bridge where shoot-through is a concern.
 */
static void tim1_complementary_pwm_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM1_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {
        .Mode      = GPIO_MODE_AF_PP,
        .Pull      = GPIO_NOPULL,
        .Speed     = GPIO_SPEED_FREQ_HIGH,
        .Alternate = GPIO_AF1_TIM1,
    };

    gpio.Pin = GPIO_PIN_8;      /* PA8  = TIM1_CH1  */
    HAL_GPIO_Init(GPIOA, &gpio);

    gpio.Pin = GPIO_PIN_13;     /* PB13 = TIM1_CH1N */
    HAL_GPIO_Init(GPIOB, &gpio);

    /* APB2 timer clock = 192 MHz → period = 192M / 10k = 19200 counts */
    htim1.Instance               = TIM1;
    htim1.Init.Prescaler         = 0;
    htim1.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim1.Init.Period            = (192000000U / EXCITATION_HZ) - 1U;
    htim1.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_PWM_Init(&htim1);

    TIM_OC_InitTypeDef oc = {
        .OCMode       = TIM_OCMODE_PWM1,
        .Pulse        = (htim1.Init.Period + 1U) / 2U,  /* 50% duty */
        .OCPolarity   = TIM_OCPOLARITY_HIGH,
        .OCNPolarity  = TIM_OCNPOLARITY_HIGH,
        .OCFastMode   = TIM_OCFAST_DISABLE,
        .OCIdleState  = TIM_OCIDLESTATE_RESET,
        .OCNIdleState = TIM_OCNIDLESTATE_RESET,
    };
    HAL_TIM_PWM_ConfigChannel(&htim1, &oc, TIM_CHANNEL_1);

    TIM_BreakDeadTimeConfigTypeDef bdt = {
        .OffStateRunMode  = TIM_OSSR_DISABLE,
        .OffStateIDLEMode = TIM_OSSI_DISABLE,
        .LockLevel        = TIM_LOCKLEVEL_OFF,
        .DeadTime         = 0,
        .BreakState       = TIM_BREAK_DISABLE,
        .BreakPolarity    = TIM_BREAKPOLARITY_HIGH,
        .AutomaticOutput  = TIM_AUTOMATICOUTPUT_DISABLE,
    };
    HAL_TIMEx_ConfigBreakDeadTime(&htim1, &bdt);

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
}

/* ── TIM2: 40 kHz sampling interrupt (HAL) ───────────────────────────────────*/
static TIM_HandleTypeDef htim2;

static void tim2_sampling_init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* APB1 timer clock = 96 MHz → period = 96M / 40k = 2400 counts */
    htim2.Instance               = TIM2;
    htim2.Init.Prescaler         = 0;
    htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim2.Init.Period            = (96000000U / SAMPLE_HZ) - 1U;
    htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&htim2);

    HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
    HAL_TIM_Base_Start_IT(&htim2);
}

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
}

/*
 * TIM2 period elapsed callback — runs at 40 kHz (every 25 µs)
 *
 * This implements a software lock-in amplifier (synchronous demodulator):
 *
 *  Excitation (TIM1):   ___     ___     ___
 *                      |   |   |   |   |   |
 *                   ___|   |___|   |___|   |___   10 kHz square wave
 *
 *  ADC samples:     ^   ^   ^   ^   ^   ^         4 samples/cycle (40 kHz)
 *  phase:           0   1   2   3   0   1  ...
 *  ref (×1/−1):    +1  +1  −1  −1  +1  +1  ...   in sync with excitation
 *
 *  At rest (balanced comb):
 *    ADC signal is a square wave at 10 kHz with equal +/− amplitude.
 *    Multiplying by ref and summing → zero (cancels perfectly).
 *
 *  With displacement (comb unbalanced):
 *    Cx+ > Cx− → amplitude increases on positive half-cycle.
 *    After multiply by ref, both halves contribute positively → DC output.
 *    The DC value is proportional to displacement.
 *
 *  Noise rejection:
 *    Any signal not coherent with the 10 kHz reference (vibration, EMI,
 *    1/f noise) averages to zero over each accumulation window.
 *    This is the key advantage of the lock-in approach.
 *
 *  Decimation:
 *    We accumulate DECIMATE_BY = 200 demodulated samples, then post the
 *    average. This acts as a boxcar (moving average) pre-filter before
 *    the IIR in the main loop, and reduces the queue rate to 200 Hz.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance != TIM2) {
        return;
    }

    /* Step 1: sample the proof mass TIA output, remove DC bias (1.65V = 2048).
     * Debug pin PA9 pulses HIGH for the duration of the ADC conversion so the
     * timing can be verified against the excitation on a scope or logic analyser:
     *   CH1: PA8  — excitation + (10 kHz)
     *   CH2: PA9  — ADC sample strobe (40 kHz pulses, ~1 µs wide)
     * The rising edge of each pulse should align consistently with the
     * excitation phase; any jitter here directly affects demodulation quality. */
    HAL_GPIO_WritePin(DEBUG_PORT, DEBUG_PIN, GPIO_PIN_SET);
    adc_read(adc_dev, &adc_seq);
    HAL_GPIO_WritePin(DEBUG_PORT, DEBUG_PIN, GPIO_PIN_RESET);
    int32_t adc = (int32_t)adc_buf - ADC_MID;

    /* Step 2: generate reference square wave locked to TIM1 excitation.
     * phase 0,1 → excitation is HIGH → multiply by +1
     * phase 2,3 → excitation is LOW  → multiply by −1
     * Since TIM1 and TIM2 are started sequentially (not hardware-synced),
     * there is a small fixed phase offset at startup. This is constant and
     * only affects overall gain, not linearity. If needed, phase can be
     * trimmed by adjusting the OVERSAMPLE/2 boundary below. */
    int8_t ref = (phase < (OVERSAMPLE / 2U)) ? 1 : -1;
    phase = (uint8_t)((phase + 1U) % OVERSAMPLE);

    /* Step 3: multiply (demodulate) and accumulate.
     * Coherent signal (at excitation frequency) → builds up as DC.
     * Incoherent noise → cancels over the accumulation window. */
    static int32_t  accum = 0;
    static uint32_t count = 0;

    accum += adc * ref;

    /* Step 4: decimate — post average every DECIMATE_BY samples (200 Hz).
     * The average also acts as a boxcar low-pass filter, attenuating
     * components above 200 Hz before they reach the IIR. */
    if (++count >= DECIMATE_BY) {
        int32_t avg = accum / (int32_t)DECIMATE_BY;
        accum = 0;
        count = 0;
        /* K_NO_WAIT: never block the ISR; drop sample if main loop is behind */
        k_msgq_put(&raw_msgq, &avg, K_NO_WAIT);
    }
}

/* ── Main ────────────────────────────────────────────────────────────────────*/
int main(void)
{
    int ret;

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

    tim1_complementary_pwm_init();
    debug_pin_init();
    tim2_sampling_init();

    LOG_INF("Comb readout started — 10 kHz excitation, 200 Hz output, 32 Hz LPF");

    float    iir_state   = 0.0f;
    uint32_t print_count = 0;

    while (1) {
        int32_t raw;
        /* Block until ISR posts a decimated sample (every 5 ms at 200 Hz) */
        k_msgq_get(&raw_msgq, &raw, K_FOREVER);

        /* Single-pole IIR low-pass: y[n] = α·x[n] + (1−α)·y[n−1]
         * α = 0.632 gives 32 Hz cutoff at 200 Hz (= 1 − e^(−2π·32/200)).
         * Attenuates mechanical resonances and residual demodulation artefacts
         * above 32 Hz before the value is printed or used downstream. */
        iir_state += IIR_ALPHA * ((float)raw - iir_state);

        /* Print at 10 Hz: every 20th sample at 200 Hz */
        if (++print_count >= 20) {
            print_count = 0;
            printk("filtered: %.2f\n", (double)iir_state);
        }
    }

    return 0;
}
