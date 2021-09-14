#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

bool* calculateEratosthenesSieve(int maxN)
{
    bool* sieve = calloc(maxN + 1, sizeof(bool));

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

    return sieve;
}

int main()
{
    setbuf(stdout, 0);

    int maxN;
    printf("Input max N:");
    scanf("%d", &maxN);

    bool* sieve = calculateEratosthenesSieve(maxN);
    printf("Prime numbers <= N: ");
    for (int i = 2; i <= maxN; i++) {
        if (sieve[i]) {
            printf("%d ", i);
        }
    }

    free(sieve);

    return 0;
}
