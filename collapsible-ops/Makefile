
LIBMYPAINT="/home/jon/contrib/code/mypaint/brushlib"
INCLUDES=`pkg-config --libs --cflags glib-2.0` -I $(LIBMYPAINT)/tests -I $(LIBMYPAINT)
FLAGS=-O3 -std=c99 -fopenmp -Wall -Werror -g -Wa,-adhln

all: check

niceasm:
	gcc -o test.asm test.c $(FLAGS) $(INCLUDES) -S

build: niceasm
	gcc -o test test.c $(FLAGS) $(INCLUDES)

run: build
	./test

perf-run: build
	#perf stat  -e L1-dcache-loads -e L1-dcache-load-misses -e cycles,instructions,cache-misses ./test
	perf stat ./test

check: perf-run

asm: build
	objdump -d -M intel -S test


