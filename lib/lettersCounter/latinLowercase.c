#include "latinLowercase.h"

#define a_code 97
#define z_code 122
#define letters_count 26

struct LatinLowercaseLettersCounter {
    FILE* inputStream;
    int* letters;
};

LatinLowercaseLettersCounter* createLatinLowercaseLettersCounter(FILE* inputStream)
{
    LatinLowercaseLettersCounter* counter = malloc(sizeof(LatinLowercaseLettersCounter));

    counter->inputStream = inputStream;
    counter->letters = calloc(letters_count, sizeof(int));

    return counter;
}

void freeLatinLowercaseLettersCounter(LatinLowercaseLettersCounter* counter)
{
    free(counter->letters);
    free(counter);
}

int isLatinLowercaseLetter(int ch)
{
    return ch >= a_code && ch <= z_code;
}

void countLatinLowercaseLetters(LatinLowercaseLettersCounter* counter)
{
    int readCharacter;
    while ((readCharacter = fgetc(counter->inputStream)) != EOF)
        if (isLatinLowercaseLetter(readCharacter))
            counter->letters[readCharacter - a_code] += 1;
}

void printResult(LatinLowercaseLettersCounter* counter, FILE* outputStream)
{
    for (int i = 0; i < letters_count; i++)
        if (counter->letters[i])
            fprintf(outputStream, "%c: %d\n", i + a_code, counter->letters[i]);
}
