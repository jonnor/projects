
#include <stdio.h>

#include "mtr.c"

#include <stdlib.h>

#define MTR_NEW(Type) (Type *)malloc(sizeof(Type)*1)

MtrEmulator *
mtr_emu_new() {
    MtrEmulator *self = MTR_NEW(MtrEmulator);
    mtr_emu_init(self);
    return self;
}

void
mtr_emu_free(MtrEmulator *self) {
    mtr_emu_destroy(self);
    free(self);
}


MtrStepper *
mtr_stepper_new() {
    MtrStepper *self = MTR_NEW(MtrStepper);
    mtr_stepper_init(self);
    return self;
}

void
mtr_stepper_free(MtrStepper *self) {
    mtr_stepper_destroy(self);
    free(self);
}

void mtr_run_smokecheck() {

    MtrEmulator s_emulator;
    MtrEmulator *emulator = &s_emulator;
    mtr_emu_init(emulator);

    MtrStepper s_stepper;
    MtrStepper *stepper = &s_stepper;
    mtr_stepper_init(stepper);

    MtrConfig config;
    config.time_per_clock = 10;
    config.distance_per_step = 13;

    stepper->config = config;
    emulator->config = config;

    // would normally come from I2C or gcode+USB/serial
    MtrCommand cmds[] = {
        { MtrMove, 0, 31*10 },
        { MtrMove, 0, 53*10 },
        { MtrMove, 0, 1*10 }
    };

    for (int i=0; i<MTR_STATIC_ARRAY_LENGTH(cmds); i++) {
        mtr_stepper_pushcmd(stepper, cmds[i]);
        while (!mtr_stepper_done(stepper)) {
            MtrBridge step;
            mtr_stepper_calculate(stepper, &step);
            mtr_emu_step(emulator, step);
        }
        printf("stepper position: %d == %d == %d\n",
            cmds[i].arg2,
            stepper->current_position,
            mtr_emu_position(emulator));
    }

    mtr_stepper_destroy(stepper);
    mtr_emu_destroy(emulator);
}
