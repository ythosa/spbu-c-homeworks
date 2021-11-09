#include <stdlib.h>

#include "stack.h"

typedef struct Node {
    struct Node* next;
    Value data;
} Node;

static Node* nodeCreate(Value data)
{
    Node* node = malloc(sizeof(Node));

    node->next = NULL;
    node->data = data;

    return node;
}

static void nodeFree(Node* node)
{
    free(node);
}

struct Stack {
    Node* head;
    int size;
};

Stack* stackCreate()
{
    Stack* stack = malloc(sizeof(Stack));

    stack->head = NULL;
    stack->size = 0;

    return stack;
}

void stackFree(Stack* stack)
{
    while (stack->size)
        stackPop(stack);

    free(stack);
}

void stackShallowFree(Stack* stack)
{
    free(stack);
}

int stackGetSize(Stack* stack)
{
    return stack->size;
}

bool isEmpty(Stack* stack)
{
    return stack->size == 0;
}

void stackPush(Stack* stack, Value data)
{
    Node* newNode = nodeCreate(data);
    newNode->next = stack->head;
    stack->head = newNode;
    stack->size++;
}

Value stackPop(Stack* stack)
{
    if (stackGetSize(stack) <= 0)
        return wrapNone();

    Node* previousHead = stack->head;
    Value result = previousHead->data;

    stack->head = previousHead->next;
    nodeFree(previousHead);

    stack->size--;

    return result;
}
