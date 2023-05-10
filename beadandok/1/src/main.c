#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <windows.h>

#define MAX_THREADS 13
#define M_PI 3.141593

typedef struct Results
{
    int start;
    int init_finish;
    int blur_finish;
    int end;
};

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

/*
Works only on unix systems
long long current_timestamp_ms()
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    return spec.tv_sec * 1000LL + spec.tv_nsec / 1000000LL;
}*/

// Windows implementation of current_timestamp_ms()

long long current_timestamp_ms()
{
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);

    ULARGE_INTEGER timestamp;
    timestamp.LowPart = ft.dwLowDateTime;
    timestamp.HighPart = ft.dwHighDateTime;

    long long milliseconds = timestamp.QuadPart / 10000LL;
    milliseconds -= 11644473600000LL; // convert from Windows epoch to Unix epoch

    return milliseconds;
}

// function to compute the Gaussian kernel
void compute_kernel(float *kernel, int radius)
{
    int kernel_diameter = radius * 2 + 1;
    float sigma = radius / 3.0f;
    float s = 2.0f * sigma * sigma;
    float sum = 0.0f;
    for (int i = -radius; i <= radius; i++)
    {
        for (int j = -radius; j <= radius; j++)
        {
            float r = sqrtf((float)(i * i + j * j));
            kernel[(i + radius) * kernel_diameter + (j + radius)] = expf(-r * r / s) / sqrtf(M_PI * s);
            sum += kernel[(i + radius) * kernel_diameter + (j + radius)];
        }
    }
    for (int i = 0; i < kernel_diameter * kernel_diameter; i++)
    {
        kernel[i] /= sum;
    }
}

// function to apply the Gaussian blur to a range of pixels
void *blur_range(void *arg)
{
    // printf("Thread %ld\n", pthread_self());
    //  printf("start, stop: %d, %d\n", ((thread_args_t *)arg)->start, ((thread_args_t *)arg)->end);
    thread_args_t *args = (thread_args_t *)arg;
    float *input = args->input;
    float *output = args->output;
    int width = args->width;
    int height = args->height;
    int radius = args->radius;
    int start = args->start;
    int end = args->end;
    float kernel[(radius * 2 + 1) * (radius * 2 + 1)];

    compute_kernel(kernel, radius);

    // printf kernel 2d
    /*printf("Kernel 2D: \n");
    for (int i = 0; i < (radius * 2 + 1); i++)
    {
        for (int j = 0; j < (radius * 2 + 1); j++)
        {
            printf("%.4f ", kernel[i * (radius * 2 + 1) + j]);
        }
        printf("\n");
    }*/

    for (int y = start; y < end; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float sum = 0.0f;

            for (int ky = -radius; ky <= radius; ky++)
            {
                for (int kx = -radius; kx <= radius; kx++)
                {
                    int nky = y + ky;
                    int nkx = x + kx;
                    if (nky >= 0 && nky < height && nkx >= 0 && nkx < width)
                    {
                        sum += input[nky * width + nkx] * kernel[(ky + radius) * (radius * 2 + 1) + (kx + radius)];
                    }
                }
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
    float clocks_per_ms = CLOCKS_PER_SEC / 1000;
    clock_t startTime = current_timestamp_ms();

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
    int radius = 1;
    int num_threads = MAX_THREADS;

    blur_image(input, output, width, height, radius, num_threads);
    clock_t endTime = current_timestamp_ms();

    // save the output image
    FILE *fout = fopen("output.raw", "wb");
    fwrite(output, sizeof(float), width * height, fout);
    fclose(fout);

    // free memory
    free(input);
    free(output);

    printf("Start, end: %ld, %ld\n", startTime, endTime);
    printf("Time: %ldms\n", (endTime - startTime));

    return 0;
}