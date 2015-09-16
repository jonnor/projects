CFLAGS:=-Wall -Werror -I. --std=c99 -DDEBUG=1 ${EXTRA_CFLAGS}

EMSCRIPTEN_EXPORTS='["_mtr_emu_new", "_mtr_stepper_new"]'
EMSCRIPTEN_OPTIONS=-s EXPORTED_FUNCTIONS=$(EMSCRIPTEN_EXPORTS)

check: main
	./main

emscripten:
	emcc -o browser/mtr.js mtr_host.c ${CFLAGS} ${EMSCRIPTEN_OPTIONS}

all: check
