#ifndef SPBU_C_HOMEWORKS_LATINLOWERCASE_H
#define SPBU_C_HOMEWORKS_LATINLOWERCASE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LatinLowercaseLettersCounter LatinLowercaseLettersCounter;

LatinLowercaseLettersCounter* createLatinLowercaseLettersCounter();
void freeLatinLowercaseLettersCounter(LatinLowercaseLettersCounter* counter);
void countLetters(LatinLowercaseLettersCounter* counter, FILE* inputStream);
void printResult(LatinLowercaseLettersCounter* counter, FILE* outputStream);

#endif // SPBU_C_HOMEWORKS_LATINLOWERCASE_H
