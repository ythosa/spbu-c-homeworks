#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NormalizedView {
    bool sign;
    double fraction;
    int base;
    int exponent;
} NormalizedView;

NormalizedView* normalizedViewCreate(bool sign, double fraction, int base, int exponent)
{
    NormalizedView* normalizedView = malloc(sizeof(NormalizedView));

    normalizedView->sign = sign;
    normalizedView->fraction = fraction;
    normalizedView->base = base;
    normalizedView->exponent = exponent;

    return normalizedView;
}

void normalizedViewFree(NormalizedView* normalizedView)
{
    free(normalizedView);
}

void normalizedViewPrint(NormalizedView* normalizedView, FILE* destination)
{
    fprintf(
        destination,
        "%s%.17f * %d^%d\n",
        normalizedView->sign ? "-" : "+",
        normalizedView->fraction,
        normalizedView->base,
        normalizedView->exponent);
}

void doubleToBinary(double number, char binary[64])
{
    u_int64_t bits = 0;
    memcpy(&bits, &number, sizeof(double));
    for (int i = 63; i >= 0; i--)
        binary[63 - i] = (bits >> i) & 1;
}

NormalizedView* normalizedViewForDouble(double number)
{
    char binary[64] = "";
    doubleToBinary(number, binary);

    double powerOfTwo = 1024;
    int exponent = -1023;
    for (int i = 1; i < 12; i++) {
        if (binary[i])
            exponent += (int)powerOfTwo;
        powerOfTwo /= 2;
    }

    double fraction = 1;
    for (int i = 12; i < 64; ++i) {
        if (binary[i])
            fraction += powerOfTwo;
        powerOfTwo /= 2;
    }

    if (exponent == -1023 && fraction == 1)
        return normalizedViewCreate(binary[0], 0, 2, 0);

    return normalizedViewCreate(binary[0], fraction, 2, exponent);
}

int main()
{
    double number = 0;
    printf("Input number: ");
    scanf("%lf", &number);

    NormalizedView* normalizedView = normalizedViewForDouble(number);
    printf("Normalized view: ");
    normalizedViewPrint(normalizedView, stdout);
    normalizedViewFree(normalizedView);
}
