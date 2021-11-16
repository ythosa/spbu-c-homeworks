#ifndef SPBU_C_HOMEWORKS_HEAP_H
#define SPBU_C_HOMEWORKS_HEAP_H

#include "../values/values.h"

typedef struct Heap Heap;

Heap* heapCreate(Comparator);
void heapFree(Heap* h);

void heapPrint(Heap*);

int heapGetSize(Heap* h);

void heapInsert(Heap* h, Value value);
Value heapRemoveMin(Heap* h);
Value heapUpdate(Heap* h, Value from, Value to, Comparator comparator);

#endif // SPBU_C_HOMEWORKS_HEAP_H
