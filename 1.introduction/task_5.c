#include <malloc.h>
#include <stdio.h>

int** get_spiral_for_square_matrix(int matrix_size)
{
    int** spiral = calloc(matrix_size, sizeof(int*));
    for (int i = 0; i < matrix_size; ++i) {
        spiral[i] = calloc(matrix_size, sizeof(int));
    }

    int fill_value = matrix_size * matrix_size;
    int starting_row_index = 0;
    int starting_column_index = 0;
    int ending_row_index = matrix_size;
    int ending_column_index = matrix_size;

    int i; // iterator
    while (starting_row_index < ending_row_index && starting_column_index < ending_column_index) {
        for (i = ending_column_index - 1; i >= starting_column_index; i--) {
            spiral[starting_row_index][i] = fill_value--;
        }
        starting_row_index++;

        for (i = starting_row_index; i < ending_row_index; i++) {
            spiral[i][starting_column_index] = fill_value--;
        }
        starting_column_index++;

        for (i = starting_column_index; i < ending_column_index; i++) {
            spiral[ending_row_index - 1][i] = fill_value--;
        }
        ending_row_index--;

        for (i = ending_row_index - 1; i >= starting_row_index; i--) {
            spiral[i][ending_column_index - 1] = fill_value--;
        }
        ending_column_index--;
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

    int** spiral = get_spiral_for_square_matrix(n);
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
