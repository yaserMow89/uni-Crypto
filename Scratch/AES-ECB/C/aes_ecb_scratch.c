#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define AES_SIZE 16 
#define NUM_ROUNDS 10

void AES_encrypt(unsigned char * plain_text, unsigned char * key);

void aes_ecb_encrypt(unsigned char * plain_text, unsigned char* key, int text_length);
void aes_ecb_decrypt(unsigned char * plain_text, unsigned char* key, int text_length);

void KeyExpansion( unsigned char* inputKey,  unsigned char* expandedKeys);
void AddRoundKey(unsigned char* plain_text, unsigned char* roundKey);
void ReverseShiftRows(unsigned char* plain_text);
void ReverseSubBytes(unsigned char* state);
void ReverseMixColumns(unsigned char* plain_text);

void AES_decrypt(unsigned char * plain_text,  unsigned char * key);

unsigned char s_box[256] =
{
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

unsigned char inv_s[256] =
{
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};
    
unsigned char rcon[AES_SIZE] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a};

void _print_hex(const char* label, const unsigned char* data, int length) {
    
    printf("%s in Hex:\t", label);
    
    for (int i = 0; i < length; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n"); 
}

unsigned char gmul(unsigned char rhs, unsigned char lhs) {
    
    unsigned char peasant = 0;
    unsigned int irreducible = 0x11b;
    while (lhs) {
        if (lhs & 1) {
            peasant ^= rhs;
        }
        if (rhs & 0x80) {
            rhs = (rhs << 1) ^ irreducible;
        } else {
            rhs <<= 1;
        }
        lhs >>= 1;
    }
    return peasant;
}

unsigned char* key_expansion(const unsigned char* key) {
    unsigned char* expanded_key = (unsigned char*)malloc(AES_SIZE * (NUM_ROUNDS + 1));
    memcpy(expanded_key, key, AES_SIZE);
    for (int i = AES_SIZE; i < AES_SIZE * (NUM_ROUNDS + 1); i += 4) {
        unsigned char temp[4];
        memcpy(temp, expanded_key + i - 4, 4);
        if (i % AES_SIZE == 0) {
            
            unsigned char t = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = t;
            
            for (int j = 0; j < 4; j++) {
                temp[j] = s_box[temp[j]];
            }
            temp[0] ^= rcon[i / AES_SIZE];
        }
        for (int j = 0; j < 4; j++) {
            expanded_key[i + j] = expanded_key[i - AES_SIZE + j] ^ temp[j];
        }
    }
    return expanded_key;
}

void MixColumns(unsigned char* state) {
    unsigned char tmp[16];
    for (int i = 0; i < 4; ++i) {
        tmp[4*i+0] = gmul(0x02, state[4*i+0]) ^ gmul(0x03, state[4*i+1]) ^ state[4*i+2] ^ state[4*i+3];
        tmp[4*i+1] = state[4*i+0] ^ gmul(0x02, state[4*i+1]) ^ gmul(0x03, state[4*i+2]) ^ state[4*i+3];
        tmp[4*i+2] = state[4*i+0] ^ state[4*i+1] ^ gmul(0x02, state[4*i+2]) ^ gmul(0x03, state[4*i+3]);
        tmp[4*i+3] = gmul(0x03, state[4*i+0]) ^ state[4*i+1] ^ state[4*i+2] ^ gmul(0x02, state[4*i+3]);
    }
    memcpy(state, tmp, 16);
}

void ShiftRows(unsigned char* state) {
    unsigned char tmp[16];
    
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            tmp[r + 4*c] = state[r + 4*((c + r) % 4)];
        }
    }
    memcpy(state, tmp, 16);
}

void AES_encrypt(unsigned char * plain_text, unsigned char * key) {
    unsigned char* expanded_key = key_expansion(key);
    
    for (int i = 0; i < AES_SIZE; i++) {
        plain_text[i] ^= expanded_key[i];
    }
    for (int round = 1; round < NUM_ROUNDS; round++) {
        
        for (int i = 0; i < AES_SIZE; i++) {
            plain_text[i] = s_box[plain_text[i]];
        }
        
        ShiftRows(plain_text);
        
        MixColumns(plain_text);
        
        for (int i = 0; i < AES_SIZE; i++) {
            plain_text[i] ^= expanded_key[round * AES_SIZE + i];
        }
    }
    
    for (int i = 0; i < AES_SIZE; i++) {
        plain_text[i] = s_box[plain_text[i]];
    }
    ShiftRows(plain_text);
    for (int i = 0; i < AES_SIZE; i++) {
        plain_text[i] ^= expanded_key[NUM_ROUNDS * AES_SIZE + i];
    }
    free(expanded_key);
}

void AES_decrypt(unsigned char * plain_text, unsigned char * key) {
    unsigned char* expandedKey = (unsigned char*)malloc(AES_SIZE * (NUM_ROUNDS + 1));
    KeyExpansion(key, expandedKey);
    AddRoundKey(plain_text, expandedKey + (AES_SIZE * NUM_ROUNDS));
    ReverseShiftRows(plain_text);
    ReverseSubBytes(plain_text);
    for (int i = NUM_ROUNDS - 1; i >= 1; i--) {
        AddRoundKey(plain_text, expandedKey + (AES_SIZE * i));
        ReverseMixColumns(plain_text);
        ReverseShiftRows(plain_text);
        ReverseSubBytes(plain_text);
    }
    AddRoundKey(plain_text, expandedKey);
    free(expandedKey);
}
void KeyExpansion( unsigned char* inputKey,  unsigned char* expandedKeys) {
	for (int i = 0; i < AES_SIZE; i++) {
		expandedKeys[i] = inputKey[i];
	}
	int bytesGenerated = AES_SIZE;
	int rcon_location = 1;
	unsigned char key_block[4];
	while (bytesGenerated < (AES_SIZE * (NUM_ROUNDS + 1))) {
		for (int i = 0; i < ((AES_SIZE * 8) / 32); i++) { 
			key_block[i] = expandedKeys[i + bytesGenerated - ((AES_SIZE * 8) / 32)];
		}
		if (bytesGenerated % AES_SIZE == 0) {
			unsigned char temp_val = key_block[0];
			key_block[0] = key_block[1];
			key_block[1] = key_block[2];
			key_block[2] = key_block[3];
			key_block[3] = temp_val;
			key_block[0] = s_box[key_block[0]];
			key_block[1] = s_box[key_block[1]];
			key_block[2] = s_box[key_block[2]];
			key_block[3] = s_box[key_block[3]];
			key_block[0] ^= rcon[rcon_location];
			rcon_location++;
		}
		for (int i = 0; i < 4; i++) {
			expandedKeys[bytesGenerated] = expandedKeys[bytesGenerated - AES_SIZE] ^ key_block[i];
			bytesGenerated++;
		}
	}
}
void AddRoundKey(unsigned char * plain_text, unsigned char * roundKey)
{
	for (int i = 0; i < AES_SIZE; i++) {
		plain_text[i] = plain_text[i] ^ roundKey[i];
	}
}
void ReverseShiftRows(unsigned char * plain_text) {
	unsigned char temp_block[AES_SIZE];
	for (int i = 0; i < AES_SIZE; i += 4) {
		
		temp_block[i] = plain_text[i];
		temp_block[(i + 5) % AES_SIZE] = plain_text[i+1];
		temp_block[(i + 10) % AES_SIZE] = plain_text[i+2];
		temp_block[(i + 15) % AES_SIZE] = plain_text[i+3];
	}
	for (int i = 0; i < AES_SIZE; i++) {
		plain_text[i] = temp_block[i];
	}
}
void ReverseSubBytes(unsigned char * state) {
	for (int i = 0; i < AES_SIZE; i++) {
		state[i] = inv_s[state[i]];
	}
}
void ReverseMixColumns(unsigned char *plain_text) {
	unsigned char temp_block[AES_SIZE];
	for (int i = 0; i < AES_SIZE; i += 4) { 
	
		temp_block[i] = gmul(plain_text[i], (unsigned char) 14) ^ gmul(plain_text[i + 1], (unsigned char)11) ^ 
			gmul(plain_text[i + 2], (unsigned char)13) ^ gmul(plain_text[i + 3], (unsigned char)9);
		temp_block[i + 1] = gmul(plain_text[i], (unsigned char) 9) ^ gmul(plain_text[i + 1], (unsigned char)14) ^ 
			gmul(plain_text[i + 2], (unsigned char)11) ^ gmul(plain_text[i + 3], (unsigned char)13);
		temp_block[i + 2] = gmul(plain_text[i], (unsigned char)13) ^ gmul(plain_text[i + 1], (unsigned char)9) ^ 
			gmul(plain_text[i + 2], (unsigned char)14) ^ gmul(plain_text[i + 3], (unsigned char)11);
		temp_block[i + 3] = gmul(plain_text[i], (unsigned char)11) ^ gmul(plain_text[i + 1], (unsigned char)13) ^ 
			gmul(plain_text[i + 2], (unsigned char)9) ^ gmul(plain_text[i + 3], (unsigned char)14);
	}
    for (int i = 0; i < AES_SIZE; i++) {
		plain_text[i] = temp_block[i];
	}
}
void aes_ecb_encrypt(unsigned char* plain_text, unsigned char* key, int text_length) {
    for (int i = 0; i < text_length; i += AES_SIZE) {
        AES_encrypt(plain_text + i, key);
    }
}
void aes_ecb_decrypt(unsigned char* cipher_text,  unsigned char* key, int text_length) {
    for (int i = 0; i < text_length; i += AES_SIZE) {
        AES_decrypt(cipher_text + i, key);
    }
}

int main() {
    printf(" ============================== AES ECB (C) ======================== \n");
    unsigned char plaintext[(AES_SIZE * 2) + 1] = { "Hello World12345" };
    unsigned char ciphertext[(AES_SIZE * 2) + 1]; 
    unsigned char key[AES_SIZE + 1] = { "123456789abcdefg" };
    printf("Original Plaintext in Hex:");
    _print_hex("\t", plaintext, 32);
    
    memcpy(ciphertext, plaintext, 32); 
    aes_ecb_encrypt(ciphertext, key, 32);
    printf("Ciphertext in Hex:");
    _print_hex("\t", ciphertext, 32);
    
    aes_ecb_decrypt(ciphertext, key, 32);
    printf("Decrypted Ciphertext in Hex:"); 
    _print_hex("\t", ciphertext, 32);
    return 0;
}
