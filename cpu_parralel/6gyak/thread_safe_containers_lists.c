#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
} Node;

typedef struct
{
    Node *head;
    int size;
} List;

List *createList()
{
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->size = 0;
    return list;
}

void pushList(List *list, int value)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = list->head;
    list->head = node;
    list->size++;
}

int popList(List *list)
{
    if (list->size == 0)
    {
        printf("List is empty.\n");
        return -1;
    }
    int value = list->head->value;
    Node *temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->size--;
    return value;
}

void printList(List *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void freeList(List *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
int main()
{
    List *list = createList();

    pushList(list, 1);
    pushList(list, 2);

    printList(list);

    popList(list);

    freeList(list);

    return 0;
}
