#include "arrayOperations.h"
#include "numericOperations.h"

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

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];

    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low >= high) {
        return;
    }

    int p = partition(arr, low, high);
    quickSort(arr, low, p - 1);
    quickSort(arr, p + 1, high);
}
