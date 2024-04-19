#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10

typedef struct
{
    int *data;
    int top;
    int capacity;
} Stack;

Stack *createStack()
{
    Stack *stack = malloc(sizeof(Stack));
    stack->top = -1;
    stack->capacity = INITIAL_SIZE;
    stack->data = malloc(sizeof(int) * stack->capacity);
    return stack;
}

void push(Stack *stack, int value)
{
    if (stack->top == stack->capacity - 1)
    {
        stack->capacity *= 2;
        stack->data = realloc(stack->data, sizeof(int) * stack->capacity);
    }
    stack->data[++stack->top] = value;
}

int pop(Stack *stack)
{
    if (stack->top == -1)
    {
        printf("Stack is empty.\n");
        return -1;
    }
    int value = stack->data[stack->top--];
    if (stack->top < stack->capacity / 2 && stack->capacity > INITIAL_SIZE)
    {
        stack->capacity /= 2;
        stack->data = realloc(stack->data, sizeof(int) * stack->capacity);
    }
    return value;
}

void printStack(Stack *stack)
{
    if (stack->top == -1)
    {
        printf("Stack is empty.\n");
        return;
    }
    for (int i = stack->top; i >= 0; i--)
    {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

void freeStack(Stack *stack)
{
    free(stack->data);
    free(stack);
}

int main()
{
    Stack *stack = createStack();

    push(stack, 1);
    push(stack, 2);

    printStack(stack);

    pop(stack);

    freeStack(stack);

    return 0;
}
