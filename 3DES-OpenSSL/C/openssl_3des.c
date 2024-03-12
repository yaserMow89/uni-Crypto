#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

void triple_des_encrypt(const unsigned char *input, unsigned char *output, size_t length, DES_key_schedule ks1, DES_key_schedule ks2, DES_key_schedule ks3) {
    size_t i;
    DES_cblock block;

    for (i = 0; i < length; i += 8) {
        // Copy the input block
        memcpy(block, input + i, 8);

        // Perform 3DES encryption
        DES_encrypt3(&block, &ks1, &ks2, &ks3);

        // Copy the result to the output
        memcpy(output + i, block, 8);
    }
}

void triple_des_decrypt(const unsigned char *input, unsigned char *output, size_t length, DES_key_schedule ks1, DES_key_schedule ks2, DES_key_schedule ks3) {
    size_t i;
    DES_cblock block;

    for (i = 0; i < length; i += 8) {
        // Copy the input block
        memcpy(block, input + i, 8);

        // Perform 3DES decryption
        DES_decrypt3(&block, &ks1, &ks2, &ks3);

        // Copy the result to the output
        memcpy(output + i, block, 8);
    }
}

int main() {
    DES_cblock key1, key2, key3;
    // Initialize key1, key2, and key3 with your actual keys
    // For demonstration purposes, let's assume they are all zero-initialized.
    memset(key1, 0, 8);
    memset(key2, 0, 8);
    memset(key3, 0, 8);

    DES_key_schedule ks1, ks2, ks3;
    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    const char *plaintext = "The quick brown fox jumps over the lazy dog";
    unsigned char ciphertext[128];
    unsigned char decrypted[128];

    // Encrypt
    triple_des_encrypt((const unsigned char *)plaintext, ciphertext, strlen(plaintext), ks1, ks2, ks3);
    printf("Ciphertext: ");
    for (size_t i = 0; i < strlen(plaintext); i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    // Decrypt
    triple_des_decrypt(ciphertext, decrypted, strlen(plaintext), ks1, ks2, ks3);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
