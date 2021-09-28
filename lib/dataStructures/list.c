#include "string.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

node_t* nodeCreate(node_t* next, node_t* prev, void* data)
{
    node_t* n = malloc(sizeof(node_t));
    n->next = next;
    n->prev = prev;
    n->data = data;

    return n;
}

void nodeFree(node_t* node)
{
    free(node->data);
    free(node);
}

node_t* nodeCopy(node_t* node, void* (*copyNodeData)(void*))
{
    if (!node) {
        return NULL;
    }

    return nodeCreate(
        nodeCopy(node->next, copyNodeData),
//        nodeCopy(node->prev, copyNodeData),
        NULL,
        copyNodeData(node->data));
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

List listCopy(List l, void* (*copyNodeData)(void*))
{
    List copy = listCreate();
    copy->size = l->size;
    copy->head = nodeCopy(l->head, copyNodeData);

    node_t* n = copy->head;
    while (n->next) {
        n = n->next;
    }
    copy->tail = n;

    return copy;
}

void listPushBack(List l, void* data)
{
    l->size++;

    if (!l->head) {
        l->tail = NULL;
        l->head = nodeCreate(l->tail, NULL, data);

        return;
    }

    node_t* newNode = nodeCreate(NULL, NULL, data);

    if (!l->tail) {
        l->tail = newNode;
        l->tail->prev = l->head;
        l->head->next = l->tail;

        return;
    }

    newNode->prev = l->tail;
    l->tail->next = newNode;
    l->tail = newNode;
}

String listToString(List l, char (*elementToChar)(void*))
{
    String result = stringDup("");

    node_t* n = l->head;
    while (n) {
        char c = elementToChar(n->data);
        result = stringPushChar(result, c);
        n = n->next;
    }

    return result;
}

void listPrint(List l, String (*elementFormatter)(void*), char* sep, FILE* dst)
{
    node_t* n = l->head;
    while (n) {
        String s = elementFormatter(n->data);
        stringPrint(s, dst);
        stringFree(s);

        if (sep) {
            fprintf(dst, "%s", sep);
        }

        n = n->next;
    }
}

node_t* listGetNodeByIndex(List l, int index)
{
    node_t* n = l->head;
    for (int i = 0; i < index; i++) {
        n = n->next;
    }

    return n;
}

int listGetIndexAfterFirstEntrance(List source, List from, bool (*comparator)(void*, void*))
{
    int indexFrom = 0;

    for (int i = from->size - 1; i < source->size; i++) {
        bool isFound = true;
        for (int j = i, k = from->size - 1; j >= i - (from->size - 1); j--, k--) {
            node_t* sn = listGetNodeByIndex(source, j);
            node_t* fn = listGetNodeByIndex(from, k);
            if (!comparator(sn->data, fn->data)) {
                isFound = false;
                break;
            }
        }

        if (isFound) {
            indexFrom = i + 1;
            break;
        }
    }

    return indexFrom;
}

int listGetIndexBeforeFirstEntrance(List source, List from, bool (*comparator)(void*, void*))
{
    return listGetIndexAfterFirstEntrance(source, from, comparator) - from->size - 1;
}

void listDeleteSequenceFromTo(List source, List from, List to, bool (*comparator)(void*, void*))
{
    int indexAfterFrom = listGetIndexAfterFirstEntrance(source, from, comparator);
    int indexBeforeTo = listGetIndexBeforeFirstEntrance(source, to, comparator);
    node_t* nodeAfterFrom = listGetNodeByIndex(source, indexAfterFrom);
    node_t* nodeBeforeTo = listGetNodeByIndex(source, indexBeforeTo);

    source->size -= indexBeforeTo - indexAfterFrom + 1;
    nodeAfterFrom->prev->next = nodeBeforeTo->next;
    nodeBeforeTo->next->prev = nodeAfterFrom->prev;

    node_t* next = NULL;
    for (node_t* node = nodeAfterFrom; node != nodeBeforeTo; node = next) {
        next = node->next;
        nodeFree(node);
    }
    nodeFree(nodeBeforeTo);
}

void listInsertSequenceAfter(List source, List from, List to, bool (*comparator)(void*, void*), void* (*copyNodeData)(void*))
{
    source->size += from->size;

    int indexAfterFrom = listGetIndexAfterFirstEntrance(source, from, comparator);
    node_t* nodeAfterFrom = listGetNodeByIndex(source, indexAfterFrom);

    List toCopy = listCopy(to, copyNodeData);
    nodeAfterFrom->prev->next = toCopy->head;
    toCopy->head->prev = nodeAfterFrom->prev;
    toCopy->tail->next = nodeAfterFrom;
    nodeAfterFrom->prev = toCopy->tail;
}

void listReplace(List source, List from, List to, bool (*comparator)(void*, void*), void* (*copyNodeData)(void*)) {
    source->size += from->size - to->size;

    int indexAfterFrom = listGetIndexAfterFirstEntrance(source, from, comparator);
    int indexBeforeTo = listGetIndexBeforeFirstEntrance(source, to, comparator);
    node_t* nodeAfterFrom = listGetNodeByIndex(source, indexAfterFrom);
    node_t* nodeBeforeTo = listGetNodeByIndex(source, indexBeforeTo);

    node_t* next = NULL;
    for (node_t* n = nodeBeforeTo->next; n != nodeAfterFrom; n = next) {
        next = n->next;
        nodeFree(n);
    }

    List toCopy = listCopy(to, copyNodeData);
    nodeBeforeTo->next = toCopy->head;
    toCopy->head->prev = nodeBeforeTo;
    nodeAfterFrom->prev = toCopy->tail;
    toCopy->tail->next = nodeAfterFrom;
}
