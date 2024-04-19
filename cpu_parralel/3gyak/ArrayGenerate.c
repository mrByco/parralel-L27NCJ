#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isUnique(int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (array[i] == array[j])
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    int n;
    printf("Enter the length of the array: ");
    scanf("%d", &n);

    srand(time(0));

    int array[n];
    clock_t start = clock();
    for (int i = 0; i < n; i++)
    {
        array[i] = i;
        if (rand() % 2 == 0)
        {
            array[i] = rand() % n;
        }
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Array generated with %d elements in %f seconds.\n", n, time_taken);

    if (isUnique(array, n))
    {
        printf("All elements are unique.\n");
    }
    else
    {
        printf("Array contains duplicate elements.\n");
    }

    return 0;
}