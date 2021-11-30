#ifndef SPBU_C_HOMEWORKS_ARRAYLIST_H
#define SPBU_C_HOMEWORKS_ARRAYLIST_H

#include "../values/values.h"

typedef struct ArrayList ArrayList;

ArrayList* arrayListCreate();
void arrayListFree(ArrayList* list);

int arrayListGetSize(ArrayList* list);

Value arrayListGet(ArrayList* list, int index);
bool arrayListSet(ArrayList* list, int index, Value value);
bool arrayListAdd(ArrayList* list, Value value);
int arrayListFind(ArrayList* list, Value key, Comparator comparator);

typedef struct ArrayListIterator ArrayListIterator;

ArrayListIterator* arrayListIteratorCreate(ArrayList* list);
Value arrayListIteratorGetValue(ArrayListIterator* iterator);
ArrayListIterator* arrayListIteratorNext(ArrayListIterator* iterator);

#endif // SPBU_C_HOMEWORKS_ARRAYLIST_H
