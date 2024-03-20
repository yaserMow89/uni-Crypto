#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate (base^exponent) % modulus
long long modPow(long long base, long long exponent, long long modulus) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Function to calculate the Greatest Common Divisor (Euclidean algorithm)
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Naive function to find a modular multiplicative inverse
long long modInverse(long long a, long long m) {
    a = a % m;
    for (long long x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // If no inverse exists
}

int main() {
    // Example RSA setup (using very small and insecure numbers for simplicity)
    long long p = 61;
    long long q = 53;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 17; // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    long long d = modInverse(e, phi); // Compute d, the modular inverse of e mod phi

    // Example message to encrypt
    char message[] = "Hello World";
    printf("Original message: %s\n", message);

    // Encrypt the message
    printf("Encrypted message: ");
    for(int i = 0; message[i] != '\0'; i++) {
        long long encrypted = modPow(message[i], e, n);
        printf("%lld ", encrypted);
    }
    printf("\n");

    // Decrypt the message
    printf("Decrypted message: ");
    char decrypted[strlen(message) + 1]; // +1 for the null terminator
    int index = 0;
    for(int i = 0; message[i] != '\0'; i++) {
        long long encrypted = modPow(message[i], e, n);
        decrypted[index++] = modPow(encrypted, d, n);
    }
    decrypted[index] = '\0'; // Null-terminate the decrypted string
    printf("%s\n", decrypted);

    return 0;
}
