#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

void single_des_encrypt(const unsigned char *input, size_t input_length, unsigned char *output, DES_key_schedule ks) {
    size_t num_blocks = (input_length + 7) / 8;  // Calculate the number of 8-byte blocks needed
    size_t remaining_bytes = input_length % 8;

    for (size_t block = 0; block < num_blocks; ++block) {
        DES_cblock des_input, des_output;

        for (size_t i = 0; i < 8; ++i) {
            if ((block * 8 + i) < input_length) {
                des_input[i] = input[block * 8 + i];
            } else {
                des_input[i] = 0;  // Pad with zeros if input is not a multiple of 8
            }
        }

        // Perform single DES encryption
        DES_encrypt1(&des_input, &ks, DES_ENCRYPT);

        // Copy the result to the output
        for (size_t i = 0; i < 8; ++i) {
            output[block * 8 + i] = des_input[i];
        }
    }
}

void single_des_decrypt(const unsigned char *input, size_t input_length, unsigned char *output, DES_key_schedule ks) {
    size_t num_blocks = (input_length + 7) / 8;  // Calculate the number of 8-byte blocks needed

    for (size_t block = 0; block < num_blocks; ++block) {
        DES_cblock des_input, des_output;

        for (size_t i = 0; i < 8; ++i) {
            des_input[i] = input[block * 8 + i];
        }

        // Perform single DES decryption
        DES_encrypt1(&des_input, &ks, DES_DECRYPT);

        // Copy the result to the output
        for (size_t i = 0; i < 8; ++i) {
            if ((block * 8 + i) < input_length) {
                output[block * 8 + i] = des_input[i];
            }
        }
    }
}

int main() {
    DES_cblock key;
    // Initialize key with your actual key
    // For demonstration purposes, let's assume it is zero-initialized.
    memset(key, 0, 8);

    DES_key_schedule ks;
    DES_set_key_unchecked(&key, &ks);

    const char *plaintext = "The quick fox jumps over the lazy dog";
    size_t plaintext_length = strlen(plaintext);

    unsigned char ciphertext[128];
    unsigned char decrypted[128];

    // Encrypt
    single_des_encrypt((const unsigned char *)plaintext, plaintext_length, ciphertext, ks);
    printf("Ciphertext: ");
    for (size_t i = 0; i < plaintext_length; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    // Decrypt
    single_des_decrypt(ciphertext, plaintext_length, decrypted, ks);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
