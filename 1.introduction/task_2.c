#include "../library/commonUtils/arrayOperations.h"
#include <malloc.h>
#include <stdio.h>

int findMaxElementOccurringMoreThanOnce(const int* array, int arraySize)
{
    int* occurredTimes = calloc(arraySize, max(array, arraySize) * sizeof(int));

    for (int i = 0; i < arraySize; i++) {
        occurredTimes[array[i]] += 1;
    }

    int m = 0;
    for (int i = 0; i < arraySize; i++) {
        if (array[i] > m && occurredTimes[array[i]] > 1) {
            m = array[i];
        }
    }

    return m;
}

int main()
{
    int arraySize = 0;
    printf("Input array size:");
    scanf("%d", &arraySize);

    int* array = calloc(arraySize, sizeof(int));
    for (int i = 0; i < arraySize; i++) {
        printf("[%d]=", i);
        scanf("%d", &array[i]);
    }

    int m = findMaxElementOccurringMoreThanOnce(array, arraySize);
    printf("Maximum element occurring more than once is %d", m);

    free(array);
}
