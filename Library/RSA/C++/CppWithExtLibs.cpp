#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

// Function prototypes
long gcd(long a, long b);
long modPow(long base, long exponent, long modulus);
long modInverse(long a, long m);
void generateRSAKeys(long &n, long &e, long &d);

// Function prototypes for new encryption and decryption functions
long encryptChar(char msg, long e, long n);
char decryptChar(long cipher, long d, long n);
std::vector<long> encryptString(const std::string &msg, long e, long n);
std::string decryptString(const std::vector<long> &cipher, long d, long n);

// Utility function to calculate gcd
long gcd(long a, long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
// Utility function to perform modular exponentiation.
// It returns (base^exponent) % modulus
long modPow(long base, long exponent, long modulus) {
    long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1)   // If exponent is odd, multiply base with result
            result = (result * base) % modulus;
        exponent = exponent >> 1; // Divide the exponent by 2
        base = (base * base) % modulus;
    }
    return result;
}

// Utility function to find modular inverse of a under modulo m
// This function returns x such that (a*x) % m = 1
long modInverse(long a, long m) {
    a = a % m;
    for (long x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return 1; // Should never happen if m is prime
}

// Function to generate public and private keys
void generateRSAKeys(long &n, long &e, long &d) {
    // Two random prime numbers (small values for demonstration)
    long p = 61;
    long q = 53;
    n = p * q;
    long phi = (p - 1) * (q - 1);

    // Choose e such that e and phi(n) are coprime
    e = 3;
    while (gcd(e, phi) != 1) {
        e++;
    }

    // Calculate d as modInverse of e
    d = modInverse(e, phi);
}

// Function to encrypt a single character
long encryptChar(char msg, long e, long n) {
    return modPow(msg, e, n);
}

// Function to decrypt a single character
char decryptChar(long cipher, long d, long n) {
    return static_cast<char>(modPow(cipher, d, n));
}

// Encrypts a string
std::vector<long> encryptString(const std::string &msg, long e, long n) {
    std::vector<long> encryptedMsg;
    for (char c : msg) {
        encryptedMsg.push_back(encryptChar(c, e, n));
    }
    return encryptedMsg;
}

// Decrypts a string
std::string decryptString(const std::vector<long> &cipher, long d, long n) {
    std::string decryptedMsg;
    for (long c : cipher) {
        decryptedMsg.push_back(decryptChar(c, d, n));
    }
    return decryptedMsg;
}

int main() {
    srand(time(0)); // Initialize random seed based on current time

    long n, e, d;
    generateRSAKeys(n, e, d);

    std::string message = "Hello World"; // Example string to encrypt and decrypt
    std::cout << "Original Message = " << message << std::endl;

    std::vector<long> encryptedMsg = encryptString(message, e, n);
    std::cout << "Encrypted Message = ";
    for (long c : encryptedMsg) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    std::string decryptedMsg = decryptString(encryptedMsg, d, n);
    std::cout << "Decrypted Message = " << decryptedMsg << std::endl;

    return 0;
}