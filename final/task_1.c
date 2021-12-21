#include "../lib/slice.h"
#include <stdio.h>

Slice* readArrayFromInput(FILE* inputStream)
{
    Slice* array = sliceCreate(sizeof(int));
    int inputNumber = 1;
    while (true) {
        fscanf(inputStream, "%d", &inputNumber);
        if (inputNumber == 0)
            break;

        sliceAdd(array, inputNumber);
    }

    return array;
}

int main()
{
    printf("Input array in format \"..., 0\":\n");
    Slice* array = readArrayFromInput(stdin);
    int arraySize = sliceGetSize(array);

    if (!arraySize)
        return 0;

    sliceSort(array);

    int previousNumber = sliceGet(array, 0);
    int currentNumber = sliceGet(array, 0);
    int numberCount = 1;
    for (int i = 1; i < arraySize; i++) {
        currentNumber = sliceGet(array, i);

        if (previousNumber != currentNumber) {
            printf("number: %d, count: %d;\n", previousNumber, numberCount);
            numberCount = 1;
            previousNumber = sliceGet(array, i);
        } else
            numberCount++;
    }
    printf("number: %d, count: %d;\n", previousNumber, numberCount);

    return 0;
}
