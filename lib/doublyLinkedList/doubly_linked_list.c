#include "../dataStructures/string.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "doubly_linked_list.h"

typedef struct Node {
    struct node_t* next;
    struct node_t* previous;
    int data;
} Node;

node_t* nodeCreate(int data)
{
    node_t* node = malloc(sizeof(node_t));

    node->data = data;
    node->next = NULL;
    node->previous = NULL;

    return node;
}

void nodeFree(node_t* node)
{
    free(node);
}

typedef struct List {
    struct node_t* head;
    struct node_t* tail;
    int size;
} list_t;

List listCreate()
{
    List list = malloc(sizeof(list_t));

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

void listFree(List list)
{
    node_t* next = NULL;
    for (node_t* node = list->head; node; node = next) {
        next = node->next;
        nodeFree(node);
    }

    free(list);
}

int listSize(List list)
{
    return list->size;
}

void listPushback(List list, int data)
{
    node_t* newNode = nodeCreate(data);

    if (list->tail) {
        list->tail->next = newNode;
        newNode->previous = list->tail;
    } else
        list->head = newNode;
    list->tail = newNode;

    list->size++;
}

bool listIsSymmetric(List list)
{
    node_t* left = list->head;
    node_t* right = list->tail;

    while (left != right) {
        if (left->data != right->data)
            return false;
        left = left->next;
        right = right->previous;
    }

    return true;
}
