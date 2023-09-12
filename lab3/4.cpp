#include <stdio.h>
#include <math.h>

long long mod_pow(long long base, long long exponent, long long modulus) {
    if (exponent == 0) return 1;
    if (exponent % 2 == 0) {
        long long temp = mod_pow(base, exponent / 2, modulus);
        return (temp * temp) % modulus;
    } else {
        return (base * mod_pow(base, exponent - 1, modulus)) % modulus;
    }
}

int main() {
    long long p, g;
    long long a_private, b_private;
    long long A_public, B_public;
    long long secret_key_A, secret_key_B;

    printf("Enter a prime number (p): ");
    scanf("%lld", &p);

    printf("Enter a generator (g): ");
    scanf("%lld", &g);

    printf("Enter Alice's private key: ");
    scanf("%lld", &a_private);

    A_public = mod_pow(g, a_private, p);

    printf("Enter Bob's private key: ");
    scanf("%lld", &b_private);

    B_public = mod_pow(g, b_private, p);

    secret_key_A = mod_pow(B_public, a_private, p);
    secret_key_B = mod_pow(A_public, b_private, p);

    printf("Shared Secret Key computed by Alice: %lld\n", secret_key_A);
    printf("Shared Secret Key computed by Bob: %lld\n", secret_key_B);

    return 0;
}
