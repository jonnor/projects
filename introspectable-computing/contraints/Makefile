
all: check native emscripten

native:
	gcc -o cstrain_kernel --std=c99 -Wall -Werror cstrain.c

emscripten:
	emcc -o cstrain_kernel.js -Wall -Werror cstrain.c

check: native
	./node_modules/.bin/mocha --compilers=coffee:coffee-script/register cstrain.coffee
