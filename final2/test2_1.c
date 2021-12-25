#include "stdio.h"

long long function(int n)
{
    long long previousResults[] = { -1, 0, 1 };
    if (n < 3)
        return previousResults[n];

    for (int i = 3; i <= n; i++) {
        long long result = 3 * previousResults[0] + 2 * previousResults[1] + previousResults[2];
        previousResults[0] = previousResults[1];
        previousResults[1] = previousResults[2];
        previousResults[2] = result;
    }

    return previousResults[2];
}

int main()
{
    int n = 0;
    printf("Input n (non negative integer): ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Error: n must be non negative integer!\n");

        return 0;
    }

    printf("Result: %lld", function(n));

    return 0;
}
