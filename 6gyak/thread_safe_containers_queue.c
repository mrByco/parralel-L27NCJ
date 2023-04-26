#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10

typedef struct
{
    int *data;
    int head;
    int tail;
    int size;
    int capacity;
} Queue;

Queue *createQueue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
    queue->capacity = INITIAL_SIZE;
    queue->data = malloc(sizeof(int) * queue->capacity);
    return queue;
}

void enqueue(Queue *queue, int value)
{
    if (queue->size == queue->capacity)
    {
        queue->capacity *= 2;
        queue->data = realloc(queue->data, sizeof(int) * queue->capacity);
    }
    queue->data[queue->tail++] = value;
    queue->tail %= queue->capacity;
    queue->size++;
}

int dequeue(Queue *queue)
{
    if (queue->size == 0)
    {
        printf("Queue is empty.\n");
        return -1;
    }
    int value = queue->data[queue->head++];
    queue->head %= queue->capacity;
    queue->size--;
    if (queue->size < queue->capacity / 2 && queue->capacity > INITIAL_SIZE)
    {
        queue->capacity /= 2;
        queue->data = realloc(queue->data, sizeof(int) * queue->capacity);
    }
    return value;
}

void printQueue(Queue *queue)
{
    if (queue->size == 0)
    {
        printf("Queue is empty.\n");
        return;
    }
    int current = queue->head;
    while (current != queue->tail)
    {
        printf("%d ", queue->data[current++]);
        current %= queue->capacity;
    }
    printf("\n");
}

void freeQueue(Queue *queue)
{
    free(queue->data);
    free(queue);
}

int main()
{
    Queue *queue = createQueue();

    enqueue(queue, 1);
    enqueue(queue, 2);

    printQueue(queue);

    dequeue(queue);

    freeQueue(queue);

    return 0;
}
