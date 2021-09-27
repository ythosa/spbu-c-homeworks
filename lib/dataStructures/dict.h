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
    void (*freeDictValue)(void*);
} dict_t;

/* A dictionary is a reference type.
 * You should use dictFree to free up the dictionary memory. */
typedef struct dict* Dict;

/* Create a new empty dictionary with key of type String and value of type `void*`.
 * You need to provide a function to free up the memory of dictionary values. */
Dict dictCreate(void (*freeDictValue)(void*));

/* Free dictionary memory.
 * You need to provide a function to free up the memory of dictionary values. */
void dictFree(Dict d, void (*freeDictValue)(void*));

/* Insert a new key-value pair into an existing dictionary. */
void dictPut(Dict d, String key, void* value);

/* Return the most recently inserted value associated with a key */
/* or NULL if no matching key is present. */
void* dictGet(Dict d, String key);

/* Delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void dictDelete(Dict d, String key);

/* Prints dictionary into [dst] output in format "key: <key> value: <value>.
 * You need to provide a function that formats the dictionary value into a string. */
void dictPrint(Dict d, String (*valueFormatter)(void*), FILE* dst);

#endif // SPBU_C_HOMEWORKS_HASHTABLE_H
