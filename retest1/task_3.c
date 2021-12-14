#include "stdio.h"
#include "stdlib.h"
#include <time.h>

void insertionSort(int* array, int arraySize, int step)
{
    int element, position;

    for (int i = step; i < arraySize; i += step) {
        element = array[i];
        position = i - step;
        while (position >= 0 && array[position] > element) {
            array[position + step] = array[position];
            position = position - step;
        }
        array[position + step] = element;
    }
}

void getArrayFromInput(int* array, int arraySize)
{
    printf("Input array: \n");
    for (int i = 0; i < arraySize; i++)
        scanf("%d", &array[i]);
}

void getRandomizedArray(int* array, int arraySize)
{
    srand(time(NULL)); // Initialization, should only be called once.
    for (int i = 0; i < arraySize; i++)
        array[i] = rand() % 32 + 11;
}

void printArray(int* array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main()
{
    printf("Input array size: ");
    int arraySize = 0;
    scanf("%d", &arraySize);

    printf("Do u want to input array numbers (Y/N): ");
    char userInput[1] = "N";
    scanf("%s", userInput);

    int* array = calloc(arraySize, sizeof(int));
    if (userInput[0] == 'N') {
        getRandomizedArray(array, arraySize);
        printf("Generated array: \n");
        printArray(array, arraySize);
    } else
        getArrayFromInput(array, arraySize);

    printf("Sorted array: \n");
    insertionSort(array, arraySize, 2);
    printArray(array, arraySize);
    free(array);

    return 0;
}
