#include "../lib/commonUtils/numericOperations.h"
#include "../lib/slice.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int** getMatrixFromSizes(int rowsCount, int colsCount)
{
    int** matrix = calloc(rowsCount, sizeof(int*));
    for (int i = 0; i < rowsCount; i++)
        matrix[i] = calloc(colsCount, sizeof(int));

    return matrix;
}

void freeMatrix(int** matrix, int rowsCount)
{
    for (int i = 0; i < rowsCount; i++)
        free(matrix[i]);
    free(matrix);
}

void fillMatrix(int** matrix, int* rowsMins, int* colsMaxes, int rowsCount, int colsCount)
{
    for (int i = 0; i < rowsCount; i++) {
        for (int j = 0; j < colsCount; j++) {
            scanf("%d", &matrix[i][j]);
            colsMaxes[j] = max(colsMaxes[j], matrix[i][j]);
            rowsMins[i] = min(rowsMins[i], matrix[i][j]);
        }
    }
}

void fillArray(int* array, int arraySize, int value)
{
    for (int i = 0; i < arraySize; i++)
        array[i] = value;
}

typedef struct SaddleElement {
    int row;
    int col;
    int element;
} SaddleElement;

SaddleElement* createSaddleElement(int row, int col, int element)
{
    SaddleElement* saddleElement = malloc(sizeof(SaddleElement));

    saddleElement->row = row;
    saddleElement->col = col;
    saddleElement->element = element;

    return saddleElement;
}

Slice* getSaddleElementsFromMatrix(int** matrix, int* rowsMins, int* colsMaxes, int rowsCount, int colsCount)
{
    Slice* saddleElements = sliceCreate(sizeof(SaddleElement*), free);

    for (int i = 0; i < rowsCount; i++)
        for (int j = 0; j < colsCount; j++)
            if (matrix[i][j] == colsMaxes[j] && matrix[i][j] == rowsMins[i])
                sliceAdd(saddleElements, createSaddleElement(i, j, matrix[i][j]));

    return saddleElements;
}

int main()
{
    printf("Input rows and cols count: ");
    int rowsCount = 0;
    int colsCount = 0;
    scanf("%d %d", &rowsCount, &colsCount);

    printf("Input matrix: \n");
    int** matrix = getMatrixFromSizes(rowsCount, colsCount);

    int* rowsMins = calloc(sizeof(int), rowsCount);
    fillArray(rowsMins, rowsCount, INT_MAX);
    int* colsMaxes = calloc(sizeof(int), colsCount);
    fillArray(colsMaxes, colsCount, INT_MIN);

    fillMatrix(matrix, rowsMins, colsMaxes, rowsCount, colsCount);

    Slice* saddleElements = getSaddleElementsFromMatrix(matrix, rowsMins, colsMaxes, rowsCount, colsCount);
    printf("Found saddle elements:\n");
    int saddleElementsCount = sliceGetSize(saddleElements);
    if (!saddleElements)
        printf("There is no saddle elements :(\n");
    else
        for (int i = 0; i < saddleElementsCount; i++) {
            SaddleElement* saddleElement = sliceGet(saddleElements, i);
            printf("%d in (%d; %d)\n", saddleElement->element, saddleElement->row, saddleElement->col);
        }

    sliceFree(saddleElements);
    free(colsMaxes);
    free(rowsMins);
    freeMatrix(matrix, rowsCount);
}
