
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
#include "cstrain_declarations.h"

struct CsCommand {
    int32_t op; // a CsConstraint
    int32_t a; // a 
    int32_t b; // in case of num, is a value instead of
    int32_t padding[1];
}

int
main(int argc, char *argv[]) {

}
