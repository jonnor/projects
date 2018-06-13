// # Touch controlled LEDs for jewelry
// For Attiny10

#include <stdint.h>

#ifdef REAL_HARDWARE

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

#endif // REAL_HARDWARE



// ## Application logic
struct Outputs {
    uint8_t led1;
    uint8_t led2;
    uint8_t led3;
};

struct Inputs {
    int time; // microseconds
    bool touch_on;
};


struct State {
    bool was_touched;
};


static inline void
next_state(const Inputs *inputs, State *state, Outputs *out) {
    State previous;
    previous = *state;

    // TODO: implement animation
    const uint8_t ledvalue = (inputs->was_touched) ? 1 : 0;

    out->led1 = ledvalue;
    out->led2 = ledvalue;
    out->led3 = ledvalue;
}


// ## Hardware specific
#ifdef REAL_HARDWARE
int g_ticks = 0;

// Pin configuration
const uint8_t LED1_PIN = PB0;
const uint8_t LED2_PIN = PB1;
const uint8_t TOUCH_PIN = PB2; //ADC2
const uint8_t LED3_PIN = PB3;


ISR(TIM0_OVF_vect) {
    g_ticks += 1;
}

static void
init_hardware() {

    // TODO: implement PWM for LEDs
    // something like https://blog.thegaragelab.com/pwm-output-on-the-attiny85/

    // Setup Timer0 overflow interrupt
    TCCR0A = 0x00; // normal counter operation
    TCCR0B = 0x02; // timer clock = 1 MHz / 8
    TIMSK0 = 0x01; // enable overflow interrupt

    // TODO: Setup touch sensing

    // Setup LED outputs
    DDRB |= (1 << LED1_PIN);
    DDRB |= (1 << LED2_PIN);
    DDRB |= (1 << LED3_PIN);

    sei();  // Enable Global Interrupts
}

static void
realize_outputs(Out out) {
    PORTB |= (out.led1 << LED1_PIN);
    PORTB |= (out.led2 << LED2_PIN);
    PORTB |= (out.led3 << LED3_PIN);
}


void main(void) {

    State state = { false };
    Inputs inputs;
    Outputs outputs;

    init();

    while (true) {
        inputs.time = g_ticks; // TODO: calculate microseconds
        inputs.was_touched = true; // TODO: actually do capacitive sensing

        next_state(&inputs, &state, &outputs);

        realize_outputs(&outputs);
    }
}
#endif // REAL_HARDWARE
