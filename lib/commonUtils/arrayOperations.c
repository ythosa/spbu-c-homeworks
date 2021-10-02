#include "arrayOperations.h"

int maxInArray(const int* array, int arraySize)
{
    int maxElement = array[0];
    for (int i = 1; i < arraySize; i++) {
        if (array[i] > maxElement) {
            maxElement = array[i];
        }
    }

    return maxElement;
}
