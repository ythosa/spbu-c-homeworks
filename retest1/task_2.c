#include <stdio.h>

#include "../lib/lettersCounter/latinLowercase.h"

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("You must provide input and output file paths.\n");

        return 0;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        printf("Invalid input file path.\n");

        return 0;
    }

    LatinLowercaseLettersCounter* counter = createLatinLowercaseLettersCounter(inputFile);

    countLatinLowercaseLetters(counter);
    fclose(inputFile);

    FILE* outputFile = fopen(argv[2], "w");
    printResult(counter, outputFile);
    fclose(outputFile);

    freeLatinLowercaseLettersCounter(counter);

    return 0;
}
