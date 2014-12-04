
// gcc -o test test.c -std=c99 -Wall -Werror `pkg-config --libs --cflags glib-2.0` -I /home/jon/contrib/code/mypaint/brushlib/tests -I /home/jon/contrib/code/mypaint/brushlib && ./test 

/*
TODO:
* Actually have a list of (non-trivial) operations that are applied in sequence
* Improve cache misses. Currently 15-30 % miss rate
*/

#include <glib.h>
#include "mypaint-benchmark.c"


static void
pixels_mul_inplace(const float * restrict a,
                   const float * restrict b,
                   float * restrict out,
                   int number)
{
    a = __builtin_assume_aligned (a, 16);
    b = __builtin_assume_aligned (b, 16);
    out = __builtin_assume_aligned (out, 16);

    for (int i=0; i<number*4; i+=8) {
        #define DO_MUL(offset) \
        { \
            out[i+offset] = a[i+offset] * b[i+offset]; \
        }
        DO_MUL(0)
        DO_MUL(1)
        DO_MUL(2)
        DO_MUL(3)
        DO_MUL(4)
        DO_MUL(5)
        DO_MUL(6)
        DO_MUL(7)
        #undef DO_MUL
    }
}

/*
static void
pixels_mul_inplace(const float * restrict a,
                   const float * restrict b,
                   float * restrict out,
                   int number)
{
    a = __builtin_assume_aligned (a, 16);
    b = __builtin_assume_aligned (b, 16);
    out = __builtin_assume_aligned (out, 16);
    for (int i=0; i<number*4; i+=1) {
        out[i] = a[i] * b[i];
    }
}
*/

/*
static float
pixel_add(float a, float b)
{
    return a+b;
}
*/

static void
pixels_set(float *p, const float c[4], int n) {
    for (int i=0; i<n*4; i+=4) {
        p[i+0] = c[0];
        p[i+1] = c[1];
        p[i+2] = c[2];
        p[i+3] = c[3];
    }
}

static void
process(const float *a, const float *b, float *out, int total_size, int chunk_size)
{
    g_assert((total_size%chunk_size) == 0);
    const int chunks = total_size/chunk_size;

//    #pragma omp parallel for schedule(static)
    // FIXME: Fix vectorization breaking when using OpenMP and not inlining
    for (int i=0; i<chunks; i++) {
        const int offset = i*chunk_size;
        const float * restrict A = __builtin_assume_aligned(a+offset, 16);
        const float * restrict B = __builtin_assume_aligned(b+offset, 16);
        float * restrict O = __builtin_assume_aligned(out+offset, 16);
        pixels_mul_inplace(A, B, O, chunk_size);
    }
}

int
main(int argc, char *argv[])
{
    const int chunk_size = 128*128;
    const int total_size = 8192*8192;

    gfloat *a __attribute__ ((aligned (16)));
    gfloat *b __attribute__ ((aligned (16)));
    gfloat *out __attribute__ ((aligned (16)));
    a = g_new(gfloat, total_size*4);
    b = g_new(gfloat, total_size*4);
    out = g_new(gfloat, total_size*4);
    const gfloat c1[4] = {3.0f, 3.0f, 3.0f, 3.0f};
    const gfloat c2[4] = {2.0f, 2.0f, 2.0f, 2.0f};
    pixels_set(a, c1, total_size);
    pixels_set(b, c2, total_size);

    // Process
    mypaint_benchmark_start("test1");
    process(a, b, out, total_size, chunk_size);
    const int process_time_ms = mypaint_benchmark_end();

    // Analyze
    const int chunks = total_size/chunk_size;
    const float mpixels = (total_size/1000000.0f);
    const float mpixels_per_second = mpixels/(process_time_ms/1000.0f);

    // XXX: CPU model specific
    // http://stackoverflow.com/questions/15655835/flops-per-cycle-for-sandy-bridge-and-haswell-sse2-avx-avx2
    const float cpu_megahertz = 2400;
    const float cpu_cores = 2;
    const float cpu_flops = 4; // note: ignores that multiply & add can be done at same time

    const float operation_flops_pixel = 4; // XXX: op specific

    const float max_mpixels_second = cpu_megahertz*cpu_cores*cpu_flops/operation_flops_pixel;
    const float utilization = mpixels_per_second/max_mpixels_second;
    g_print("Size: %.2f (mpixels) in %d chunks\n", mpixels, chunks);
    g_print("Time: %.2f (milliseconds), %.2fms per chunk\n", (double)process_time_ms, (double)process_time_ms/chunks);
    g_print("Speed: %.2f (mpixels/s)\n", mpixels_per_second);
    g_print("Theoretical max: %.2f (mpixels/s)\n", max_mpixels_second);
    g_print("Utilization: %.2f %%\n", utilization*100);

    //g_print("%f\n", out[0]);
    g_assert(out[0] == 6.0f);
    g_assert(out[total_size-1] == 6.0f);

    // Teardown
    g_free(a);
    g_free(b);
    g_free(out);
}
