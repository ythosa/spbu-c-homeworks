#include <stdlib.h>

#include "date.h"

Date* dateCreate(int day, int month, int year)
{
    Date* date = malloc(sizeof(Date));

    date->day = day;
    date->month = month;
    date->year = year;

    return date;
}

void datePrint(Date* date, FILE* outputStream)
{
    fprintf(outputStream, "%d.%d.%d", date->day, date->month, date->year);
}

int datesComparator(Date* first, Date* second)
{
    if (first->year < second->year)
        return -1;
    if (first->year > second->year)
        return 1;

    if (first->month < second->month)
        return -1;
    if (first->month > second->month)
        return 1;

    if (first->day < second->day)
        return -1;
    if (first->day > second->day)
        return 1;

    return 0;
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool isDot(char c)
{
    return c == '.';
}

int digitToInt(char c)
{
    return c - '0';
}

bool isValidDateString(char date[DATE_LENGTH])
{
    return isDigit(date[0]) && isDigit(date[1])
        && isDot(date[2])
        && isDigit(date[3]) && isDigit(date[4])
        && isDot(date[5])
        && isDigit(date[6]) && isDigit(date[7]) && isDigit(date[8]) && isDigit(date[9]);
}

Date* dateFromString(char s[DATE_LENGTH])
{
    Date* date = malloc(sizeof(Date));

    date->day = digitToInt(s[0]) * 10 + digitToInt(s[1]);
    date->month = digitToInt(s[3]) * 10 + digitToInt(s[4]);
    date->year = digitToInt(s[6]) * 1000 + digitToInt(s[7]) * 100 + digitToInt(s[8]) * 10 + digitToInt(s[9]);

    return date;
}
