#include "string.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct node {
    struct node* next;
    void* data;
} node_t;

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

node_t* nodeCopy(node_t* node, void* (*copyNodeData)(void*))
{
    if (!node) {
        return NULL;
    }

    return nodeCreate(
        nodeCopy(node->next, copyNodeData),
        copyNodeData(node->data));
}

typedef struct list {
    struct node* head;
    struct node* tail;
    int size;
} list_t;

List listCreate()
{
    List l = malloc(sizeof(list_t));
    l->size = 0;
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

int listSize(List l)
{
    return l->size;
}

List listCpy(List l, void* (*copyNodeData)(void*))
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

bool listInsert(List l, int position, void* data)
{
    if (position < 0 || position > l->size - 1) {
        return false;
    }

    node_t* newNode = nodeCreate(NULL, data);
    if (l->head == NULL) {
        if (position == 0) {
            l->head = newNode;
            l->tail = newNode;
            l->size++;

            return true;
        }

        return false;
    }

    l->size++;

    if (position == 0) {
        newNode->next = l->head;
        l->head = newNode;

        return true;
    }

    if (position == l->size - 1) {
        l->tail->next = newNode;
        l->tail = newNode;

        return true;
    }

    node_t* nodeBefore = l->head;
    for (int i = 0; i < position - 1; i++) {
        nodeBefore = nodeBefore->next;
    }
    node_t* nodeAfter = nodeBefore->next;
    nodeBefore->next = newNode;
    newNode->next = nodeAfter;

    return true;
}

void listPushback(List l, void* data)
{
    l->size++;

    if (!l->head) {
        l->tail = NULL;
        l->head = nodeCreate(l->tail, data);

        return;
    }

    node_t* newNode = nodeCreate(NULL, data);

    if (!l->tail) {
        l->tail = newNode;
        l->head->next = l->tail;

        return;
    }

    l->tail->next = newNode;
    l->tail = newNode;
}

String listToString(List l, char (*elementToChar)(void*))
{
    String result = stringDup("");

    node_t* n = l->head;
    while (n) {
        char c = elementToChar(n->data);
        result = stringPush(result, c);
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

bool isValidListIndexToOperations(List l, int index)
{
    return index >= 0 && index <= l->size;
}

node_t* listGet(List l, int position)
{
    if (!isValidListIndexToOperations(l, position)) {
        return NULL;
    }

    node_t* node = l->head;
    for (int i = 0; i < position; i++) {
        node = node->next;
    }

    return node;
}

int listSubseqIndex(List l, List subseq, bool (*comparator)(void*, void*))
{
    if (subseq->size > l->size) {
        return -1;
    }

    for (int i = 0; i < l->size - subseq->size; i++) {
        bool isFound = true;
        for (int j = 0; j < subseq->size; j++) {
            node_t* li = listGet(l, i + j);
            node_t* si = listGet(subseq, j);

            if (!comparator(li->data, si->data)) {
                isFound = false;
                break;
            }
        }

        if (isFound) {
            return i;
        }
    }

    return -1;
}

bool listDeleteNodes(List l, int fromPos, int toPos)
{
    if (!isValidListIndexToOperations(l, fromPos)
        || !isValidListIndexToOperations(l, toPos)
        || fromPos > toPos) {
        return false;
    }

    node_t* curNode = l->head;
    int i = 0;
    for (; i < fromPos - 1; i++) {
        curNode = curNode->next;
    }
    node_t* beforeFromNode = curNode;

    node_t* nextNode;
    curNode = curNode->next;
    for (; i < toPos - 1; i++) {
        nextNode = curNode->next;
        nodeFree(curNode);
        curNode = nextNode;
    }
    beforeFromNode->next = nextNode;

    l->size -= toPos - fromPos;

    return true;
}

bool listInsertSubseq(List l, List subseq, int position, void* (*copyNodeData)(void*))
{
    if (!isValidListIndexToOperations(l, position)) {
        return false;
    }

    List subseqCopy = listCpy(subseq, copyNodeData);
    if (position == 0) {
        subseqCopy->tail->next = l->head;
        l->head = subseqCopy->head;

        return true;
    }

    if (position == l->size) {
        l->tail->next = subseqCopy->head;

        return true;
    }

    node_t* nodeBefore = listGet(l, position - 1);
    subseqCopy->tail->next = nodeBefore->next;
    nodeBefore->next = subseqCopy->head;

    l->size += subseq->size;

    return true;
}

bool listDeleteFromToSeqs(List l, List lseq, List rseq, bool (*comparator)(void*, void*))
{
    int indexFrom = listSubseqIndex(l, lseq, comparator);
    if (indexFrom < 0) {
        return false;
    }

    int indexTo = listSubseqIndex(l, rseq, comparator) + rseq->size;
    if (indexTo < 0) {
        return false;
    }

    return listDeleteNodes(l, indexFrom, indexTo);
}

bool listInsertSeqAfterSeq(
    List l,
    List after,
    List seq,
    bool (*comparator)(void*, void*),
    void* (*copyNodeData)(void*))
{
    int afterIndex = listSubseqIndex(l, after, comparator);
    if (afterIndex < 0) {
        return false;
    }

    return listInsertSubseq(l, seq, afterIndex + after->size, copyNodeData);
}

bool listReplace(
    List l,
    List from,
    List to,
    bool (*comparator)(void*, void*),
    void* (*copyNodeData)(void*))
{
    int indexFrom = listSubseqIndex(l, from, comparator);
    if (indexFrom < 0) {
        return false;
    }

    if (!listDeleteNodes(l, indexFrom, indexFrom + from->size)) {
        return false;
    }

    return listInsertSubseq(l, to, indexFrom, copyNodeData);
}
