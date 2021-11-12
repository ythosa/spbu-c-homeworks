#ifndef SPBU_C_HOMEWORKS_STRING_H
#define SPBU_C_HOMEWORKS_STRING_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A String is a reference type.
 * You should use stringFree to free up the String memory. */
typedef struct String* String;

/* Free up String memory. */
void stringFree(String s);

/* Returns String length. */
uint8_t stringLength(String s);

/* Prints String into `dst` output. */
void stringPrint(String s, FILE* dst);

/* Constructs String from char*.
 * Analog for `strdup`. */
String stringDup(const char* from);

/* Converts String to char*. */
uint8_t* stringC(String s);

/* Adds a character to the end of the String. */
String stringPush(String s, char c);

/* Performs String concatenation. */
String stringCat(String left, String right);

/* Returns char Element with index from String.
 * There is no check for the validity of the index. */
uint8_t stringGet(String s, uint8_t index);

/* Compares two strings lexicographically.
 * `strcmp` analog. */
int stringCmp(String s1, String s2);

#endif // SPBU_C_HOMEWORKS_STRING_H
