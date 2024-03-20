#include <mbedtls/aes.h>
#include <iostream>

#include <string.h>
using namespace std;

void print_hex(const char* label, const unsigned char* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; ++i) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

void ascii_to_bytes(const char* ascii_string, size_t len, unsigned char* byte_array) {
    for (size_t i = 0; i < len; ++i) {
        byte_array[i] = (unsigned char)ascii_string[i];
    }
}

void add_padding(const unsigned char* input, size_t input_len, unsigned char* padded_input, size_t block_size) {
    size_t padding_len = block_size - (input_len % block_size);
    memcpy(padded_input, input, input_len);
    memset(padded_input + input_len, (unsigned char)padding_len, padding_len);
}

void aes_cbc_encrypt(const char* key_ascii, const char* iv_ascii, const unsigned char* input, size_t input_len, unsigned char* output) {
    unsigned char key[16];
    unsigned char iv[16];

    ascii_to_bytes(key_ascii, 16, key);
    ascii_to_bytes(iv_ascii, 16, iv);

    mbedtls_aes_context aes;
    mbedtls_aes_setkey_enc(&aes, key, 128);

    size_t block_size = 16;
    size_t padded_len = (input_len / block_size + 1) * block_size;
    unsigned char padded_input[padded_len];

    add_padding(input, input_len, padded_input, block_size);

    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, padded_len, iv, padded_input, output);
    mbedtls_aes_free(&aes);

    print_hex("Plaintext", padded_input, padded_len);
}

void aes_cbc_decrypt(const char* key_ascii, const char* iv_ascii, const unsigned char* input, size_t input_len, unsigned char* output) {
    unsigned char key[16];
    unsigned char iv[16];

    ascii_to_bytes(key_ascii, 16, key);
    ascii_to_bytes(iv_ascii, 16, iv);

    mbedtls_aes_context aes;
    mbedtls_aes_setkey_dec(&aes, key, 128);

    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, input_len, iv, input, output);
    mbedtls_aes_free(&aes);

    print_hex("Plaintext", output, input_len);  // Print decrypted text as well
}

void setup() {
    Serial.begin(115200);
}

void loop() {
    unsigned long start_time = millis();
    std::cout <<" ============================== AES ECB with Library mbedtls (C++) ======================== " <<endl;
    const char* key_ascii = "123456789abcdefg";
    const char* iv_ascii = "0123456789abcdef";

    const char* plaintext = "Hello World12345";
    size_t plaintext_len = strlen(plaintext);

    size_t block_size = 16;
    size_t padded_len = (plaintext_len / block_size + 1) * block_size;
    unsigned char ciphertext[padded_len];
    unsigned char decrypted_text[padded_len];

    memset(ciphertext, 0, sizeof(ciphertext));
    memset(decrypted_text, 0, sizeof(decrypted_text));

    // Encrypt
    aes_cbc_encrypt(key_ascii, iv_ascii, (const unsigned char*)plaintext, plaintext_len, ciphertext);
    print_hex("Ciphertext", ciphertext, padded_len);

    // Decrypt
    aes_cbc_decrypt(key_ascii, iv_ascii, ciphertext, padded_len, decrypted_text);
    print_hex("Decrypted Text", decrypted_text, padded_len);

    std::cout << "Free Heap: " << ESP.getFreeHeap() << " bytes" << std::endl;
    unsigned long end_time = millis();
    std::cout << "Execution Time: " << (end_time - start_time) << " milliseconds" << std::endl;
    

    delay(1000);
}
