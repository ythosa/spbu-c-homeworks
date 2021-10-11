#include <stdio.h>
#include <stdlib.h>

int main()
{
    double number = 0;
    printf("Input number: ");
    scanf("%lf", &number);

    int integerPartOfNumber = (int)number;
    int powerOf2 = 0;
    while (integerPartOfNumber >= 2) {
        number /= 2;
        integerPartOfNumber = abs((int)number);
        powerOf2 += 1;
    }

    printf("%.30lf*2^%d", number, powerOf2);
}
