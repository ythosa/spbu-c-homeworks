#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void calculate_incomplete_quotient(int dividend, int divisor, int* quotient, int* reminder)
{
    *quotient = 0;
    *reminder = 0;

    short sign = (dividend < 0 ^ divisor < 0) ? -1 : 1;
    int dividend_abs = abs(dividend);
    int divisor_abs = abs(divisor);

    while (dividend_abs >= divisor_abs) {
        dividend_abs -= divisor_abs;
        *quotient += 1;
    }

    if (dividend > 0) {
        *reminder = dividend - *quotient * divisor_abs;
        *quotient = *quotient * sign;

        return;
    }

    int quotient_for_reminder = -*quotient - 1;
    *reminder = dividend - divisor * quotient_for_reminder;
    *quotient = abs(quotient_for_reminder) * sign;
}

bool get_dividend_and_divisor(int* dividend, int* divisor)
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
    if (!get_dividend_and_divisor(&dividend, &divisor)) {
        return -1;
    }

    int quotient = 0;
    int reminder = 0;
    calculate_incomplete_quotient(dividend, divisor, &quotient, &reminder);

    printf("Results:\n\tquotient: %d\n\treminder: %d\n", quotient, reminder);

    return 0;
}
