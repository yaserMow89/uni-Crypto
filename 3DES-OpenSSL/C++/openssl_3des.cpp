#include <iostream>
#include <cstring>
#include <iomanip>
#include <openssl/des.h>

void triple_des_encrypt(const unsigned char *input, size_t input_length, unsigned char *output, DES_key_schedule ks1, DES_key_schedule ks2, DES_key_schedule ks3) {
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

        // First encryption
        DES_encrypt1(reinterpret_cast<DES_LONG*>(&des_input), &ks1, DES_ENCRYPT);

        // Second decryption
        DES_encrypt1(reinterpret_cast<DES_LONG*>(&des_input), &ks2, DES_DECRYPT);

        // Third encryption
        DES_encrypt1(reinterpret_cast<DES_LONG*>(&des_input), &ks3, DES_ENCRYPT);

        // Copy the result to the output
        for (size_t i = 0; i < 8; ++i) {
            output[block * 8 + i] = des_input[i];
        }
    }
}

void triple_des_decrypt(const unsigned char *input, size_t input_length, unsigned char *output, DES_key_schedule ks1, DES_key_schedule ks2, DES_key_schedule ks3) {
    size_t num_blocks = (input_length + 7) / 8;  // Calculate the number of 8-byte blocks needed

    for (size_t block = 0; block < num_blocks; ++block) {
        DES_cblock des_input, des_output;

        for (size_t i = 0; i < 8; ++i) {
            des_input[i] = input[block * 8 + i];
        }

        // First decryption
        DES_encrypt1(reinterpret_cast<DES_LONG*>(&des_input), &ks3, DES_DECRYPT);

        // Second encryption
        DES_encrypt1(reinterpret_cast<DES_LONG*>(&des_input), &ks2, DES_ENCRYPT);

        // Third decryption
        DES_encrypt1(reinterpret_cast<DES_LONG*>(&des_input), &ks1, DES_DECRYPT);

        // Copy the result to the output
        for (size_t i = 0; i < 8; ++i) {
            if ((block * 8 + i) < input_length) {
                output[block * 8 + i] = des_input[i];
            }
        }
    }
}

int main() {
    DES_cblock key1, key2, key3;
    // Initialize key1, key2, and key3 with your actual keys
    // For demonstration purposes, let's assume they are all zero-initialized.
    std::memset(key1, 0, 8);
    std::memset(key2, 0, 8);
    std::memset(key3, 0, 8);

    DES_key_schedule ks1, ks2, ks3;
    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    const char *plaintext = "The quick brown fox jumps over the lazy dog";
    size_t plaintext_length = std::strlen(plaintext);

    unsigned char ciphertext[128];
    unsigned char decrypted[128];

    // Encrypt
    triple_des_encrypt(reinterpret_cast<const unsigned char *>(plaintext), plaintext_length, ciphertext, ks1, ks2, ks3);
    std::cout << "Ciphertext: ";
    for (size_t i = 0; i < plaintext_length; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ciphertext[i]);
    }
    std::cout << std::dec << std::endl;

    // Decrypt
    triple_des_decrypt(ciphertext, plaintext_length, decrypted, ks1, ks2, ks3);
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}
