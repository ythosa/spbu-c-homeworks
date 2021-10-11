#include <stdio.h>
#include <stdlib.h>

long multiplyNumbers(leftOperand, rightOperand)
{
    short sign = (leftOperand >= 0) ^ (rightOperand >= 0) ? 1 : -1;
    leftOperand = abs(leftOperand);
    rightOperand = abs(rightOperand);

    unsigned int result = 0;
    while (rightOperand != 0) {
        if (rightOperand & 1)
            result += leftOperand;
        leftOperand <<= 1;
        rightOperand >>= 1;
    }

    return sign * result;
}

int main()
{
    int firstNumber = 0;
    printf("Input first number: ");
    scanf("%d", &firstNumber);

    int secondNumber = 0;
    printf("Input second number: ");
    scanf("%d", &secondNumber);

    printf("Multiply result: %ld", multiplyNumbers(firstNumber, secondNumber));
}
