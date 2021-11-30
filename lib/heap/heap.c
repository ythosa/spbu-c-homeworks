#include "heap.h"
#include "../arrayList/arrayList.h"
#include "stdlib.h"
#include <stdio.h>

struct Heap {
    int size;
    ArrayList* data;
    Comparator comparator;
};

Heap* heapCreate(Comparator comparator)
{
    Heap* h = malloc(sizeof(Heap));

    h->size = 0;
    h->data = arrayListCreate();
    h->comparator = comparator;

    return h;
}

void heapFree(Heap* h)
{
    arrayListFree(h->data);
    free(h);
}

int heapGetSize(Heap* h)
{
    return h->size;
}

static int getParent(int index)
{
    return (index - 1) / 2;
}

static int getLeftChild(int index)
{
    return 2 * index + 1;
}

static int getRightChild(int index)
{
    return 2 * index + 2;
}

static void swapElements(Heap* h, int firstIndex, int secondIndex)
{
    Value first = arrayListGet(h->data, firstIndex);
    Value second = arrayListGet(h->data, secondIndex);

    arrayListSet(h->data, firstIndex, second);
    arrayListSet(h->data, secondIndex, first);
}

static void siftUp(Heap* h, int index)
{
    while (
        h->comparator(arrayListGet(h->data, index), arrayListGet(h->data, getParent(index))) < 0
        && index > 0) {
        swapElements(h, index, getParent(index));
        index = getParent(index);
    }
}

static void siftDown(Heap* h, int index)
{
    while (true) {
        int indexOfMinChild = index;

        if (getLeftChild(index) < h->size
            && h->comparator(arrayListGet(h->data, getLeftChild(index)), arrayListGet(h->data, indexOfMinChild)) < 0)
            indexOfMinChild = getLeftChild(index);

        if (getRightChild(index) < h->size
            && h->comparator(arrayListGet(h->data, getRightChild(index)), arrayListGet(h->data, indexOfMinChild)) < 0)
            indexOfMinChild = getRightChild(index);

        if (index == indexOfMinChild)
            break;

        swapElements(h, index, indexOfMinChild);

        index = indexOfMinChild;
    }
}

void heapPrint(Heap* h)
{
    for (int i = 0; i < h->size; i++) {
        printf("%d ", getInt(arrayListGet(h->data, i)));
    }
    printf("\n");
}

void heapInsert(Heap* h, Value value)
{
    arrayListSet(h->data, h->size++, value);
    siftUp(h, h->size - 1);
}

Value heapRemoveMin(Heap* h)
{
    if (h->size == 0)
        return wrapNone();

    Value result = arrayListGet(h->data, 0);

    arrayListSet(h->data, 0, arrayListGet(h->data, --h->size));
    siftDown(h, 0);

    return result;
}

Value heapUpdate(Heap* h, Value from, Value to, Comparator comparator)
{
    for (int i = 0; i < h->size; i++) {
        Value node = arrayListGet(h->data, i);
        if (comparator(node, from) == 0) {
            arrayListSet(h->data, i, to);
            siftUp(h, i);

            return node;
        }
    }

    return wrapNone();
}
