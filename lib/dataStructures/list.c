#include "string.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct Node {
    struct Node* next;
    void* data;
} node_t;

node_t* nodeCreate(node_t* next, void* data)
{
    node_t* node = malloc(sizeof(node_t));
    node->next = next;
    node->data = data;

    return node;
}

void nodeFree(node_t* node, void (*freeNodeData)(void*))
{
    freeNodeData(node->data);
    free(node);
}

node_t* nodeCopy(node_t* node, void* (*copyNodeData)(void*))
{
    if (!node)
        return NULL;

    return nodeCreate(nodeCopy(node->next, copyNodeData), copyNodeData(node->data));
}

typedef struct List {
    struct Node* head;
    struct Node* tail;
    int size;
    void (*freeNodeData)(void*);
} list_t;

List listCreate(void (*freeNodeData)(void*))
{
    List list = malloc(sizeof(list_t));

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->freeNodeData = freeNodeData;

    return list;
}

void listFree(List list)
{
    node_t* next = NULL;
    for (node_t* node = list->head; node; node = next) {
        next = node->next;
        nodeFree(node, list->freeNodeData);
    }

    free(list);
}

int listSize(List list)
{
    return list->size;
}

List listCopy(List list, void* (*copyNodeData)(void*))
{
    List copy = listCreate(list->freeNodeData);
    copy->size = list->size;
    copy->head = nodeCopy(list->head, copyNodeData);

    node_t* currentNode = copy->head;
    while (currentNode->next)
        currentNode = currentNode->next;
    copy->tail = currentNode;

    return copy;
}

void listPushback(List list, void* data)
{
    list->size++;

    if (!list->head) {
        list->tail = NULL;
        list->head = nodeCreate(list->tail, data);

        return;
    }

    node_t* newNode = nodeCreate(NULL, data);

    if (!list->tail) {
        list->tail = newNode;
        list->head->next = list->tail;

        return;
    }

    list->tail->next = newNode;
    list->tail = newNode;
}

String listToString(List list, char (*convertElementToChar)(void*))
{
    String result = stringDup("");

    node_t* currentNode = list->head;
    while (currentNode) {
        result = stringPush(result, convertElementToChar(currentNode->data));
        currentNode = currentNode->next;
    }

    return result;
}

void listPrint(List list, String (*formatElementData)(void*), char* separator, FILE* destination)
{
    node_t* currentNode = list->head;
    while (currentNode) {
        String s = formatElementData(currentNode->data);
        stringPrint(s, destination);
        stringFree(s);

        if (separator)
            fprintf(destination, "%s", separator);

        currentNode = currentNode->next;
    }
}

bool isValidListIndex(List list, int index)
{
    return index >= 0 && index < list->size;
}

node_t* listGet(List list, int position)
{
    if (!isValidListIndex(list, position))
        return NULL;

    node_t* node = list->head;
    for (int i = 0; i < position; i++)
        node = node->next;

    return node;
}

int listSubsequenceIndex(List list, List subsequence, bool (*compareNodeData)(void*, void*))
{
    if (subsequence->size > list->size)
        return -1;

    for (int i = 0; i < list->size - subsequence->size; i++) {
        bool isFound = true;
        for (int j = 0; j < subsequence->size; j++) {
            node_t* li = listGet(list, i + j);
            node_t* si = listGet(subsequence, j);

            if (!compareNodeData(li->data, si->data)) {
                isFound = false;
                break;
            }
        }

        if (isFound)
            return i;
    }

    return -1;
}

bool isValidListIndexToOperations(List list, int index)
{
    return index >= 0 && index <= list->size;
}

bool listDeleteNodes(List l, int fromIndex, int byIndex)
{
    if (!isValidListIndexToOperations(l, fromIndex)
        || !isValidListIndexToOperations(l, byIndex)
        || fromIndex >= byIndex) {
        return false;
    }

    node_t* currentNode = l->head;
    int i = 0;
    for (; i < fromIndex - 1; i++)
        currentNode = currentNode->next;
    node_t* beforeFromNode = currentNode;

    node_t* nextNode = NULL;
    currentNode = currentNode->next;
    for (; i < byIndex - 1; i++) {
        nextNode = currentNode->next;
        nodeFree(currentNode, l->freeNodeData);
        currentNode = nextNode;
    }
    beforeFromNode->next = nextNode;

    l->size -= byIndex - fromIndex;

    return true;
}

bool listInsertSequence(List list, List sequence, int position, void* (*copyNodeData)(void*))
{
    if (!isValidListIndexToOperations(list, position))
        return false;

    List sequenceCopy = listCopy(sequence, copyNodeData);
    if (position == 0) {
        sequenceCopy->tail->next = list->head;
        list->head = sequenceCopy->head;

        return true;
    }

    if (position == list->size) {
        list->tail->next = sequenceCopy->head;

        return true;
    }

    node_t* nodeBefore = listGet(list, position - 1);
    sequenceCopy->tail->next = nodeBefore->next;
    nodeBefore->next = sequenceCopy->head;

    list->size += sequenceCopy->size;

    return true;
}

bool listDeleteFromSequenceBySequence(
    List list,
    List fromSequence,
    List bySequence,
    bool (*compareNodeData)(void*, void*))
{
    int indexFromWhichDeleteElements = listSubsequenceIndex(list, fromSequence, compareNodeData);
    if (indexFromWhichDeleteElements < 0)
        return false;

    int indexByWhichDeleteElements
        = listSubsequenceIndex(list, bySequence, compareNodeData) + bySequence->size;
    if (indexByWhichDeleteElements < 0)
        return false;

    return listDeleteNodes(list, indexFromWhichDeleteElements, indexByWhichDeleteElements);
}

bool listInsertSequenceAfterSequence(
    List list,
    List sequenceAfter,
    List sequence,
    bool (*compareNodeData)(void*, void*),
    void* (*copyNodeData)(void*))
{
    int sequenceAfterIndex = listSubsequenceIndex(list, sequenceAfter, compareNodeData);
    if (sequenceAfterIndex < 0)
        return false;

    return listInsertSequence(list, sequence, sequenceAfterIndex + sequenceAfter->size, copyNodeData);
}

bool listReplaceSequence(
    List list,
    List sequenceToBeReplaced,
    List sequenceReplaceWith,
    bool (*compareNodeData)(void*, void*),
    void* (*copyNodeData)(void*))
{
    int indexFrom = listSubsequenceIndex(list, sequenceToBeReplaced, compareNodeData);
    if (indexFrom < 0)
        return false;

    if (!listDeleteNodes(list, indexFrom, indexFrom + sequenceToBeReplaced->size))
        return false;

    return listInsertSequence(list, sequenceReplaceWith, indexFrom, copyNodeData);
}

struct ListIterator {
    List list;
    node_t* currentNode;
};

ListIterator listIteratorCreate(List list) {
    ListIterator listIterator = malloc(sizeof(ListIterator));

    listIterator->list = list;
    listIterator->currentNode = NULL;

    return listIterator;
}

void listIteratorFree(ListIterator listIterator) {
    free(listIterator);
}

void* listIteratorGetNext(ListIterator listIterator) {
    if (!listIterator->currentNode) {
        listIterator->currentNode = listIterator->list->head;

        return listIterator->currentNode->data;
    }

    listIterator->currentNode = listIterator->currentNode->next;

    return listIterator->currentNode->data;
}

bool listIteratorHasMore(ListIterator listIterator) {
    if (!listIterator->currentNode)
        return true;

    return listIterator->currentNode->next;
}
