#include "../lib/slice.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayWithMeta {
    int* array;
    int meta;
} ArrayWithMeta;

ArrayWithMeta** getMatrixFromSizes(int rowsCount, int colsCount)
{
    ArrayWithMeta** matrix = calloc(rowsCount, sizeof(ArrayWithMeta*));
    for (int i = 0; i < colsCount; i++)
        matrix[rowsCount] = calloc(colsCount, sizeof(ArrayWithMeta));

    return matrix;
}

void fillMatrix(int** matrix, int rowsCount, int colsCount)
{
    for (int i = 0; i < rowsCount; i++) {
        for (int j = 0; j < colsCount; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
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

Slice* fillSaddleElementMatrix(int** matrix, int rowsCount, int colsCount)
{
    for (int i = 0; i < rowsCount; i++) {
        for (int j = 0; j < colsCount; j++) {
            int maxColumn
        }
    }
}

int main()
{
    printf("Input rows and cols count: ");
    int rowsCount = 0;
    int colsCount = 0;
    scanf("%d %d", &rowsCount, &colsCount);

    int** matrix = malloc(sizeof())
}
