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
    node_t* newNode = nodeCreate(NULL, data);
    if (list->tail)
        list->tail->next = newNode;
    else
        list->head = newNode;
    list->tail = newNode;

    list->size++;
}

String listToString(List list, char (*convertElementToChar)(void*))
{
    char* resultBuffer = calloc(sizeof(char), list->size + 1);

    node_t* currentNode = list->head;
    int i = 0;
    while (currentNode) {
        resultBuffer[i] = convertElementToChar(currentNode->data);
        currentNode = currentNode->next;
        i++;
    }
    resultBuffer[list->size] = '\0';

    String resultString = stringDup(resultBuffer);
    free(resultBuffer);

    return resultString;
}

void listPrint(List list, String (*formatElementData)(void*), String separator, FILE* destination)
{
    node_t* currentNode = list->head;
    while (currentNode) {
        String s = formatElementData(currentNode->data);
        stringPrint(s, destination);
        stringFree(s);

        if (separator)
            stringPrint(separator, destination);

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

int listSubsequenceIndexFromIndex(List list, int fromIndex, List subsequence, bool (*compareNodeData)(void*, void*))
{
    if (subsequence->size > list->size && !isValidListIndex(list, fromIndex))
        return -1;

    node_t* listCurrentNode = listGet(list, fromIndex);
    int i = fromIndex;
    while (listCurrentNode) {
        bool isFound = true;
        node_t* subsequenceCurrentNode = subsequence->head;
        node_t* listCurrentNodeCopy = listCurrentNode;
        while (subsequenceCurrentNode && listCurrentNodeCopy) {
            if (!compareNodeData(listCurrentNodeCopy->data, subsequenceCurrentNode->data)) {
                isFound = false;

                break;
            }

            subsequenceCurrentNode = subsequenceCurrentNode->next;
            listCurrentNodeCopy = listCurrentNodeCopy->next;
        }

        if (isFound && !subsequenceCurrentNode)
            return i;

        listCurrentNode = listCurrentNode->next;
        i++;
    }

    return -1;
}

int listSubsequenceIndex(List list, List subsequence, bool (*compareNodeData)(void*, void*))
{
    return listSubsequenceIndexFromIndex(list, 0, subsequence, compareNodeData);
}

bool isValidListIndexToOperations(List list, int index)
{
    return index >= 0 && index <= list->size;
}

bool listDeleteNodes(List list, int fromIndex, int toIndex)
{
    if (!isValidListIndexToOperations(list, fromIndex)
        || !isValidListIndexToOperations(list, toIndex)
        || fromIndex >= toIndex) {
        return false;
    }

    node_t* beforeFromNode = fromIndex > 0 ? listGet(list, fromIndex - 1) : NULL;
    node_t* nextNode = NULL;
    node_t* currentNode = beforeFromNode ? beforeFromNode->next : list->head;
    for (int i = fromIndex; i < toIndex; i++) {
        nextNode = currentNode->next;
        nodeFree(currentNode, list->freeNodeData);
        currentNode = nextNode;
    }

    if (!beforeFromNode && !nextNode) {
        // head and tail deleted -> empty list
        list->head = NULL;
        list->tail = NULL;
    } else if (!beforeFromNode) {
        // head deleted
        list->head = nextNode;
    } else if (!nextNode) {
        // tail deleted
        beforeFromNode->next = NULL;
        list->tail = beforeFromNode;
    } else
        beforeFromNode->next = nextNode;

    list->size -= toIndex - fromIndex;

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
        if (!list->tail)
            list->tail = sequenceCopy->tail;
    } else if (position == list->size) {
        list->tail->next = sequenceCopy->head;
        list->tail = sequenceCopy->tail;
    } else {
        node_t* nodeBefore = listGet(list, position - 1);
        sequenceCopy->tail->next = nodeBefore->next;
        nodeBefore->next = sequenceCopy->head;
    }

    list->size += sequenceCopy->size;
    free(sequenceCopy);

    return true;
}

bool listDeleteFromSequenceToSequence(
    List list,
    List fromSequence,
    List toSequence,
    bool (*compareNodeData)(void*, void*))
{
    int indexFromWhichDeleteElements = listSubsequenceIndex(list, fromSequence, compareNodeData);
    if (indexFromWhichDeleteElements < 0)
        return false;

    int indexToWhichDeleteElements = listSubsequenceIndexFromIndex(
                                         list,
                                         indexFromWhichDeleteElements + fromSequence->size,
                                         toSequence,
                                         compareNodeData)
        + toSequence->size;
    if (indexToWhichDeleteElements < 0)
        return false;

    return listDeleteNodes(list, indexFromWhichDeleteElements, indexToWhichDeleteElements);
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

typedef struct ListIterator {
    List list;
    node_t* currentNode;
} listIterator_t;

ListIterator listIteratorCreate(List list)
{
    ListIterator listIterator = malloc(sizeof(listIterator_t));

    listIterator->list = list;
    listIterator->currentNode = NULL;

    return listIterator;
}

void listIteratorFree(ListIterator listIterator)
{
    free(listIterator);
}

void* listIteratorGetNext(ListIterator listIterator)
{
    if (!listIterator->currentNode) {
        listIterator->currentNode = listIterator->list->head;

        return listIterator->currentNode->data;
    }

    listIterator->currentNode = listIterator->currentNode->next;

    return listIterator->currentNode->data;
}

bool listIteratorHasMore(ListIterator listIterator)
{
    if (!listIterator->currentNode)
        return true;

    return listIterator->currentNode->next;
}
