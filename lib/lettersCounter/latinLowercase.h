#ifndef SPBU_C_HOMEWORKS_LATINLOWERCASE_H
#define SPBU_C_HOMEWORKS_LATINLOWERCASE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LatinLowercaseLettersCounter LatinLowercaseLettersCounter;

LatinLowercaseLettersCounter* createLatinLowercaseLettersCounter(FILE* inputStream);
void freeLatinLowercaseLettersCounter(LatinLowercaseLettersCounter* counter);
void countLatinLowercaseLetters(LatinLowercaseLettersCounter* counter);
void printResult(LatinLowercaseLettersCounter* counter, FILE* outputStream);

#endif // SPBU_C_HOMEWORKS_LATINLOWERCASE_H
