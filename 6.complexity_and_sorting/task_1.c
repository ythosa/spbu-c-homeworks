#include <string.h>

#define COPY_ARRAY(destination, source, length, sizeOfElement) (memcpy(destination, source, length * sizeOfElement))

void mergeSubarrays(int array[], int leftIndex, int middleIndex, int rightIndex)
{
    int sizeOfLeftSubarray = middleIndex - leftIndex + 1;
    int sizeOfRightSubarray = rightIndex - middleIndex;

    int leftSubarray[sizeOfLeftSubarray], rightSubarray[sizeOfRightSubarray];
    COPY_ARRAY(leftSubarray, array + leftIndex, sizeOfLeftSubarray, sizeof(int));
    COPY_ARRAY(rightSubarray, array + middleIndex + 1, sizeOfRightSubarray, sizeof(int));

    int leftSubarrayIndex = 0;
    int rightSubarrayIndex = 0;
    int baseArrayIndex = leftIndex;
    while (leftSubarrayIndex < sizeOfLeftSubarray && rightSubarrayIndex < sizeOfRightSubarray) {
        if (leftSubarray[leftSubarrayIndex] <= rightSubarray[rightSubarrayIndex]) {
            array[baseArrayIndex] = leftSubarray[leftSubarrayIndex];
            leftSubarrayIndex++;
        } else {
            array[baseArrayIndex] = rightSubarray[rightSubarrayIndex];
            rightSubarrayIndex++;
        }
        baseArrayIndex++;
    }

    while (leftSubarrayIndex < sizeOfLeftSubarray) {
        array[baseArrayIndex] = leftSubarray[leftSubarrayIndex];
        leftSubarrayIndex++;
        baseArrayIndex++;
    }

    while (rightSubarrayIndex < sizeOfRightSubarray) {
        array[baseArrayIndex] = rightSubarray[rightSubarrayIndex];
        rightSubarrayIndex++;
        baseArrayIndex++;
    }
}

void mergeSort(int array[], int leftIndexOfSubarray, int rightIndexOfSubarray)
{
    if (leftIndexOfSubarray >= rightIndexOfSubarray) {
        return;
    }

    int middle = leftIndexOfSubarray + (rightIndexOfSubarray - leftIndexOfSubarray) / 2;
    mergeSort(array, leftIndexOfSubarray, middle);
    mergeSort(array, middle + 1, rightIndexOfSubarray);
    mergeSubarrays(array, leftIndexOfSubarray, middle, rightIndexOfSubarray);
}
