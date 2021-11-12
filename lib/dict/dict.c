#include "../string/string.h"
#include <assert.h>
#include <stdlib.h>

#include "dict.h"

typedef struct Element {
    struct Element* next;
    String key;
    void* value;
} element_t;

static Element elementCreate(Element next, String key, void* value)
{
    Element node = malloc(sizeof(element_t));

    node->next = next;
    node->key = key;
    node->value = value;

    return node;
}

static void elementFree(Element node, void (*freeElementValue)(void*))
{
    stringFree(node->key);
    freeElementValue(node->value);
    free(node);
}

String elementGetKey(Element element)
{
    return element->key;
}

void* elementGetValue(Element element)
{
    return element->value;
}

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)

typedef struct Dict {
    int bufferSize; // bufferSize of the pointer table
    int size; // number of elements stored
    element_t** table;
    void (*freeDictValue)(void*);
} dict_t;

Dict internalDictCreate(int size, void (*freeDictValue)(void*))
{
    Dict dict = malloc(sizeof(dict_t));

    dict->bufferSize = size;
    dict->size = 0;
    dict->table = calloc(dict->bufferSize, sizeof(element_t*));
    dict->freeDictValue = freeDictValue;

    return dict;
}

Dict dictCreate(void (*freeElementValue)(void*))
{
    return internalDictCreate(INITIAL_SIZE, freeElementValue);
}

void dictFree(Dict dict)
{
    for (int i = 0; i < dict->bufferSize; i++) {
        element_t* next = NULL;
        for (element_t* node = dict->table[i]; node; node = next) {
            next = node->next;
            elementFree(node, dict->freeDictValue);
        }
    }

    free(dict->table);
    free(dict);
}

void dictShallowFree(Dict dict)
{
    for (int i = 0; i < dict->bufferSize; i++) {
        element_t* next = NULL;
        for (element_t* node = dict->table[i]; node; node = next) {
            next = node->next;
            free(node);
        }
    }

    free(dict->table);
    free(dict);
}

int dictGetSize(Dict dict)
{
    return dict->size;
}

element_t* dictGetElementsByIndex(Dict dict, int index)
{
    return dict->table[index];
}

#define MULTIPLIER (97)

static unsigned long calculateHashOfString(String string)
{
    uint8_t* s = stringC(string);

    unsigned long hash = 0;
    for (unsigned const char* us = (unsigned const char*)s; *us; us++)
        hash = hash * MULTIPLIER + *us;

    return hash;
}

static unsigned long dictCalculateBinIndex(Dict dict, String key)
{
    return calculateHashOfString(key) % dict->bufferSize;
}

static void swapDicts(Dict first, Dict second)
{
    dict_t temp = *first;
    *first = *second;
    *second = temp;
}

static void dictGrow(Dict dict)
{
    Dict newDict = internalDictCreate(dict->bufferSize * GROWTH_FACTOR, dict->freeDictValue);

    for (int i = 0; i < dict->bufferSize; i++)
        for (element_t* element = dict->table[i]; element; element = element->next)
            dictPut(newDict, element->key, element->value);

    swapDicts(dict, newDict);
    dictShallowFree(newDict);
}

element_t* dictFind(Dict dict, String key)
{
    for (element_t* element = dict->table[dictCalculateBinIndex(dict, key)]; element; element = element->next)
        if (!stringCmp(element->key, key))
            return element;

    return NULL;
}

void* dictGet(Dict dict, String key)
{
    element_t* element = dictFind(dict, key);

    return element ? element->value : NULL;
}

void dictPut(Dict dict, String key, void* value)
{
    assert(key);

    element_t* element = dictGet(dict, key);
    if (element) {
        element->value = value;

        return;
    }

    unsigned long binIndex = dictCalculateBinIndex(dict, key);
    dict->table[binIndex] = elementCreate(dict->table[binIndex], key, value);
    dict->size++;

    if (dict->size >= dict->bufferSize * MAX_LOAD_FACTOR)
        dictGrow(dict);
}

void dictDelete(Dict dict, String key)
{
    unsigned long binIndex = dictCalculateBinIndex(dict, key);
    for (element_t** nextPointer = &dict->table[binIndex]; *nextPointer; nextPointer = &((*nextPointer)->next))
        if (!stringCmp((*nextPointer)->key, key)) {
            element_t* nodeToDelete = *nextPointer;
            *nextPointer = nodeToDelete->next;
            elementFree(nodeToDelete, dict->freeDictValue);

            return;
        }
}

void dictPrint(Dict dict, String (*convertElementValueToString)(void*), FILE* dst)
{
    DictIterator dictIterator = dictIteratorCreate(dict);
    for (Element element = dictIteratorGetNext(dictIterator); element; element = dictIteratorGetNext(dictIterator)) {
        fprintf(dst, "key: ");
        stringPrint(elementGetKey(element), dst);
        fprintf(dst, " value: ");
        String s = convertElementValueToString(elementGetValue(element));
        stringPrint(s, dst);
        stringFree(s);
        fprintf(dst, "\n");
    }
    dictIteratorFree(dictIterator);
}

typedef struct DictIterator {
    Dict dict;
    int tableRowIndex;
    element_t* currentElement;
} dictIterator_t;

DictIterator dictIteratorCreate(Dict dict)
{
    DictIterator dictIterator = malloc(sizeof(dictIterator_t));

    dictIterator->dict = dict;
    dictIterator->tableRowIndex = -1;
    dictIterator->currentElement = NULL;

    return dictIterator;
}

void dictIteratorFree(DictIterator dictIterator)
{
    free(dictIterator);
}

Element dictIteratorGetNext(DictIterator iterator)
{
    if (!iterator->currentElement || !iterator->currentElement->next)
        for (++iterator->tableRowIndex; iterator->tableRowIndex < iterator->dict->bufferSize; iterator->tableRowIndex++)
            if (dictGetElementsByIndex(iterator->dict, iterator->tableRowIndex)) {
                iterator->currentElement = dictGetElementsByIndex(iterator->dict, iterator->tableRowIndex);

                return iterator->currentElement;
            }

    iterator->currentElement = iterator->currentElement->next;

    return iterator->currentElement;
}
