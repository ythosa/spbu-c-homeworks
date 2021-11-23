#ifndef SPBU_C_HOMEWORKS_BINARY_H
#define SPBU_C_HOMEWORKS_BINARY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryNumber BinaryNumber;

BinaryNumber* binaryNumberCreate(size_t size);
void binaryNumberFree(BinaryNumber* binaryNumber);
void binaryNumberInvert(BinaryNumber* binaryNumber);
BinaryNumber* binaryNumberFromInteger(int number);
int binaryNumberToInteger(BinaryNumber* binaryNumber);
BinaryNumber* binaryNumberAdd(BinaryNumber* leftOperand, BinaryNumber* rightOperand);
void binaryNumberPrint(BinaryNumber* binaryNumber, char* end, FILE* destination);
void binaryNumberLeftShift(BinaryNumber* binaryNumber, size_t bitsCount);
void binaryNumberRightShift(BinaryNumber* binaryNumber, size_t bitsCount);
BinaryNumber* binaryNumberMultiply(BinaryNumber* leftOperand, BinaryNumber* rightOperand);

#endif // SPBU_C_HOMEWORKS_BINARY_H
