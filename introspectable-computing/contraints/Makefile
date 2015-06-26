
all: check native emscripten

native:
	gcc -o cstrain_kernel -Wall -Werror cstrain.c

emscripten:
	emcc -o cstrain_kernel.js -Wall -Werror cstrain.c

check:
	./node_modules/.bin/mocha --compilers=coffee:coffee-script/register cstrain.coffee
