#include <malloc.h>
#include <stdio.h>

int** getSpiralForSquareMatrix(int matrixSize)
{
    int** spiral = calloc(matrixSize, sizeof(int*));
    for (int i = 0; i < matrixSize; ++i) {
        spiral[i] = calloc(matrixSize, sizeof(int));
    }

    int fillValue = matrixSize * matrixSize;
    int startingRowIndex = 0;
    int startingColumnIndex = 0;
    int endingRowIndex = matrixSize;
    int endingColumnIndex = matrixSize;

    int i; // iterator
    while (startingRowIndex < endingRowIndex && startingColumnIndex < endingColumnIndex) {
        for (i = endingColumnIndex - 1; i >= startingColumnIndex; i--) {
            spiral[startingRowIndex][i] = fillValue--;
        }
        startingRowIndex++;

        for (i = startingRowIndex; i < endingRowIndex; i++) {
            spiral[i][startingColumnIndex] = fillValue--;
        }
        startingColumnIndex++;

        for (i = startingColumnIndex; i < endingColumnIndex; i++) {
            spiral[endingRowIndex - 1][i] = fillValue--;
        }
        endingRowIndex--;

        for (i = endingRowIndex - 1; i >= startingRowIndex; i--) {
            spiral[i][endingColumnIndex - 1] = fillValue--;
        }
        endingColumnIndex--;
    }

    return spiral;
}

int main()
{
    setbuf(stdout, 0);

    int n;
    printf("Input N (N mod 2 != 0, N > 0):");
    scanf("%d", &n);

    if (n % 2 == 0 || n <= 0) {
        printf("Error: invalid N");

        return -1;
    }

    int** spiral = getSpiralForSquareMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", spiral[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(spiral[i]);
    }
    free(spiral);

    return 0;
}
