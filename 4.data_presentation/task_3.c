#include <stdio.h>

unsigned int multiplyNumbers(leftOperand, rightOperand)
{
    unsigned int result = 0;

    while (rightOperand != 0) {
        if (rightOperand & 1)
            result += leftOperand;
        leftOperand <<= 1;
        rightOperand >>= 1;
    }

    return result;
}

int main()
{
    unsigned short firstNumber = 0;
    printf("Input first number: ");
    scanf("%d", &firstNumber);

    unsigned short secondNumber = 0;
    printf("Input second number: ");
    scanf("%d", &secondNumber);

    printf("Multiply result: %d", multiplyNumbers(4, 5));
}
