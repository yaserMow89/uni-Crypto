#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cstring>
#include "mbedtls/aes.h"
//#include <Arduino.h> // Include the Arduino library for ESP functions
using namespace std;

void _print_text(const char* label, const unsigned char* text, size_t text_size) {
    std::cout << label << ":\t";
    for (size_t i = 0; i < text_size; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(text[i]) << " ";
    }
    std::cout << std::endl;
}

mbedtls_aes_context aes;

size_t _length = 16;
// Not iv is not used in this AES ECB implementation, left for convinience
unsigned char iv[16] = "0123456789abcde";
unsigned char key[] = "123456789abcdefg";
unsigned char input[32] = "Hello World12345";
unsigned char encrypt_output[16];
unsigned char decrypt_output[16];

void _aes_encrypt(unsigned char* iv, size_t crypt_len, const unsigned char* input, unsigned char* output) {
    mbedtls_aes_setkey_enc(&aes, key, 128);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, input, output);
}

void _aes_decrypt(unsigned char* iv, size_t crypt_len, const unsigned char* input, unsigned char* output) {
    mbedtls_aes_setkey_dec(&aes, key, 128);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, input, output);
}

void _security_init(void) {
    mbedtls_aes_init(&aes);
}

void _security_deinit(void) {
    mbedtls_aes_free(&aes);
}


int main() {
    std::cout <<" ============================== AES ECB with mbedtls Library (C++) ======================== " << std::endl;
    _security_init();

    _aes_encrypt(iv, _length, input, encrypt_output);
    _aes_decrypt(iv, _length, encrypt_output, decrypt_output);

    _print_text("Input", input, sizeof(input));
    _print_text("Encrypted", encrypt_output, sizeof(encrypt_output));
    _print_text("Decrypted", decrypt_output, sizeof(decrypt_output));

    _security_deinit();
    return 0;
    }
