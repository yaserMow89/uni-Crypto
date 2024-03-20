#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

void init_openssl() {
    if (OPENSSL_VERSION_NUMBER < 0x10100000L) {
        OpenSSL_add_all_algorithms();  // Old versions of OpenSSL need this
        ERR_load_crypto_strings();
    }
}

void cleanup_openssl() {
    ERR_free_strings();
    EVP_cleanup();
}

int main() {
    init_openssl();

    int rc;

    // Generate RSA keys
    BIGNUM *bne = BN_new();
    rc = BN_set_word(bne, RSA_F4); // 65537
    if (rc != 1) {
        // handle error
    }

    RSA *rsa = RSA_new();
    rc = RSA_generate_key_ex(rsa, 2048, bne, NULL);
    if (rc != 1) {
        // handle error
    }

    // Encrypting a message
    const unsigned char message[] = "Hello World";
    unsigned char encrypted[256]; // Make sure this size is big enough to hold the encrypted data
    unsigned char decrypted[256];

    int encrypted_length = RSA_public_encrypt(strlen((char *)message) + 1, message, encrypted, rsa, RSA_PKCS1_PADDING);
    if (encrypted_length == -1) {
        // handle error
    }

    printf("Encrypted message:\n");
    for(int i = 0; i < encrypted_length; i++) {
        printf("%x", encrypted[i]);
    }
    printf("\n");

    // Decrypting the message
    int decrypted_length = RSA_private_decrypt(encrypted_length, encrypted, decrypted, rsa, RSA_PKCS1_PADDING);
    if (decrypted_length == -1) {
        // handle error
    }

    printf("Decrypted message: %s\n", decrypted);

    // Cleanup
    RSA_free(rsa);
    BN_free(bne);
    cleanup_openssl();

    return 0;
}
