#include "string.h"
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

node_t* nodeCreate(node_t* next, void* data)
{
    node_t* n = malloc(sizeof(node_t));
    n->next = next;
    n->data = data;

    return n;
}

void nodeFree(node_t* node)
{
    free(node->data);
    free(node);
}

List listCreate()
{
    List l = malloc(sizeof(list_t));
    l->head = NULL;
    l->tail = NULL;

    return l;
}

void listFree(List l)
{
    node_t* next = NULL;
    for (node_t* node = l->head; node != NULL; node = next) {
        next = node->next;
        nodeFree(node);
    }

    free(l);
}

void listPushBack(List l, void* data)
{
    l->size++;
    node_t* newNode = nodeCreate(NULL, data);

    if (!l->head) {
        l->tail = NULL;
        l->head = nodeCreate(l->tail, data);

        return;
    }

    if (!l->tail) {
        l->tail = newNode;
        l->head->next = l->tail;

        return;
    }

    l->tail->next = newNode;
    l->tail = newNode;
}

void listOfIntPrint(List l, FILE* dst)
{
    node_t* n = l->head;
    while (n) {
        fprintf(dst, "%d", *(int*)n->data);
        n = n->next;
    }
}

void listOfStringPrint(List l, FILE* dst)
{
    node_t* n = l->head;
    while (n) {
        fprintf(dst, "%s ", (char*)n->data);
        n = n->next;
    }
}
