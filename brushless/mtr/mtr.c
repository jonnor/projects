
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define MTR_STATIC_ARRAY_LENGTH(arr) sizeof(arr)/sizeof(arr[0])

#ifdef DEBUG
#define MTR_DEBUG(fmt, ...) do { printf(fmt, ##__VA_ARGS__); } while (0)
#else
#define MTR_DEBUG(fmt, ...) do { } while (0)
#endif


static const
uint8_t
mtr_fullstep_sequence[] = {
    0b0011,
    0b0110,
    0b1100,
    0b1001
};
const uint8_t mtr_fullstep_length = MTR_STATIC_ARRAY_LENGTH(mtr_fullstep_sequence);


// Parser
typedef enum MtrCommandType_ {
    MtrMove = 0,
    MtrCommand_Invalid,
    MtrCommand_Max = 255
} MtrCommandType;

typedef struct MtrCommand_ {
    MtrCommandType type;
    int32_t arg1;
    int32_t arg2;
} MtrCommand;


// Stepper
typedef struct MtrBridge_ {
    uint8_t bits;
} MtrBridge;

typedef struct MtrConfig_ {
    int time_per_clock; // microseconds?
    int distance_per_step; // micrometer?
} MtrConfig;


typedef struct MtrStepper_ {
    // State
    int8_t sequence_no;
    MtrCommand current_cmd;
    int current_position;
    int current_time;

    // Settings
    MtrConfig config;
} MtrStepper;


void
mtr_stepper_init(MtrStepper *self) {
    self->sequence_no = 0;
    self->current_position = 0;
    self->current_time = 0;
}

void
mtr_stepper_destroy(MtrStepper *self) {

}

void
mtr_stepper_pushcmd(MtrStepper *self, MtrCommand cmd) {
    // FIXME: keep a buffer? or maybe that should stay outside?
    self->current_cmd = cmd;
}

void
mtr_stepper_calculate(MtrStepper *self, MtrBridge *out_bridge) {
    MtrBridge bridge_next;
    const int step_size = self->config.distance_per_step;

    self->current_time += self->config.time_per_clock;

    // each motion command is split up into a number of segments
    // for now we implement constant-velocity (acceleration-less) stepping
    const int distance_from_destination = self->current_position - self->current_cmd.arg2;
    //const int steps_to_dest = distance_from_destination/step_size;

    // XXX: hardcoded full-stepping
    if (distance_from_destination <= step_size) {
        // clockwise
        self->sequence_no += 1;
        if (self->sequence_no > 3) {
            self->sequence_no = 0;
        }
        self->current_position += step_size;
    } else if (distance_from_destination >= step_size) {
        // counter-clockwise
        self->sequence_no -= 1;
        if (self->sequence_no < 0) {
            self->sequence_no = 3;
        }
        self->current_position -= step_size;
    } else {
        // approximately there
    }
    // FIXME: set bridge_next
    
    //MTR_DEBUG("dist, steps2go %d, %d\n", distance_from_destination, steps_to_dest);
    //MTR_DEBUG("sequence_no %d\n", self->sequence_no);

    bridge_next.bits = mtr_fullstep_sequence[self->sequence_no];
    if (out_bridge) {
        *out_bridge = bridge_next;
    }
}

bool
mtr_stepper_done(MtrStepper *self) {
    const int distance = abs(self->current_position - self->current_cmd.arg2);
    const bool at_destination = distance < self->config.distance_per_step;
    return at_destination;
}


// Stepper emulator
typedef struct MtrEmulator_ {
    // State
    int current_position;
    MtrBridge state;

    // Settings
    MtrConfig config;
} MtrEmulator;

void
mtr_emu_init(MtrEmulator *self) {
    self->current_position = 0;
    self->state.bits = 255;
}

void
mtr_emu_destroy(MtrEmulator *self) {

}

void
mtr_print_steps(uint8_t bits) {
    MTR_DEBUG("step: %d%d%d%d\n",
        (bits&0b1000)>>3, (bits&0b0100)>>2, (bits&0b0010)>>1, bits&0b0001);
}

void
mtr_emu_step(MtrEmulator *self, MtrBridge step) {
    if (self->state.bits == 255) {
        self->state.bits = step.bits;
    }

    if (self->state.bits == step.bits) {
        return; // no-op
    }

    mtr_print_steps(step.bits);

    const int step_size = self->config.distance_per_step;

    // TODO: return error/warn for illegal inputs

    // calculate which direction we are moving
    // XXX: hardcoded full-step sequence
    int8_t current_sequence_no = -1;
    for (int i=0; i<4; i++) {
        if (mtr_fullstep_sequence[i] == self->state.bits) {
            current_sequence_no = i;
        }
    }

    if (current_sequence_no < 0) {
        MTR_DEBUG("ERROR: invalid current sequence no: %d", current_sequence_no);
    }

    // moving clockwise?
    int8_t next_sequence_no = current_sequence_no+1;
    if (next_sequence_no > 3) {
        next_sequence_no = 0;
    }

    if (mtr_fullstep_sequence[next_sequence_no] == step.bits) {
        self->current_position += step_size;
    } else {
        // moving counter-clockwise?
        next_sequence_no = current_sequence_no-1;
        if (next_sequence_no < 0) {
            next_sequence_no = 3;
        }
        if (mtr_fullstep_sequence[next_sequence_no] == step.bits) {
            self->current_position -= step_size;
        } else {
            MTR_DEBUG("ERROR: Invalid step %d, %d, %d\n",
                next_sequence_no, mtr_fullstep_sequence[next_sequence_no], step.bits);
        }
    }

    MTR_DEBUG("current: %d %d %d\n", current_sequence_no, self->current_position, step_size); 
    
    // TODO: calculated acceleration / speteed
    // TODO: consider microstepping

    self->state = step;
}

int
mtr_emu_position(MtrEmulator *self) {
    return self->current_position;
}
