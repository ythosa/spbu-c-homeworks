#include "arrayOperations.h"
#include <limits.h>

int max(const int* array, int arraySize)
{
    int m = INT_MIN;
    for (int i = 0; i < arraySize; i++) {
        if (array[i] > m) {
            m = array[i];
        }
    }

    return m;
}
