#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

long long power(long long x, unsigned long long y, long long p) {
    long long result = 1;
    x = x % p;

    while (y > 0) {
        if (y & 1) {
            result = (result * x) % p;
        }

        y = y >> 1;
        x = (x * x) % p;
    }

    return result;
}

bool isPrimeMillerRabin(long long n, int k) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 4);
        long long x = power(a, d, n);

        if (x == 1 || x == n - 1) continue;

        for (long long r = 1; r < d; r *= 2) {
            x = power(x, 2, n);
            if (x == 1) return false;
            if (x == n - 1) break;
        }

        if (x != n - 1) return false;
    }

    return true;
}

int main() {
    long long n;
    int k;

    printf("Enter an integer to test for primality: ");
    scanf("%lld", &n);

    printf("Enter the number of iterations (recommended >= 5): ");
    scanf("%d", &k);

    if (isPrimeMillerRabin(n, k)) {
        printf("%lld is probably prime.\n", n);
    } else {
        printf("%lld is composite.\n", n);
    }

    return 0;
}
