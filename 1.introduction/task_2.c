#include <stdio.h>
#include <stdlib.h>

int compareInts(int a, int b)
{
    return (a > b) - (a < b);
}

int findIndexOfMaxElementOccurringMoreThanOnce(int* array, int arraySize)
{
    qsort(array, arraySize, sizeof(int), compareInts);

    for (int i = arraySize - 1; i > 0; i--) {
        if (array[i] == array[i - 1]) {
            return i;
        }
    }

    return -1;
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
