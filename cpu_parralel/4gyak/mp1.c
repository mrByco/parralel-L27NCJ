#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 10
#define NUM_RANGES 10

int primes[NUM_RANGES];

int is_prime(int n)
{
    if (n <= 1)
        return 0;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

void count_primes(int index)
{
    int start = index * 100;
    int end = start + 99;
    int count = 0;
    
    for (int i = start; i <= end; i++) {
        if (is_prime(i))
            count++;
    }
    
    primes[index] = count;
}

int main()
{
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int thread_id = omp_get_thread_num();
        count_primes(thread_id);
    }

    printf("Primes in ranges:\n");
    for (int i = 0; i < NUM_RANGES; i++)
        printf("[%d, %d]: %d\n", i*100, i*100+99, primes[i]);

    return 0;
}
