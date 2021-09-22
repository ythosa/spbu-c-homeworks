#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void calculateEratosthenesSieve(int maxN, bool* sieve)
{
    for (int i = 0; i <= maxN; i++) {
        sieve[i] = true;
    }

    for (int i = 2; i * i <= maxN; i++) {
        if (!sieve[i]) {
            continue;
        }

        for (int j = i * i; j <= maxN; j += i) {
            sieve[j] = false;
        }
    }
}

int main()
{
    int maxN = 0;
    printf("Input max N:");
    scanf("%d", &maxN);

    bool* sieve = calloc(maxN + 1, sizeof(bool));
    calculateEratosthenesSieve(maxN, sieve);
    printf("Prime numbers <= N: ");
    for (int i = 2; i <= maxN; i++) {
        if (sieve[i]) {
            printf("%d ", i);
        }
    }

    free(sieve);

    return 0;
}
