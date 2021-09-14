#include "../library/commonUtils/arrayOperations.h"
#include <malloc.h>
#include <stdio.h>

int find_max_element_occurring_more_than_once(const int* array, int array_size)
{
    int* occurred_times = calloc(array_size, max(array, array_size) * sizeof(int));

    for (int i = 0; i < array_size; i++) {
        occurred_times[array[i]] += 1;
    }

    int m = 0;
    for (int i = 0; i < array_size; i++) {
        if (array[i] > m && occurred_times[array[i]] > 1) {
            m = array[i];
        }
    }

    return m;
}

int main()
{
    int array_size = 0;
    printf("Input array size:");
    scanf("%d", &array_size);

    int* array = calloc(array_size, sizeof(int));
    for (int i = 0; i < array_size; i++) {
        printf("[%d]=", i);
        scanf("%d", &array[i]);
    }

    int m = find_max_element_occurring_more_than_once(array, array_size);
    printf("Maximum element occurring more than once is %d", m);

    free(array);
}
