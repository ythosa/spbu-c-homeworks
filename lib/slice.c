#include "slice.h"

#include <stdlib.h>

#define INITIAL_SIZE 16

struct Slice {
    void** data;
    int capacity;
    int size;
    size_t elementSize;
    Destructor elementDestructor;
};

Slice* sliceCreate(size_t elementSize, Destructor elementDestructor)
{
    Slice* list = malloc(sizeof(Slice));

    if (!list)
        return NULL;
    list->capacity = INITIAL_SIZE;
    list->size = 0;
    list->elementSize = elementSize;
    list->elementDestructor = elementDestructor;
    list->data = malloc(INITIAL_SIZE * elementSize);
    if (!list->data) {
        free(list);
        return NULL;
    }

    return list;
}
void sliceFree(Slice* list)
{
    for (int i = 0; i < list->size; i++)
        list->elementDestructor(list->data[i]);
    free(list->data);
    free(list);
}

bool increaseCapacity(Slice* list)
{
    void* buffer = realloc(list->data, 2 * list->capacity * sizeof(list->elementSize));
    if (buffer) {
        list->capacity *= 2;
        list->data = buffer;
    }

    return buffer;
}

void* sliceGet(Slice* list, int index)
{
    if (index < 0 || index >= list->size)
        return NULL;
    return list->data[index];
}

void* sliceSet(Slice* list, int index, void* value)
{
    if (index < 0 || index > list->size)
        return false;

    if (index == list->size) {
        sliceAdd(list, value);

        return NULL;
    }

    void* previousValue = list->data[index];
    list->data[index] = value;

    return previousValue;
}

bool sliceAdd(Slice* list, void* value)
{
    if (list->size == list->capacity && !increaseCapacity(list))
        return false;
    list->data[list->size++] = value;
    return true;
}

int sliceGetSize(Slice* list)
{
    return list->size;
}
