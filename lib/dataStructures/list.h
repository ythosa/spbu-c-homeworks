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

typedef struct list* List;

List listCreate();
void listFree(List l);
void listPushBack(List l, void* data);
void listPrint(List l, String (*elementFormatter)(void*), FILE* dst);

#endif // SPBU_C_HOMEWORKS_LIST_H
