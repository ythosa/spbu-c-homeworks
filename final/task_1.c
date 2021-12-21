#include <stdio.h>

#include "../lib/slice.h"

int compareFunction(const void* a, const void* b)
{
    int* x = (int*)a;
    int* y = (int*)b;
    return *x - *y;
}

Slice* readArrayFromInput(FILE* inputStream)
{
    Slice* array = sliceCreate(sizeof(int), free);
    int inputNumber = 1;
    while (true) {
        fscanf(inputStream, "%d", &inputNumber);
        if (inputNumber == 0)
            break;

        int* inputNumberPointer = malloc(sizeof(int));
        *inputNumberPointer = inputNumber;
        sliceAdd(array, inputNumberPointer);
    }

    return array;
}

int main()
{
    printf("Input array in format \"..., 0\":\n");
    Slice* array = readArrayFromInput(stdin);
    for (int i = 0; i < sliceGetSize(array); i++) {
        printf("%d ", *(int*)sliceGet(array, i));
    }
    printf("\n");

    sliceSort(array, compareFunction);

    for (int i = 0; i < sliceGetSize(array); i++) {
        printf("%d ", *(int*)sliceGet(array, i));
    }
    printf("\n");

    return 0;

    if (!sliceGetSize(array))
        return 0;

    int* previousNumber = sliceGet(array, 0);
    int* currentNumber = sliceGet(array, 0);
    int numberCount = 1;
    for (int i = 1; i < sliceGetSize(array); i++) {
        currentNumber = sliceGet(array, i);

        if (*previousNumber != *currentNumber) {
            printf("number: %d, count: %d;\n", *previousNumber, numberCount);
            numberCount = 1;
            previousNumber = sliceGet(array, i);
        } else
            numberCount++;
    }

    return 0;
}

// 23 23 6 1 3 2 0
