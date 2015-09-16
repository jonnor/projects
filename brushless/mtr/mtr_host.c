
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

    mtr_gcodeparser_init(&self->gcode_parser);

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
    mtr_machine_xy_init(self);
    return self;
}


void
mtr_machine_xy_sendgcode(MtrMachineXY *self, const char *str) {
    MtrCommand cmd;
    
    for (int i=0; i<=strlen(str); i++) { 
        const char byte = str[i];
        const bool cmd_ready = mtr_gcodeparser_parse(&self->gcode_parser, byte, &cmd);
        if (cmd_ready && cmd.type == MtrMove) {
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
    snprintf(str, MAX_LEN, "X: %8.2f Y: %8.2f",
            (float)mtr_emu_position(&self->emu_x),
            (float)mtr_emu_position(&self->emu_y)
    );
    return str;
}
