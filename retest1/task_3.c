#include "stdio.h"
#include "stdlib.h"
#include <time.h>

void insertionSort(int* array, int arraySize, int indexStep)
{
    for (int i = indexStep; i < arraySize; i += indexStep) {
        int element = array[i];
        int position = i - indexStep;

        while (position >= 0 && array[position] > element) {
            array[position + indexStep] = array[position];
            position = position - indexStep;
        }

        array[position + indexStep] = element;
    }
}

void fillArrayFromInput(int* array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
        scanf("%d", &array[i]);
}

void fillArrayWithRandomNumbers(int* array, int arraySize, int minValue, int maxValue)
{
    srand(time(NULL));
    for (int i = 0; i < arraySize; i++)
        array[i] = rand() % (maxValue - minValue + 1) + minValue;
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
    char userInput[1] = "Y";
    scanf("%s", userInput);

    int* array = calloc(arraySize, sizeof(int));
    if (userInput[0] == 'Y') {
        printf("Input array: \n");
        fillArrayFromInput(array, arraySize);
    } else {
        fillArrayWithRandomNumbers(array, arraySize, 11, 42);
        printf("Generated array: \n");
        printArray(array, arraySize);
    }

    printf("Sorted array: \n");
    insertionSort(array, arraySize, 2);
    printArray(array, arraySize);
    free(array);

    return 0;
}
