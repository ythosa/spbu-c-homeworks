#ifndef SPBU_C_HOMEWORKS_LIST_H
#define SPBU_C_HOMEWORKS_LIST_H

typedef struct node {
    struct node* next;
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

/* Prints list to `dst` output in format "<e1> <e2>...".
 * You need to provide a function that formats element to string. */
void listPrint(List l, String (*elementFormatter)(void*), FILE* dst);

#endif // SPBU_C_HOMEWORKS_LIST_H
