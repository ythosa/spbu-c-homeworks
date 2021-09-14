#include <malloc.h>
#include <stdio.h>

void reverse_array(int first_index, int size, int* array)
{
    int temp;
    for (int i = 0; i < size / 2; i++) {
        temp = array[size - i - 1 + first_index];
        array[size - i - 1 + first_index] = array[i + first_index];
        array[i + first_index] = temp;
    }
}

void swap_array_parts(int left_part_size, int right_part_size, int* array)
{
    reverse_array(0, left_part_size, array);
    reverse_array(left_part_size, right_part_size, array);
    reverse_array(0, left_part_size + right_part_size, array);
}

int main()
{
    int left_part_size = 0;
    printf("Input m (left_part_size)=");
    scanf("%d", &left_part_size);

    int right_part_size = 0;
    printf("Input n (right_part_size)=");
    scanf("%d", &right_part_size);

    int array_size = left_part_size + right_part_size;
    int* array = calloc(array_size, sizeof(int));
    for (int i = 0; i < array_size; i++) {
        printf("[%d]=", i);
        scanf("%d", &array[i]);
    }

    swap_array_parts(left_part_size, right_part_size, array);

    printf("Array with swapped parts: ");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", array[i]);
    }

    free(array);

    return 0;
}
