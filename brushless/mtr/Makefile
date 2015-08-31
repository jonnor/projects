CFLAGS:=-Wall -Werror -I. --std=c99 -DDEBUG=1 ${EXTRA_CFLAGS}

check: main
	./main

emscripten:
	emcc -o mtr.js main.c ${CFLAGS}

all: check
