#ifndef SPBU_C_HOMEWORKS_DATE_H
#define SPBU_C_HOMEWORKS_DATE_H

#include <stdbool.h>
#include <stdio.h>

#define DATE_LENGTH 10

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

Date* dateCreate(int day, int month, int year);
void datePrint(Date* date, FILE* outputStream);
int datesComparator(Date* first, Date* second);
bool isValidDateString(char date[DATE_LENGTH]);
Date* dateFromString(char s[DATE_LENGTH]);

#endif // SPBU_C_HOMEWORKS_DATE_H
