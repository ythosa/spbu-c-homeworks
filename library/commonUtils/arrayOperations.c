#include "arrayOperations.h"
#include <limits.h>

int max(const int* array, int array_size)
{
    int m = INT_MIN;
    for (int i = 0; i < array_size; i++) {
        if (array[i] > m) {
            m = array[i];
        }
    }

    return m;
}
