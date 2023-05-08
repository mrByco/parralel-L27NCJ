#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAX_THREADS 32
#define M_PI 3.141593

// structure for passing parameters to threads
typedef struct
{
    int start;
    int end;
    int width;
    int height;
    int radius;
    float *input;
    float *output;
} thread_args_t;

// function to compute the Gaussian kernel
void compute_kernel(float *kernel, int radius)
{
    float sigma = radius / 3.0f;
    float s = 2.0f * sigma * sigma;
    float sum = 0.0f;
    for (int i = -radius; i <= radius; i++)
    {
        float r = (float)i;
        kernel[i + radius] = expf(-r * r / s) / sqrtf(M_PI * s);
        sum += kernel[i + radius];
    }
    for (int i = 0; i <= 2 * radius; i++)
    {
        kernel[i] /= sum;
    }
}

// function to apply the Gaussian blur to a range of pixels
void *blur_range(void *arg)
{
    thread_args_t *args = (thread_args_t *)arg;
    float *input = args->input;
    float *output = args->output;
    int width = args->width;
    int height = args->height;
    int radius = args->radius;
    int start = args->start;
    int end = args->end;
    float kernel[MAX_THREADS];
    compute_kernel(kernel, radius);
    for (int y = start; y < end; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float sum = 0.0f;
            for (int i = -radius; i <= radius; i++)
            {
                int px = x + i;
                if (px < 0)
                    px = 0;
                if (px >= width)
                    px = width - 1;
                sum += kernel[i + radius] * input[y * width + px];
            }
            output[y * width + x] = sum;
        }
    }
    pthread_exit(NULL);
}

// function to apply the Gaussian blur using multiple threads
void blur_image(float *input, float *output, int width, int height, int radius, int num_threads)
{

    pthread_t threads[MAX_THREADS];
    thread_args_t args[MAX_THREADS];
    int chunk_size = height / num_threads;
    for (int i = 0; i < num_threads; i++)
    {
        args[i].start = i * chunk_size;
        args[i].end = (i == num_threads - 1) ? height : (i + 1) * chunk_size;
        args[i].width = width;
        args[i].height = height;
        args[i].radius = radius;
        args[i].input = input;
        args[i].output = output;
        pthread_create(&threads[i], NULL, blur_range, &args[i]);
    }
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

// example usage
int main()
{
    // assume we have an input image of size 640x480
    int width = 640;
    int height = 480;
    float *input = (float *)malloc(width * height * sizeof(float));
    float *output = (float *)malloc(width * height * sizeof(float));
    // initialize the input image
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            input[y * width + x] = (float)rand() / (float)RAND_MAX;
        }
    }
    // apply the Gaussian blur using 4 threads and a radius of 5
    int radius = 5;
    int num_threads = 4;
    blur_image(input, output, width, height, radius, num_threads);

    // save the output image
    FILE *fout = fopen("output.raw", "wb");
    fwrite(output, sizeof(float), width * height, fout);
    fclose(fout);
    // free memory
    free(input);
    free(output);
    return 0;
}