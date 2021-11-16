#include <stdio.h>
#include <stdlib.h>

int* mergeTwoSortedArrays(int firstSize, const int* first, int secondSize, const int* second)
{
    int* mergeResult = calloc(firstSize + secondSize, sizeof(int));

    int firstIndex = 0;
    int secondIndex = 0;
    int mergeResultIndex = 0;

    while (firstIndex < firstSize && secondIndex < secondSize)
        if (first[firstIndex] < second[secondIndex])
            mergeResult[mergeResultIndex++] = first[firstIndex++];
        else
            mergeResult[mergeResultIndex++] = second[secondIndex++];

    while (firstIndex < firstSize)
        mergeResult[mergeResultIndex++] = first[firstIndex++];

    while (secondIndex < secondSize)
        mergeResult[mergeResultIndex++] = second[secondIndex++];

    return mergeResult;
}

/*
 * Complexity - O(firstStudentSubjectsNumber + secondStudentSubjectsNumber)
 * or O(N + M) or linear complexity.
*/

int main()
{
    printf("Enter the number of subjects of the first student: ");
    int firstStudentSubjectsNumber = 0;
    scanf("%d", &firstStudentSubjectsNumber);

    int* firstStudentSubjects = calloc(firstStudentSubjectsNumber, sizeof(int));
    printf("Enter first student subjects: ");
    for (int i = 0; i < firstStudentSubjectsNumber; i++)
        scanf("%d", &firstStudentSubjects[i]);

    printf("Enter the number of subjects of the second student: ");
    int secondStudentSubjectsNumber = 0;
    scanf("%d", &secondStudentSubjectsNumber);

    int* secondStudentSubjects = calloc(secondStudentSubjectsNumber, sizeof(int));
    printf("Enter second student subjects: ");
    for (int i = 0; i < secondStudentSubjectsNumber; i++)
        scanf("%d", &secondStudentSubjects[i]);

    int* merged = mergeTwoSortedArrays(firstStudentSubjectsNumber, firstStudentSubjects,
        secondStudentSubjectsNumber, secondStudentSubjects);

    printf("Combined subject summaries: ");
    for (int i = 0; i < firstStudentSubjectsNumber + secondStudentSubjectsNumber; i++)
        printf("%d ", merged[i]);

    free(firstStudentSubjects);
    free(secondStudentSubjects);
    free(merged);
}
