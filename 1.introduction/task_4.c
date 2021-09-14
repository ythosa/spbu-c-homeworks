#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

bool* calculate_eratosthenes_sieve(int max_n)
{
    bool* sieve = calloc(max_n + 1, sizeof(bool));

    for (int i = 0; i <= max_n; i++) {
        sieve[i] = true;
    }

    for (int i = 2; i * i <= max_n; i++) {
        if (!sieve[i]) {
            continue;
        }

        for (int j = i * i; j <= max_n; j += i) {
            sieve[j] = false;
        }
    }

    return sieve;
}

int main()
{
    setbuf(stdout, 0);

    int max_n;
    printf("Input max N:");
    scanf("%d", &max_n);

    bool* sieve = calculate_eratosthenes_sieve(max_n);
    printf("Prime numbers <= N: ");
    for (int i = 2; i <= max_n; i++) {
        if (sieve[i]) {
            printf("%d ", i);
        }
    }

    free(sieve);

    return 0;
}
