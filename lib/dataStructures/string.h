#ifndef SPBU_C_HOMEWORKS_STRING_H
#define SPBU_C_HOMEWORKS_STRING_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
    uint8_t* data;
    uint8_t length;
    uint8_t capacity;
} str_t;

typedef struct string* String;

void stringFree(String s);
uint8_t stringLength(String s);
void stringPrint(String s, FILE* dst);
String stringDup(const char* from);
String stringPushChar(String s, char c);
String stringConcat(String left, String right);
uint8_t stringGetByIndex(String s, uint8_t index);
int stringCompare(String s1, String s2);

#endif // SPBU_C_HOMEWORKS_STRING_H
