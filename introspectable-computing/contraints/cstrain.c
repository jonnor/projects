
/*
References:
http://ktiml.mff.cuni.cz/~bartak/constraints/constrsat.html
https://github.com/srikumarks/FD.js

Core implementation ideas:

- compilable to JavaScript using Emscripten
- split into a kernel/backend in C and pre-processor/frontent in JS
- easy+efficient integration into higher-level language, by message passing
- operate only on binary constraints, compiling higher-level constraints

*/

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cstrain_declarations.h"

typedef int32_t VariableId;

typedef struct {
    int32_t cmd; // a Command
    int32_t a; // value or VariableId
    int32_t b; // value or VariableId
    int32_t c; // value or VariableId
} CommandData;

typedef struct {
    enum ConstraintType type;
    VariableId a;
    VariableId b;
} Constraint;

typedef struct {
    int32_t lower;
    int32_t upper;
} Domain;

typedef struct {
    Constraint *constraints;
    uint32_t n_constraints;

    uint32_t n_variables;
    Domain *domains;
    int32_t *values;
} Solver;


static bool
check_constraint(int32_t *values, Constraint c)
{
    const VariableId a = c.a;
    const VariableId b = c.b;
    switch (c.type) {
    case CS_EQ:
        return values[a] == values[b];
    case CS_NEQ:
        return values[a] != values[b];
    case CS_LT:
        return values[a] < values[b];
    case CS_GT:
        return values[a] > values[b];
    case CS_LTE:
        return values[a] <= values[b];
    case CS_GTE:
        return values[a] >= values[b];
    default:
        return false;
    }
}

static bool
check_constraints(int32_t *values, Constraint *constraints, uint32_t n_constraints)
{
    for (int i=0; i<n_constraints; i++) {
        const bool pass = check_constraint(values, constraints[i]);
        if (!pass) {
            return false;
        }
    }
    return true;
}

void
solver_init(Solver *self)
{
    self->constraints = NULL;
    self->n_constraints = 0;

    self->n_variables = 0;
    self->values = NULL;
    self->domains = NULL;
}

void
solver_destroy(Solver *self)
{
    if (self->constraints) {
        free(self->constraints);
        self->constraints = NULL;
    }
    if (self->values) {
        free(self->values);
        self->values = NULL;
    }
    if (self->domains) {
        free(self->domains);
        self->domains = NULL;
    }
}

bool
solver_naive(Solver *self)
{
    check_constraints(self->values, self->constraints, self->n_constraints);
    return true;
}

bool
solver_read_file(Solver *self, const char *fname)
{
    static const size_t CMD_SIZE = 4*4;
    unsigned char buffer[CMD_SIZE];
    FILE *f = fopen(fname, "rb");

    if (!f) { return false; }

    size_t read = 0;
    do {
        read = fread(buffer, CMD_SIZE, 1, f);
        if (read) {
            CommandData* cmd = (CommandData *)(&buffer);
            printf("op=%d \n", cmd->cmd);
        }
    } while (read > 0);

    printf("read %zd bytes\n", read);
    fclose(f);
    return true;
}

int
main(int argc, char *argv[]) {
 
    if (argc != 2) {
        fprintf(stderr, "Expected 2 arguments\n");
        exit(1);
    }
    char *fname = argv[1];

    Solver solver;
    solver_init(&solver);

    printf("reading %s\n", fname);
    solver_read_file(&solver, fname);

    solver_destroy(&solver);
}
