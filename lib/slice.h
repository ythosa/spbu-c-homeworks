#ifndef SPBU_C_HOMEWORKS_SLICE_H
#define SPBU_C_HOMEWORKS_SLICE_H

#include <stdbool.h>
#include <stdlib.h>

typedef void (*Destructor)(void*);
typedef int (*Comparator)(void*, void*);

typedef struct Slice Slice;
Slice* sliceCreate(size_t elementSize, Destructor elementDestructor);
void sliceFree(Slice* list);

void* sliceGet(Slice* list, int index);
void* sliceSet(Slice* list, int index, void* value);
bool sliceAdd(Slice* list, void* value);
int sliceGetSize(Slice* list);
void sliceSort(Slice* list, Comparator comparator);

#endif // SPBU_C_HOMEWORKS_SLICE_H
