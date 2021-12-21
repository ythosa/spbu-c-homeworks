#include <stdio.h>
#include <stdlib.h>

int** getMatrixFromSizes(int rowsCount, int colsCount)
{
    int** matrix = calloc(rowsCount, sizeof(int*));
    for (int i = 0; i < colsCount; i++)
        matrix[rowsCount] = calloc(colsCount, sizeof(int));

    return matrix;
}

void fillMatrix(int** matrix, int rowsCount, int colsCount)
{
    for (int i = 0; i < rowsCount; i++)
        for (int j = 0; j < colsCount; j++)
            scanf("%d", &matrix[i][j]);
}

int** fillSaddleElementMatrix(int** matrix, int rowsCount, int colsCount)
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
