#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

bool isPrimitiveRoot(int a, int p) {
    if (gcd(a, p) != 1) {
        return false;
    }

    int phi = p - 1;
    int factors[phi];
    int factorCount = 0;

    for (int i = 2; i <= sqrt(phi); i++) {
        if (phi % i == 0) {
            factors[factorCount++] = i;

            while (phi % i == 0) {
                phi /= i;
            }
        }
    }

    if (phi > 1) {
        factors[factorCount++] = phi;
    }

    for (int i = 0; i < factorCount; i++) {
        int factor = factors[i];
        int exp = phi / factor;
        int result = 1;

        for (int j = 0; j < exp; j++) {
            result = (result * a) % p;
        }

        if (result == 1) {
            return false;
        }
    }

    return true;
}

int main() {
    int p;

    printf("Enter a prime number p: ");
    scanf("%d", &p);

    if (p <= 1) {
        printf("Please enter a prime number greater than 1.\n");
        return 1;
    }

    printf("Primitive roots modulo %d are:\n", p);

    for (int a = 2; a < p; a++) {
        if (isPrimitiveRoot(a, p)) {
            printf("%d ", a);
        }
    }

    printf("\n");

    return 0;
}

