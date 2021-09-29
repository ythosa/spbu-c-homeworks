#include "string.h"
#include <assert.h>
#include <stdlib.h>

#include "dict.h"

element_t* elementCreate(element_t* next, String key, void* value)
{
    element_t* node = malloc(sizeof(element_t));
    node->next = next;
    node->key = key;
    node->value = value;

    return node;
}

void elementFree(element_t* node, void (*freeDictValue)(void*))
{
    stringFree(node->key);
    freeDictValue(node->value);
    free(node);
}

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)

Dict internalDictCreate(int size, void (*freeDictValue)(void*))
{
    Dict d = malloc(sizeof(dict_t));
    d->freeDictValue = freeDictValue;
    d->buffer = size;
    d->size = 0;
    d->table = malloc(d->buffer * sizeof(element_t*));

    for (int i = 0; i < d->buffer; i++) {
        d->table[i] = NULL;
    }

    return d;
}

Dict dictCreate(void (*freeDictValue)(void*))
{
    return internalDictCreate(INITIAL_SIZE, freeDictValue);
}

void dictFree(Dict d, void (*freeDictValue)(void*))
{
    element_t* next = NULL;

    for (int i = 0; i < d->buffer; i++) {
        for (element_t* node = d->table[i]; node != NULL; node = next) {
            next = node->next;
            elementFree(node, freeDictValue);
        }
    }

    free(d->table);
    free(d);
}

#define MULTIPLIER (97)

static unsigned long hashFunction(String string)
{
    uint8_t* s = stringC(string);
    unsigned long hash = 0;

    for (unsigned const char* us = (unsigned const char*)s; *us; us++) {
        hash = hash * MULTIPLIER + *us;
    }

    return hash;
}

void swapDicts(Dict first, Dict second)
{
    dict_t temp = *first;
    *first = *second;
    *second = temp;
}

static void grow(Dict d)
{
    Dict newDict = internalDictCreate(d->buffer * GROWTH_FACTOR, d->freeDictValue);

    for (int i = 0; i < d->buffer; i++) {
        for (element_t* e = d->table[i]; e != 0; e = e->next) {
            dictPut(newDict, e->key, e->value);
        }
    }
    swapDicts(d, newDict);

    dictFree(newDict, d->freeDictValue);
}

void dictPut(Dict d, String key, void* value)
{
    assert(key);
    assert(value);

    unsigned long h = hashFunction(key) % d->buffer;

    bool isElementWithSuchKeyExists = false;
    for (element_t* e = d->table[h]; e != NULL; e = e->next) {
        if (stringCmp(e->key, key) == 0) {
            e->value = value;
            isElementWithSuchKeyExists = true;
            break;
        }
    }

    if (!isElementWithSuchKeyExists) {
        element_t* e = elementCreate(d->table[h], key, value);
        d->table[h] = e;
        d->size++;
    }

    if (d->size >= d->buffer * MAX_LOAD_FACTOR) {
        grow(d);
    }
}

void* dictGet(Dict d, String key)
{
    for (element_t* e = d->table[hashFunction(key) % d->buffer]; e; e = e->next) {
        if (!stringCmp(e->key, key)) {
            return e->value;
        }
    }

    return NULL;
}

void dictDelete(Dict d, String key)
{
    element_t* nodeToDelete = NULL;

    for (
        element_t** prev = &(d->table[hashFunction(key) % d->buffer]);
        *prev != NULL;
        prev = &((*prev)->next)) {

        if (!stringCmp((*prev)->key, key)) {
            nodeToDelete = *prev;
            *prev = nodeToDelete->next;
            elementFree(nodeToDelete, d->freeDictValue);

            return;
        }
    }
}

void dictPrint(Dict d, String (*valueFormatter)(void*), FILE* dst)
{
    for (int i = 0; i < d->buffer; i++) {
        for (element_t* e = d->table[i]; e != NULL; e = e->next) {
            fprintf(dst, "key: ");
            stringPrint(e->key, dst);
            fprintf(dst, " value: ");
            String s = valueFormatter(e->value);
            stringPrint(s, dst);
            stringFree(s);
            fprintf(dst, "\n");
        }
    }
}
