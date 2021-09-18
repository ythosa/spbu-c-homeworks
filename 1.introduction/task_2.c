#include "../library/commonUtils/arrayOperations.h"
#include <malloc.h>
#include <stdio.h>

int findIndexOfMaxElementOccurringMoreThanOnce(const int* array, int arraySize)
{
    int* occurredTimes = calloc(arraySize, maxInArray(array, arraySize) * sizeof(int));
    for (int i = 0; i < arraySize; i++) {
        occurredTimes[array[i]] = 0;
    }

    for (int i = 0; i < arraySize; i++) {
        occurredTimes[array[i]] += 1;
    }

    int maxElement = 0;
    int indexOfMaxElement = -1;
    for (int i = 0; i < arraySize; i++) {
        if (array[i] > maxElement && occurredTimes[array[i]] > 1) {
            maxElement = array[i];
            indexOfMaxElement = i;
        }
    }

    return indexOfMaxElement;
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

    int indexOfMaxElement = findIndexOfMaxElementOccurringMoreThanOnce(array, arraySize);
    if (indexOfMaxElement < 0) {
        printf("There are no elements that occur more than once");

        return 0;
    }

    printf("Maximum element occurring more than once is %d", array[indexOfMaxElement]);

    free(array);
}
