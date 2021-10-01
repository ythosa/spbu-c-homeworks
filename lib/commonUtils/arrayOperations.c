#include "arrayOperations.h"

int maxInArray(const int* array, int arraySize)
{
    int m = array[0];
    for (int i = 1; i < arraySize; i++) {
        if (array[i] > m) {
            m = array[i];
        }
    }

    return m;
}
