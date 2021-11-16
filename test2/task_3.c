#include "../lib/date/date.h"
#include <stdio.h>
#include <stdlib.h>

Date* findMinDateInText(FILE* inputStream)
{
    char readBuffer[DATE_LENGTH] = "";

    Date* minDate = dateCreate(32, 13, 999999);

    char ch = 0;
    while ((ch = fgetc(inputStream)) != EOF) {
        for (int j = 0; j < DATE_LENGTH - 1; j++)
            readBuffer[j] = readBuffer[j + 1];
        readBuffer[DATE_LENGTH - 1] = ch;

        if (isValidDateString(readBuffer)) {
            Date* currentDate = dateFromString(readBuffer);
            if (datesComparator(minDate, currentDate) > -1) {
                minDate->day = currentDate->day;
                minDate->month = currentDate->month;
                minDate->year = currentDate->year;
            }
            free(currentDate);
        }
    }

    return minDate;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("You need to provide input file path in program arguments");

        return 0;
    }

    char* inputFilePath = argv[1];
    FILE* inputFile = fopen(inputFilePath, "r");
    if (!inputFile) {
        printf("Invalid input file path");

        return 0;
    }

    Date* minDate = findMinDateInText(inputFile);
    datePrint(minDate, stdout);
    free(minDate);
}
