#include "DES.h" //Replace with <DES.h> after installing the library
#include <stdio.h>



DES Des;

void printArrayHex(const unsigned char output[8]) {
    for (int i = 0; i < 8; i++) {
        if (output[i] < 0x10) {
            printf("0");
        }
        printf("%02X ", output[i]);
    }
    printf("\n");
}

void des() {
    unsigned char out_bytes[8];
    unsigned char in_bytes[] = {101, 110, 99, 114, 121, 112, 116, 100};
    unsigned char key[] = {0x62, 0x65, 0x64, 0x61, 0x6E, 0x67, 0x61, 0x74};
    
    printf("\n========= DES test ==========\n");
    
    printf("Plaintext Hex: ");
    printArrayHex(in_bytes);

    // Encrypt
    printf("Encrypted Hex: ");
    Des.encrypt(out_bytes, in_bytes, key);
    printArrayHex(out_bytes);

    // Replace contents of in with contents of out
    for (int i = 0; i < 8; i++) {
        in_bytes[i] = out_bytes[i];
    }

    // Decrypt
    printf("Decrypted Hex: ");
    Des.decrypt(out_bytes, in_bytes, key);
    printArrayHex(out_bytes);
}

void three_des() {
    unsigned char out_bytes[8];
    unsigned char in_bytes[] = {101, 110, 99, 114, 121, 112, 116, 100};
    unsigned char key[] = { 0x62, 0x65, 0x64, 0x61, 0x6E, 0x67, 0x61, 0x74,
                   0x5e, 0xf7, 0x20, 0x15, 0x37, 0x98, 0x38, 0x3b,
                   0x62, 0x65, 0x64, 0x61, 0x6E, 0x67, 0x61, 0x74};
    
    printf("\n========= 3DES test ==========\n");
    
    printf("Plaintext Hex: ");
    printArrayHex(in_bytes);

    // Encrypt
    printf("Encrypted Hex: ");
    Des.tripleEncrypt(out_bytes, in_bytes, key);
    printArrayHex(out_bytes);

    // Replace contents of in with contents of out
    for (int i = 0; i < 8; i++) {
        in_bytes[i] = out_bytes[i];
    }

    // Decrypt
    printf("Decrypted Hex: ");
    Des.tripleDecrypt(out_bytes, in_bytes, key);
    printArrayHex(out_bytes);
}


void setup() {
  Serial.begin(115200);
  Serial.println("DES & TDES ON ARDUINO!");
}

void loop() {
  des();
  three_des();
  
  delay(6000);
}
