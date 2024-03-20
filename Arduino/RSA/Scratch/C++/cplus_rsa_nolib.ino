#include <Arduino.h>

// Utility function to calculate gcd
long gcd(long a, long b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Utility function to find modular inverse
long modInverse(long a, long m) {
    a = a % m;
    for (long x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // Return -1 if inverse doesn't exist
}

// Utility function to perform modular exponentiation
long modPow(long base, long exponent, long modulus) {
    long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent & 1)
            result = (result * base) % modulus;
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Simple RSA encryption and decryption 
class SimpleRSA {
public:
    SimpleRSA(long p, long q) {
        if (!isPrime(p) || !isPrime(q))
            Serial.println("Both numbers must be prime.");
        else if (p == q)
            Serial.println("p and q can't be equal.");

        n = p * q;
        long phi = (p - 1) * (q - 1);
        
        // Choose e
        e = 3;
        while (e < phi && gcd(e, phi) != 1) {
            e += 2;
        }
        
        d = modInverse(e, phi);
    }

    long encrypt(long msg) const {
        if (msg < 0 || msg >= n)
            Serial.println("Message must be between 0 and n-1.");
        return modPow(msg, e, n);
    }

    long decrypt(long cipher) const {
        return modPow(cipher, d, n);
    }

private:
    long p, q, n, phi, e, d;

    bool isPrime(long number) {
        if (number <= 1) return false;
        for (long i = 2; i <= sqrt(number); i++) {
            if (number % i == 0) return false;
        }
        return true;
    }
};

SimpleRSA rsa(61, 53); // Instantiate SimpleRSA object with prime numbers

void setup() {
    Serial.begin(115200);  // Initialize serial communication at a baud rate of 115200
}

void loop() {
    unsigned long start_time = millis();

    Serial.println("============================== RSA NO Lib (C++) ========================\n");
    Serial.println("Original message: Hello World!");

    long encryptedMessage[] = { // Encrypted message
        rsa.encrypt('H'),
        rsa.encrypt('e'),
        rsa.encrypt('l'),
        rsa.encrypt('l'),
        rsa.encrypt('o'),
        rsa.encrypt(' '),
        rsa.encrypt('W'),
        rsa.encrypt('o'),
        rsa.encrypt('r'),
        rsa.encrypt('l'),
        rsa.encrypt('d'),
        rsa.encrypt('!')
    };

    Serial.print("Encrypted message: ");
    for (long m : encryptedMessage) {
        Serial.print(m);
        Serial.print(" ");
    }
    Serial.println();

    Serial.print("Decrypted message: ");
    for (long m : encryptedMessage) {
        Serial.print(static_cast<char>(rsa.decrypt(m)));
    }
    Serial.println();

// Print Free Heap
Serial.print("Free Heap: ");
Serial.print(ESP.getFreeHeap());
Serial.println(" bytes");

// Calculate and print Execution Time
unsigned long end_time = millis();
Serial.print("Execution Time: ");
Serial.print(end_time - start_time);
Serial.println(" milliseconds");
    delay(1000); // Delay for 1 second before repeating
}
