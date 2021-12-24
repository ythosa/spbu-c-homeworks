#include "../dataStructures/string.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "doubly_linked_list.h"

typedef struct Node {
    struct Node* next;
    struct Node* previous;
    int data;
} Node;

Node* nodeCreate(int data)
{
    Node* node = malloc(sizeof(Node));

    node->data = data;
    node->next = NULL;
    node->previous = NULL;

    return node;
}

void nodeFree(Node* node)
{
    free(node);
}

typedef struct List {
    struct Node* head;
    struct Node* tail;
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
    Node* next = NULL;
    for (Node* node = list->head; node; node = next) {
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
    Node* newNode = nodeCreate(data);

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
    Node* left = list->head;
    Node* right = list->tail;

    while (left != right) {
        if (left->data != right->data)
            return false;
        left = left->next;
        right = right->previous;
    }

    return true;
}
