#include "string.h"
#include <stdbool.h>

#ifndef SPBU_C_HOMEWORKS_HASHTABLE_H
#define SPBU_C_HOMEWORKS_HASHTABLE_H

/* Dict Element type - key/value pair. */
typedef struct Element* Element;

/* Return Element key. */
String elementGetKey(Element element);

/* Returns Element value. */
void* elementGetValue(Element element);

/* Returns next Element. */
Element elementGetNext(Element element);

/* A dictionary is a reference type.
 * You should use dictFree to free up the dictionary memory. */
typedef struct Dict* Dict;

/* Create a new empty dictionary with key of type String and value of type `void*`.
 * You need to provide a function to free up the memory of dictionary values. */
Dict dictCreate(void (*freeElementValue)(void*));

/* Free dictionary memory.
 * You need to provide a function to free up the memory of dictionary values. */
void dictFree(Dict dict);

/* Returns bufferSize size of dictionary. */
int dictGetBufferSize(Dict dict);

/* Returns dictionary size. */
int dictGetSize(Dict dict);

/* Returns Dict elements List by index.
 * Returns row with index of buffer table (linked list). */
Element dictGetElementsByIndex(Dict dict, int index);

/* Insert a new key-value pair into an existing dictionary. */
void dictPut(Dict dict, String key, void* value);

/* Return the most recently inserted value associated with a key */
/* or NULL if no matching key is present. */
void* dictGet(Dict dict, String key);

/* Delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void dictDelete(Dict dict, String key);

/* Prints dictionary into [dst] output in format "key: <key> value: <value>.
 * You need to provide a function that formats the dictionary value into a String. */
void dictPrint(Dict dict, String (*convertElementValueToString)(void*), FILE* dst);

/* A DictIterator is a reference type.
 * You should use `dictIteratorFree` to free up the `DictIterator` memory. */
typedef struct DictIterator* DictIterator;

/* Creates iterator for dict. */
DictIterator dictIteratorCreate(Dict dict);

/* Free up dict iterator memory. */
void dictIteratorFree(DictIterator dictIterator);

/* Returns next element of dict or `NULL` if there isn't next element. */
Element dictIteratorGetNext(DictIterator iterator);

#endif // SPBU_C_HOMEWORKS_HASHTABLE_H
