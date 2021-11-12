#include <stdio.h>
#include <stdlib.h>

#include "../lib/vector/vector.h"

void readVector(Vector* vector, FILE* inputStream)
{
    char* line = NULL;
    size_t lineSize = 0;
    ssize_t lineLength = getline(&line, &lineSize, inputStream);
    for (int i = 0; i < lineLength; i += 2) {
        vectorPushback(vector, line[i] - '0');
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("invalid count of arguments. please provide inputFile file path");

        return 0;
    }

    FILE* inputFile = fopen(argv[1], "r");

    Vector* vector1 = vectorCreate();
    readVector(vector1, inputFile);

    Vector* vector2 = vectorCreate();
    readVector(vector2, inputFile);

    printf("Vector1 length: %f\n", vectorLength(vector1));
    printf("Vector2 length: %f\n", vectorLength(vector2));

    Vector* vectorSum = vectorPlus(vector1, vector2);
    if (!vectorSum) {
        printf("Error counting vectors sum\n");
    } else {
        printf("Vectors sum: ");
        vectorPrint(vectorSum, stdout);
        printf("\n");
    }
    vectorFree(vectorSum);

    Vector* vectorDiff = vectorMinus(vector1, vector2);
    if (!vectorDiff) {
        printf("Error counting vectors minus\n");
    } else {
        printf("Vectors minus: ");
        vectorPrint(vectorDiff, stdout);
        printf("\n");
    }
    vectorFree(vectorDiff);

    int dotProduct = 0;
    if (!vectorDotProduct(&dotProduct, vector1, vector2)) {
        printf("Error counting dot product\n");
    } else {
        printf("Vectors dot product: %d\n", dotProduct);
    }

    vectorFree(vector1);
    vectorFree(vector2);

    return 0;
}
