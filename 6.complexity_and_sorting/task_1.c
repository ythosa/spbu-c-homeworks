#include "../lib/mergeSort/mergeSort.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Input array size: ");
    int arraySize = 0;
    scanf("%d", &arraySize);
    if (arraySize < 0) {
        printf("Invalid array size. Must be > 0");

        return 0;
    }

    printf("Input array: ");
    int* array = malloc(arraySize * sizeof(int));
    for (int i = 0; i < arraySize; i++)
        scanf("%d", &array[i]);

    sort(array, arraySize);
    printf("Sorted array: ");
    for (int i = 0; i < arraySize; i++)
        printf("%d ", array[i]);

    free(array);

    return 0;
}
