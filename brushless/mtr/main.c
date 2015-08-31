
#include <stdio.h>

#include <mtr.c>


int
main(int argc, char *argv[])
{
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
        printf("stepper position: %d, %d, %d\n",
            cmds[i].arg2,
            stepper->current_position,
            mtr_emu_position(emulator));
    }

    mtr_stepper_destroy(stepper);
    mtr_emu_destroy(emulator);
}
