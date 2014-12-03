
// gcc -o test test.c -std=c99 -Wall -Werror `pkg-config --libs --cflags glib-2.0` -I /home/jon/contrib/code/mypaint/brushlib/tests -I /home/jon/contrib/code/mypaint/brushlib && ./test 

#include <glib.h>
#include "mypaint-benchmark.c"

static void
pixels_add_inplace(float *a, const float *b, int number)
{
    for (int i=0; i<number; i++) {
        a[i] = b[i] + a[i];
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
pixels_set(float *p, float c, int n) {
    for (int i=0; i<n; i++) {
        p[i] = c;
    }
}

int
main(int argc, char *argv[])
{
    const int chunk_size = 64*64;
    const int total_size = 4096*4096;


    gfloat *a = g_new(gfloat, total_size);
    gfloat *b = g_new(gfloat, total_size);
    pixels_set(a, 3.0f, total_size);
    pixels_set(b, 2.0f, total_size);

    // Process
    mypaint_benchmark_start("test1");

    g_assert((total_size%chunk_size) == 0);
    const int chunks = total_size/chunk_size;

    #pragma omp parallel for schedule(static)
    for (int i=0; i<chunks; i++) {
        const int offset = i*chunk_size;
        pixels_add_inplace(&a[offset], &b[offset], chunk_size);
/*
        pixels_add_inplace(&a[offset], &b[offset], chunk_size);
        pixels_add_inplace(&a[offset], &b[offset], chunk_size);
        pixels_add_inplace(&a[offset], &b[offset], chunk_size);
        pixels_add_inplace(&a[offset], &b[offset], chunk_size);
        pixels_add_inplace(&a[offset], &b[offset], chunk_size);
        pixels_add_inplace(&a[offset], &b[offset], chunk_size);
*/
    }

    const int process_time_ms = mypaint_benchmark_end();

    // Analyze

    const float mpixels = (total_size/1000000.0f);
    const float mpixels_per_second = mpixels/(process_time_ms/1000.0f);
    g_print("Size: %.2f (mpixels) in %d chunks\n", mpixels, chunks);
    g_print("Time: %.2f (milliseconds)\n", (double)process_time_ms);
    g_print("Speed: %.2f (mpixels/s)\n", mpixels_per_second);

    g_assert(a[0] == 5.0f);
    g_assert(a[total_size-1] == 5.0f);

    // Teardown
    g_free(a);
    g_free(b);
}
