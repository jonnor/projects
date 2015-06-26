
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

int
main(int argc, char *argv[]) {

}
