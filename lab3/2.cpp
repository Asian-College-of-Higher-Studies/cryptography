#include <stdio.h>

int eulerTotient(int n) {
    int result = n;

    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p;
            }
            result -= result / p;
        }
    }

    if (n > 1) {
        result -= result / n;
    }

    return result;
}

int main() {
    int n;

    printf("Enter an integer n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    int phi = eulerTotient(n);
    printf("Euler's Totient Function (f) of %d is %d\n", n, phi);

    return 0;
}
