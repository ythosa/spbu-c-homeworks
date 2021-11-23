#include "../lib/binary.h"
#include <stdio.h>

int main()
{
    int firstNumber = 0;
    printf("Input first number: ");
    scanf("%d", &firstNumber);

    int secondNumber = 0;
    printf("Input second number: ");
    scanf("%d", &secondNumber);

    BinaryNumber* firstNumberBinary = binaryNumberFromInteger(firstNumber);
    BinaryNumber* secondNumberBinary = binaryNumberFromInteger(secondNumber);
    BinaryNumber* multiplyResult = binaryNumberMultiply(firstNumberBinary, secondNumberBinary);

    printf("Multiply result: %d", binaryNumberToInteger(multiplyResult));

    binaryNumberFree(firstNumberBinary);
    binaryNumberFree(secondNumberBinary);
    binaryNumberFree(multiplyResult);
}
