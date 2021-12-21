#ifndef SPBU_C_HOMEWORKS_SLICE_H
#define SPBU_C_HOMEWORKS_SLICE_H

#include <stdbool.h>
#include <stdlib.h>

typedef int (*Comparator)(int, int);

typedef struct Slice Slice;
Slice* sliceCreate(size_t elementSize);
void sliceFree(Slice* list);

int sliceGet(Slice* list, int index);
bool sliceSet(Slice* list, int index, int value);
bool sliceAdd(Slice* list, int value);
int sliceGetSize(Slice* list);
void sliceSort(Slice* list);

#endif // SPBU_C_HOMEWORKS_SLICE_H
