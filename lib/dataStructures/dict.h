#include "string.h"
#include <stdbool.h>

#ifndef SPBU_C_HOMEWORKS_HASHTABLE_H
#define SPBU_C_HOMEWORKS_HASHTABLE_H

typedef struct element {
    struct element* next;
    String key;
    void* value;
} element_t;

typedef struct dict {
    int buffer; // buffer of the pointer table
    int size; // number of elements stored
    element_t** table;
} dict_t;

typedef struct dict* Dict;

/* create a new empty dictionary */
Dict dictCreate(void);

/* destroy a dictionary */
void dictFree(Dict d);

/* insert a new key-value pair into an existing dictionary */
void dictPut(Dict d, String key, void* value);

/* return the most recently inserted value associated with a key */
/* or NULL if no matching key is present */
void* dictGet(Dict d, String key);

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void dictDelete(Dict d, String key);

/* prints dictionary into std output */
void dictIntPrint(Dict d, FILE* dst);

#endif // SPBU_C_HOMEWORKS_HASHTABLE_H