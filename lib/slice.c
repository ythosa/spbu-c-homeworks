#include "slice.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 16

struct Slice {
    int* data;
    int capacity;
    int size;
};

Slice* sliceCreate(size_t elementSize)
{
    Slice* list = malloc(sizeof(Slice));

    if (!list)
        return NULL;
    list->capacity = INITIAL_SIZE;
    list->size = 0;
    list->data = malloc(INITIAL_SIZE * elementSize);
    if (!list->data) {
        free(list);
        return NULL;
    }

    return list;
}
void sliceFree(Slice* list)
{
    free(list->data);
    free(list);
}

bool increaseCapacity(Slice* list)
{
    int buffer = realloc(list->data, 2 * list->capacity * sizeof(int));
    if (buffer) {
        list->capacity *= 2;
        list->data = buffer;
    }

    return buffer;
}

int sliceGet(Slice* list, int index)
{
    assert(index >= 0 && index < list->size);

    return list->data[index];
}

bool sliceSet(Slice* list, int index, int value)
{
    if (index < 0 || index > list->size)
        return false;

    if (index == list->size) {
        sliceAdd(list, value);

        return NULL;
    }

    int previousValue = list->data[index];
    list->data[index] = value;

    return previousValue;
}

bool sliceAdd(Slice* list, int value)
{
    if (list->size == list->capacity && !increaseCapacity(list)) {
        return false;
    }
    list->data[list->size++] = value;

    return true;
}

int sliceGetSize(Slice* list)
{
    return list->size;
}

int compareInt(const void* first, const void* second)
{
    return *(int*)first - *(int*)second;
}

void sliceSort(Slice* list)
{
    qsort(list->data, list->size, sizeof(int), compareInt);
}
