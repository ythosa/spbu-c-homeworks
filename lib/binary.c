#include <math.h>

#include "binary.h"

#define BITS_IN_BYTE 8

struct BinaryNumber {
    uint size;
    bool* bits;
};

BinaryNumber* binaryNumberCreate(uint size)
{
    BinaryNumber* binaryNumber = malloc(sizeof(BinaryNumber));

    binaryNumber->size = size;
    binaryNumber->bits = calloc(size, sizeof(bool));

    return binaryNumber;
}

void binaryNumberFree(BinaryNumber* binaryNumber)
{
    free(binaryNumber->bits);
    free(binaryNumber);
}

void binaryNumberInvert(BinaryNumber* binaryNumber)
{
    for (int i = 0; i < binaryNumber->size; i++)
        binaryNumber->bits[i] = abs(1 - binaryNumber->bits[i]);
}

BinaryNumber* binaryNumberFromInteger(int number)
{
    BinaryNumber* binaryNumber = binaryNumberCreate(sizeof(number) * BITS_IN_BYTE);

    int numberAbs = abs(number);
    for (int i = 0; numberAbs > 0; i++) {
        binaryNumber->bits[binaryNumber->size - i - 1] = numberAbs % 2;
        numberAbs /= 2;
    }

    if (number < 0) {
        binaryNumberInvert(binaryNumber);
        BinaryNumber* one = binaryNumberFromInteger(1);
        BinaryNumber* binaryNumberPlusOne = binaryNumberAdd(binaryNumber, one);
        binaryNumberFree(one);
        binaryNumberFree(binaryNumber);
        binaryNumber = binaryNumberPlusOne;
    }

    return binaryNumber;
}

int binaryNumberToInteger(BinaryNumber* binaryNumber)
{
    int integerNumber = 0;
    for (int i = 0; i < binaryNumber->size; i++)
        integerNumber += (int)pow(2, i) * binaryNumber->bits[binaryNumber->size - i - 1];

    return integerNumber;
}

BinaryNumber* binaryNumberAdd(BinaryNumber* leftOperand, BinaryNumber* rightOperand)
{
    if (leftOperand->size != rightOperand->size)
        return NULL;

    BinaryNumber* resultBinaryNumber = binaryNumberCreate(leftOperand->size);
    int buf = 0;
    for (int i = (int)resultBinaryNumber->size - 1; i >= 0; i--) {
        int s = leftOperand->bits[i] + rightOperand->bits[i];
        resultBinaryNumber->bits[i] = (s + buf) % 2;
        buf = (s + buf) >= 2 ? 1 : 0;
    }

    return resultBinaryNumber;
}

void binaryNumberPrint(BinaryNumber* binaryNumber, char* end, FILE* destination)
{
    for (int i = 0; i < binaryNumber->size; i++)
        fprintf(destination, "%d ", binaryNumber->bits[i]);

    if (end)
        fprintf(destination, "%s", end);
}
