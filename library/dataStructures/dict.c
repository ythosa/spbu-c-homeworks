#include "string.h"
#include <assert.h>
#include <stdlib.h>

#include "dict.h"

typedef struct element {
    struct element* next;
    String key;
    String value;
} element_t;

element_t* nodeCreate(element_t* next, String key, String value)
{
    element_t* node = malloc(sizeof(element_t));
    node->next = next;
    node->key = key;
    node->value = value;

    return node;
}

void nodeFree(element_t* node)
{
    stringFree(node->key);
    stringFree(node->value);
    free(node);
}

typedef struct dict {
    int buffer; /* buffer of the pointer table */
    int size; /* number of element_t stored */
    element_t** table;
} dict_t;

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)

/* dictionary initialization code used in both dictCreate and grow */
Dict internalDictCreate(int size)
{
    Dict d = malloc(sizeof(dict_t));
    d->buffer = size;
    d->size = 0;
    d->table = malloc(d->buffer * sizeof(element_t*));

    for (int i = 0; i < d->buffer; i++) {
        d->table[i] = 0;
    }

    return d;
}

Dict dictCreate(void)
{
    return internalDictCreate(INITIAL_SIZE);
}

void dictFree(Dict d)
{
    element_t* next = NULL;

    for (int i = 0; i < d->buffer; i++) {
        for (element_t* node = d->table[i]; node != 0; node = next) {
            next = node->next;
            nodeFree(node);
        }
    }

    free(d->table);
    free(d);
}

void swapDicts(Dict first, Dict second)
{
    dict_t temp = *first;
    *first = *second;
    *second = temp;
}

#define MULTIPLIER (97)

static unsigned long hashFunction(const char* s)
{
    unsigned long hash = 0;

    for (unsigned const char* us = (unsigned const char*)s; *us; us++) {
        hash = hash * MULTIPLIER + *us;
    }

    return hash;
}

static void grow(Dict d)
{
    Dict newDict = internalDictCreate(d->buffer * GROWTH_FACTOR);

    for (int i = 0; i < d->buffer; i++) {
        for (element_t* e = d->table[i]; e != 0; e = e->next) {
            dictPut(newDict, e->key, e->value);
        }
    }
    swapDicts(d, newDict);

    dictFree(newDict);
}

/* insert a new key-value pair into an existing dictionary */
void dictPut(Dict d, String key, String value)
{
    assert(key);
    assert(value);

    unsigned long h = hashFunction(stringToC(key)) % d->buffer;

    element_t* e = nodeCreate(d->table[h], key, value);
    d->table[h] = e;
    d->size++;

    /* grow table if there is not enough room */
    if (d->size >= d->buffer * MAX_LOAD_FACTOR) {
        grow(d);
    }
}

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
String dictGet(Dict d, String key)
{
    for (element_t* e = d->table[hashFunction(stringToC(key)) % d->buffer]; e; e = e->next) {
        if (!stringCompare(e->key, key)) {
            return e->value;
        }
    }

    return NULL;
}

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void dictDelete(Dict d, String key)
{
    element_t* nodeToDelete = NULL;

    for (element_t** prev = &(d->table[hashFunction(stringToC(key)) % d->buffer]);
         *prev != 0;
         prev = &((*prev)->next)) {

        if (!stringCompare((*prev)->key, key)) {
            nodeToDelete = *prev;
            *prev = nodeToDelete->next;
            nodeFree(nodeToDelete);

            return;
        }
    }
}
