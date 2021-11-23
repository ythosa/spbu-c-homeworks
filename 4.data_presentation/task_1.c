#include <stdio.h>

#include "../lib/binary.h"

int main()
{
    int firstNumber = 0;
    printf("Input first number: ");
    scanf("%d", &firstNumber);

    int secondNumber = 0;
    printf("Input second number: ");
    scanf("%d", &secondNumber);

    BinaryNumber* firstNumberBin = binaryNumberFromInteger(firstNumber);
    printf("First number in binary: ");
    binaryNumberPrint(firstNumberBin, "\n", stdout);

    BinaryNumber* secondNumberBin = binaryNumberFromInteger(secondNumber);
    printf("Second number in binary: ");
    binaryNumberPrint(secondNumberBin, "\n", stdout);

    printf("Sum: %d\n", firstNumber + secondNumber);
    BinaryNumber* sumBinary = binaryNumberAdd(firstNumberBin, secondNumberBin);
    printf("Sum in binary: ");
    binaryNumberPrint(sumBinary, "\n", stdout);

    binaryNumberFree(firstNumberBin);
    binaryNumberFree(secondNumberBin);
    binaryNumberFree(sumBinary);
}
