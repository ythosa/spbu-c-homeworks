#include <stdio.h>

long long calculateFib(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    long long fibPrevPrev = 0;
    long long fibPrev = 1;
    long long result = 0;

    for (int i = 2; i <= n; i++) {
        result = fibPrevPrev + fibPrev;
        fibPrevPrev = fibPrev;
        fibPrev = result;
    }

    return result;
}

int main()
{
    printf("Input N - Nth Fibonacci element: ");

    int n = 0;
    scanf("%d", &n);
    printf("Result: %lld", calculateFib(n - 1));

    return 0;
}
