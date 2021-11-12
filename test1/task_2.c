#include "../lib/vector/vector.h"
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("invalid count of arguments. please provide inputFile and outputFile file paths");

        return 0;
    }

    printf("Input a: ");
    int a = 0;
    scanf("%d", &a);

    printf("Input b: ");
    int b = 0;
    scanf("%d", &b);

    if (a > b) {
        swap(&a, &b);
    }

    Vector* numsLowerThenA = vectorCreate();
    Vector* numsInABInterval = vectorCreate();
    Vector* numsGreaterThenB = vectorCreate();

    FILE* inputFile = fopen(argv[1], "r");
    char* line = NULL;
    size_t lineSize = 0;
    ssize_t lineLength = getline(&line, &lineSize, inputFile);
    for (int i = 0; i < lineLength; i += 2) {
        int currentNumber = line[i] - '0';
        if (currentNumber < a) {
            vectorPushback(numsLowerThenA, currentNumber);
        } else if (currentNumber > b) {
            vectorPushback(numsGreaterThenB, currentNumber);
        } else {
            vectorPushback(numsInABInterval, currentNumber);
        }
    }
    fclose(inputFile);

    FILE* outputFile = fopen(argv[2], "w");
    vectorPrint(numsLowerThenA, outputFile);
    vectorPrint(numsInABInterval, outputFile);
    vectorPrint(numsGreaterThenB, outputFile);
    fclose(outputFile);
}
