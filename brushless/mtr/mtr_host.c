
#include <stdio.h>

#include "mtr.c"

#include <string.h>
#include <stdlib.h>

#define MTR_NEW(Type) (Type *)malloc(sizeof(Type)*1)

// new/free functions, for Emscripten
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


// Representation of a simple two-axis machine, for testing
typedef struct _MtrMachineXY {
    MtrStepper stepper_x;
    MtrStepper stepper_y;

    MtrGcodeParser gcode_parser;

    MtrEmulator emu_x;
    MtrEmulator emu_y;
} MtrMachineXY;

void
mtr_machine_xy_init(MtrMachineXY *self) {

    mtr_stepper_init(&self->stepper_x);
    mtr_stepper_init(&self->stepper_y);

    mtr_emu_init(&self->emu_x);
    mtr_emu_init(&self->emu_y);

    // FIXME: unhardcode config, allow setting over commands
    MtrConfig config;
    config.time_per_clock = 10;
    config.distance_per_step = 13;

    self->stepper_x.config = config;
    self->stepper_y.config = config;
    self->emu_x.config = config;
    self->emu_y.config = config;
}



MtrMachineXY *
mtr_machine_xy_new() {
    MtrMachineXY *self = MTR_NEW(MtrMachineXY);
    return self;
}


void
mtr_machine_xy_sendgcode(MtrMachineXY *self, const char *str) {
    MtrCommand cmd;
    
    for (int i=0; i<strlen(str); i++) { 
        const char byte = str[i];
        const bool cmd_ready = mtr_gcodeparser_parse(&self->gcode_parser, byte, &cmd);
        if (cmd_ready) {
            MtrStepper *target = (cmd.arg3 == MtrXAxis) ? &self->stepper_x : &self->stepper_y;
            MtrEmulator *target_emu = (cmd.arg3 == MtrXAxis) ? &self->emu_x : &self->emu_y;
            mtr_stepper_pushcmd(target, cmd);

            // Note: single axis movement only
            while (!mtr_stepper_done(target)) {
                MtrBridge step;
                mtr_stepper_calculate(target, &step);
                mtr_emu_step(target_emu, step);
            }
        }
    }
}

// TODO: implement as response to gcode command instead (M114)
char *
mtr_machine_xy_current_position(MtrMachineXY *self) {
    size_t MAX_LEN = 100;
    char *str = malloc(MAX_LEN+1);
    snprintf(str, MAX_LEN, "X: %.2f X: %.2f",
            (float)mtr_emu_position(&self->emu_x),
            (float)mtr_emu_position(&self->emu_y)
    );
    return str;
}




void mtr_run_smokecheck_single() {

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


void mtr_run_smokecheck_xy() {
    MtrMachineXY *machine = mtr_machine_xy_new();
    const char * cmds[] = {
        "G1 X11",
        "G1 Y33",
        "G1 X22",
        "G1 Y22"
    };
    for (int i=0; i<MTR_STATIC_ARRAY_LENGTH(cmds); i++) {
        mtr_machine_xy_sendgcode(machine, cmds[i]);
        printf("position: %s\n",
            mtr_machine_xy_current_position(machine)
        );
    }
}

void
mtr_run_smokecheck() {
    mtr_run_smokecheck_xy();

    mtr_run_smokecheck_single();
}
