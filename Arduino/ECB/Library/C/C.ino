#include <stdio.h>
#include "mbedtls/aes.h"
void setup() {
    Serial.begin(115200);  // Initialize serial communication at a baud rate of 115200
}
void _print_text(const char* label, const unsigned char* text, size_t text_size) {
    printf("%s:\t", label);
    for (size_t i = 0; i < text_size; ++i) {
        printf("%02X ", text[i]);
    }
    printf("\n");
}

mbedtls_aes_context aes;

size_t _length = 16;
//Not iv is not being used, is legacy element from code iterations
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

void loop() {
      unsigned long start_time = millis();
    printf(" ============================== AES ECB mbedtls library (C) ======================== \n");

    _security_init();

    _aes_encrypt(iv, _length, input, encrypt_output);
    _aes_decrypt(iv, _length, encrypt_output, decrypt_output);

    _print_text("Input", input, sizeof(input));
    _print_text("Encrypted", encrypt_output, sizeof(encrypt_output));
    _print_text("Decrypted", decrypt_output, sizeof(decrypt_output));

    _security_deinit();

      // Followings are for measurement purposes

      printf("Free Heap: %u bytes\n", ESP.getFreeHeap());
  
  unsigned long end_time = millis(); // End timing
  printf("Execution Time: %lu milliseconds\n", end_time - start_time);
  delay(1000);
    
}
