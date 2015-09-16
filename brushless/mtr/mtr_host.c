
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
