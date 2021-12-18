#include <stdlib.h>

#include "stack.h"

typedef struct StackNode StackNode;

struct StackNode {
    void* data;
    StackNode* nextNode;
};

static StackNode* createNode(void* data)
{
    StackNode* node = malloc(sizeof(StackNode));

    node->data = data;
    node->nextNode = NULL;

    return node;
}

static void freeNode(StackNode* node, Destructor dataDestructor)
{
    dataDestructor(node);
    free(node);
}

struct Stack {
    int size;
    StackNode* head;
    Destructor dataDestructor;
};

Stack* stackCreate(Destructor dataDestructor)
{
    Stack* stack = malloc(sizeof(Stack));

    stack->size = 0;
    stack->head = NULL;
    stack->dataDestructor = dataDestructor;

    return stack;
}

void stackFree(Stack* stack)
{
    while (stack->head) {
        StackNode* newHead = stack->head;
        freeNode(stack->head, stack->dataDestructor);
        stack->head = newHead;
    }

    free(stack);
}

void stackPush(Stack* stack, void* data)
{
    StackNode* node = createNode(data);

    node->nextNode = stack->head;
    stack->head = node;

    stack->size++;
}

void* stackPop(Stack* stack)
{
    if (!stack->size)
        return NULL;

    StackNode* previousHead = stack->head;
    void* previousHeadData = previousHead->data;
    stack->head = previousHead->nextNode;
    free(previousHead);

    return previousHeadData;
}
