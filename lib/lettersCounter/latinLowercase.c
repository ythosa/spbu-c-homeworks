#include "latinLowercase.h"

#define LOWERCASE_A_CODE 97
#define LOWERCASE_Z_CODE 122
#define LATIN_LETTERS_NUMBER 26

struct LatinLowercaseLettersCounter {
    int* quantities;
};

LatinLowercaseLettersCounter* createLatinLowercaseLettersCounter()
{
    LatinLowercaseLettersCounter* counter = malloc(sizeof(LatinLowercaseLettersCounter));

    counter->quantities = calloc(LATIN_LETTERS_NUMBER, sizeof(int));

    return counter;
}

void freeLatinLowercaseLettersCounter(LatinLowercaseLettersCounter* counter)
{
    free(counter->quantities);
    free(counter);
}

int isLatinLowercaseLetter(int ch)
{
    return ch >= LOWERCASE_A_CODE && ch <= LOWERCASE_Z_CODE;
}

void countLetters(LatinLowercaseLettersCounter* counter, FILE* inputStream)
{
    int readCharacter;
    while ((readCharacter = fgetc(inputStream)) != EOF)
        if (isLatinLowercaseLetter(readCharacter))
            counter->quantities[readCharacter - LOWERCASE_A_CODE] += 1;
}

void printResult(LatinLowercaseLettersCounter* counter, FILE* outputStream)
{
    for (int i = 0; i < LATIN_LETTERS_NUMBER; i++)
        if (counter->quantities[i])
            fprintf(outputStream, "%c: %d\n", i + LOWERCASE_A_CODE, counter->quantities[i]);
}
