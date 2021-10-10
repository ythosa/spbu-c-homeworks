#ifndef SPBU_C_HOMEWORKS_BINARY_H
#define SPBU_C_HOMEWORKS_BINARY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryNumber BinaryNumber;

BinaryNumber* binaryNumberCreate(uint size);
void binaryNumberFree(BinaryNumber* binaryNumber);
void binaryNumberInvert(BinaryNumber* binaryNumber);
BinaryNumber* binaryNumberFromInteger(int number);
int binaryNumberToInteger(BinaryNumber* binaryNumber);
BinaryNumber* binaryNumberAdd(BinaryNumber* leftOperand, BinaryNumber* rightOperand);
void binaryNumberPrint(BinaryNumber* binaryNumber, char* end, FILE* destination);

#endif // SPBU_C_HOMEWORKS_BINARY_H
