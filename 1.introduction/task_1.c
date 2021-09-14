#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void calculateIncompleteQuotient(int dividend, int divisor, int* quotient, int* reminder)
{
    *quotient = 0;
    *reminder = 0;

    short sign = (dividend < 0 ^ divisor < 0) ? -1 : 1;
    int dividendAbs = abs(dividend);
    int divisorAbs = abs(divisor);

    while (dividendAbs >= divisorAbs) {
        dividendAbs -= divisorAbs;
        *quotient += 1;
    }

    if (dividend > 0) {
        *reminder = dividend - *quotient * divisorAbs;
        *quotient = *quotient * sign;

        return;
    }

    int quotientForReminder = -*quotient - 1;
    *reminder = dividend - divisor * quotientForReminder;
    *quotient = abs(quotientForReminder) * sign;
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
        return -1;
    }

    int quotient = 0;
    int reminder = 0;
    calculateIncompleteQuotient(dividend, divisor, &quotient, &reminder);

    printf("Results:\n\tquotient: %d\n\treminder: %d\n", quotient, reminder);

    return 0;
}
