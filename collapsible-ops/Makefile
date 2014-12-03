
LIBMYPAINT="/home/jon/contrib/code/mypaint/brushlib"
INCLUDES=`pkg-config --libs --cflags glib-2.0` -I $(LIBMYPAINT)/tests -I $(LIBMYPAINT)
FLAGS=-O3 -std=c99 -fopenmp -Wall -Werror

all: check

build:
	gcc -o test test.c $(FLAGS) $(INCLUDES)

run: build
	./test

perf-run: build
	perf stat ./test

check: perf-run

asm: build
	objdump -d -M intel -S test
