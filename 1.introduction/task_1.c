#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int calculateIncompleteQuotientForPositiveIntegers(int dividend, int divisor) {
    int quotient = 0;
    while (dividend >= divisor) {
        dividend -= divisor;
        ++quotient;
    }

    return quotient;
}

int calculateIncompleteQuotient(int dividend, int divisor)
{
    int result = calculateIncompleteQuotientForPositiveIntegers(abs(dividend), abs(divisor));

    if (dividend < 0) {
        result = -result - 1;
    }

    if (divisor < 0) {
        result = -result;
    }

    return result;
}

bool getDividendAndDivisor(int* dividend, int* divisor)
{
    printf("Input dividend:");
    scanf("%d", dividend);
    printf("Input divisor:");
    scanf("%d", divisor);

    if (!divisor) {
        printf("Error: division by zero");

        return false;
    }

    return true;
}

int main()
{
    int dividend = 0;
    int divisor = 0;
    if (!getDividendAndDivisor(&dividend, &divisor)) {
        printf("The program failed with an error");

        return 0;
    }

    int quotient = calculateIncompleteQuotient(dividend, divisor);
    printf("Results:\n\tincomplete quotient: %d", quotient);

    return 0;
}
