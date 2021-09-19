#include <stdio.h>
#include <stdlib.h>

void reverseArray(int firstIndex, int size, int* array)
{
    for (int i = 0; i < size / 2; i++) {
        int temp = array[size - i - 1 + firstIndex];
        array[size - i - 1 + firstIndex] = array[i + firstIndex];
        array[i + firstIndex] = temp;
    }
}

void swapArrayParts(int leftPartSize, int rightPartSize, int* array)
{
    reverseArray(0, leftPartSize, array);
    reverseArray(leftPartSize, rightPartSize, array);
    reverseArray(0, leftPartSize + rightPartSize, array);
}

int main()
{
    int leftPartSize = 0;
    printf("Input m (left part size)=");
    scanf("%d", &leftPartSize);

    int rightPartSize = 0;
    printf("Input n (right part size)=");
    scanf("%d", &rightPartSize);

    int arraySize = leftPartSize + rightPartSize;
    int* array = calloc(arraySize, sizeof(int));
    for (int i = 0; i < arraySize; i++) {
        printf("[%d]=", i);
        scanf("%d", &array[i]);
    }

    swapArrayParts(leftPartSize, rightPartSize, array);

    printf("Array with swapped parts: ");
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", array[i]);
    }

    free(array);

    return 0;
}
