#include "string.h"
#ifndef SPBU_C_HOMEWORKS_LIST_H
#define SPBU_C_HOMEWORKS_LIST_H

typedef struct node {
    struct node* next;
    struct node* prev;
    void* data;
} node_t;

typedef struct list {
    struct node* head;
    struct node* tail;
    int size;
} list_t;

/* A List is a reference type.
 * You should use listFree to free up the string memory. */
typedef struct list* List;

/* Creates empty list. */
List listCreate();

/* Free up list memory. */
void listFree(List l);

/* Adds an element to the end of the list. */
void listPushBack(List l, void* data);

/* Prints list to `dst` output in format "<e1><sep><e2><sep>...".
 * You need to provide a function that formats element to string and elements separator. */
void listPrint(List l, String (*elementFormatter)(void*), char* sep, FILE* dst);

/* Converts list to string.
 * You need to provide a function that formats element to char. */
String listToString(List l, char (*elementToChar)(void* element));

node_t* listGetNodeByIndex(List l, int index);
int listGetIndexAfterFirstEntrance(List source, List from, bool (*comparator)(void*, void*));
int listGetIndexBeforeFirstEntrance(List source, List from, bool (*comparator)(void*, void*));
void listDeleteSequenceFromTo(List source, List from, List to, bool (*comparator)(void*, void*));
void listInsertSequenceAfter(
    List source,
    List from,
    List to,
    bool (*comparator)(void*, void*),
    void* (*copyNodeData)(void*));
void listReplace(List source, List from, List to, bool (*comparator)(void*, void*), void* (*copyNodeData)(void*));
List listCopy(List l, void* (*copyNodeData)(void*));

#endif // SPBU_C_HOMEWORKS_LIST_H
