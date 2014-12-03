
// gcc -o test test.c -std=c99 -Wall -Werror `pkg-config --libs --cflags glib-2.0` -I /home/jon/contrib/code/mypaint/brushlib/tests -I /home/jon/contrib/code/mypaint/brushlib && ./test 

#include <glib.h>
#include "mypaint-benchmark.c"

static void
pixels_mul_inplace(float *a, const float *b, int number)
{
    for (int i=0; i<number*4; i+=4) {
        a[i+0] = b[i+0] * a[i+0];
        a[i+1] = b[i+1] * a[i+1];
        a[i+2] = b[i+2] * a[i+2];
        a[i+3] = b[i+3] * a[i+3];
    }
}

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
process(float *a, float *b, int total_size, int chunk_size)
{
    g_assert((total_size%chunk_size) == 0);
    const int chunks = total_size/chunk_size;

    #pragma omp parallel for schedule(static)
    for (int i=0; i<chunks; i++) {
        const int offset = i*chunk_size;
        pixels_mul_inplace(&a[offset], &b[offset], chunk_size);
    }
}

int
main(int argc, char *argv[])
{
    const int chunk_size = 64*64;
    const int total_size = 4096*4096;

    gfloat *a = g_new(gfloat, total_size*4);
    gfloat *b = g_new(gfloat, total_size*4);
    const gfloat c1[4] = {3.0f, 3.0f, 3.0f, 3.0f};
    const gfloat c2[4] = {2.0f, 2.0f, 2.0f, 2.0f};
    pixels_set(a, c1, total_size);
    pixels_set(b, c2, total_size);

    // Process
    mypaint_benchmark_start("test1");
    process(a, b, total_size, chunk_size);
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
    g_print("Time: %.2f (milliseconds)\n", (double)process_time_ms);
    g_print("Speed: %.2f (mpixels/s)\n", mpixels_per_second);
    g_print("Theoretical max: %.2f (mpixels/s)\n", max_mpixels_second);
    g_print("Utilization: %.2f %%\n", utilization*100);

    g_assert(a[0] == 5.0f);
    g_assert(a[total_size-1] == 5.0f);

    // Teardown
    g_free(a);
    g_free(b);
}
