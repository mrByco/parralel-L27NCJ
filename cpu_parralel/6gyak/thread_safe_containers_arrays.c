#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10

typedef struct
{
    int *data;
    int size;
    int capacity;
} Array;

Array *createArray()
{
    Array *array = malloc(sizeof(Array));
    array->size = 0;
    array->capacity = INITIAL_SIZE;
    array->data = malloc(sizeof(int) * array->capacity);
    return array;
}

void pushArray(Array *array, int value)
{
    if (array->size == array->capacity)
    {
        array->capacity *= 2;
        array->data = realloc(array->data, sizeof(int) * array->capacity);
    }
    array->data[array->size++] = value;
}

int popArray(Array *array)
{
    if (array->size == 0)
    {
        printf("Array is empty.\n");
        return -1;
    }
    int value = array->data[--array->size];
    if (array->size < array->capacity / 2 && array->capacity > INITIAL_SIZE)
    {
        array->capacity /= 2;
        array->data = realloc(array->data, sizeof(int) * array->capacity);
    }
    return value;
}

void printArray(Array *array)
{
    for (int i = 0; i < array->size; i++)
    {
        printf("%d ", array->data[i]);
    }
    printf("\n");
}

void freeArray(Array *array)
{
    free(array->data);
    free(array);
}

int main()
{
    Array *array = createArray();

    pushArray(array, 1);
    pushArray(array, 2);

    printArray(array);

    popArray(array);

    freeArray(array);

    return 0;
}
