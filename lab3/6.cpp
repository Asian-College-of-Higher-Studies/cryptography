#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

long long mod_pow(long long base, long long exponent, long long modulus) {
    if (exponent == 0) return 1;
    if (exponent % 2 == 0) {
        long long temp = mod_pow(base, exponent / 2, modulus);
        return (temp * temp) % modulus;
    } else {
        return (base * mod_pow(base, exponent - 1, modulus)) % modulus;
    }
}

int is_prime(long long num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

long long generate_random_prime(long long min, long long max) {
    long long rand_num;
    do {
        rand_num = (rand() % (max - min + 1)) + min;
    } while (!is_prime(rand_num));
    return rand_num;
}

void generate_keys(long long *p, long long *g, long long *x, long long *y) {
    *p = generate_random_prime(100, 1000);
    for (*g = 2; *g < *p - 1; (*g)++) {
        if (mod_pow(*g, *p - 1, *p) == 1) break;
    }
    *x = (rand() % (*p - 3)) + 2;
    *y = mod_pow(*g, *x, *p);
}

void encrypt(long long plaintext, long long p, long long g, long long y, long long *c1, long long *c2) {
    long long k = (rand() % (p - 2)) + 1;
    *c1 = mod_pow(g, k, p);
    *c2 = (plaintext * mod_pow(y, k, p)) % p;
}

long long decrypt(long long c1, long long c2, long long p, long long x) {
    long long s = mod_pow(c1, x, p);
    long long s_inverse = mod_pow(s, p - 2, p);
    long long plaintext = (c2 * s_inverse) % p;
    return plaintext;
}

int main() {
    long long p, g, x, y;
    long long plaintext, ciphertext1, ciphertext2, decrypted_text;

    srand(time(NULL));

    generate_keys(&p, &g, &x, &y);

    printf("Enter the plaintext message (an integer): ");
    scanf("%lld", &plaintext);

    encrypt(plaintext, p, g, y, &ciphertext1, &ciphertext2);
    decrypted_text = decrypt(ciphertext1, ciphertext2, p, x);

    printf("Public Key (p, g, y): (%lld, %lld, %lld)\n", p, g, y);
    printf("Private Key (x): %lld\n", x);
    printf("Ciphertext (c1, c2): (%lld, %lld)\n", ciphertext1, ciphertext2);
    printf("Decrypted Message: %lld\n", decrypted_text);

    return 0;
}
