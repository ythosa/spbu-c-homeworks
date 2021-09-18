#include <malloc.h>
#include <stdio.h>

int** getSpiralForSquareMatrix(int matrixSize, int** matrix)
{
    int fillValue = matrixSize * matrixSize;
    int startingRowIndex = 0;
    int startingColumnIndex = 0;
    int endingRowIndex = matrixSize;
    int endingColumnIndex = matrixSize;

    while (startingRowIndex < endingRowIndex && startingColumnIndex < endingColumnIndex) {
        for (int i = endingColumnIndex - 1; i >= startingColumnIndex; i--) {
            matrix[startingRowIndex][i] = fillValue--;
        }
        startingRowIndex++;

        for (int i = startingRowIndex; i < endingRowIndex; i++) {
            matrix[i][startingColumnIndex] = fillValue--;
        }
        startingColumnIndex++;

        for (int i = startingColumnIndex; i < endingColumnIndex; i++) {
            matrix[endingRowIndex - 1][i] = fillValue--;
        }
        endingRowIndex--;

        for (int i = endingRowIndex - 1; i >= startingRowIndex; i--) {
            matrix[i][endingColumnIndex - 1] = fillValue--;
        }
        endingColumnIndex--;
    }

    return matrix;
}

int main()
{
    int matrixSize = 0;
    printf("Input N (a natural number that is a multiple of two):");
    scanf("%d", &matrixSize);

    if (matrixSize % 2 == 0 || matrixSize <= 0) {
        printf("Error: invalid N");

        return 0;
    }

    int** matrix = calloc(matrixSize, sizeof(int*));
    for (int i = 0; i < matrixSize; ++i) {
        matrix[i] = calloc(matrixSize, sizeof(int));
    }
    getSpiralForSquareMatrix(matrixSize);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < matrixSize; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
