#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char round_keys[16][49];
char pt[1024] = "";

char* byteToBinary(char byte) {
    char* binary = (char*)malloc(9); // 8 bits + '\0'
    int index = 7;
    while (byte > 0) {
        binary[index--] = (byte % 2 == 0 ? '0' : '1');
        byte /= 2;
    }
    while (index >= 0) {
        binary[index--] = '0';
    }
    binary[8] = '\0';
    return binary;
}

char* binaryToHex(char* binaryInput) 
{
    //printf("%s: The length is : %ld\n", binaryInput, strlen(binaryInput));
    //char* paddedBinary = (char*)malloc(sizeof(char) * strlen(binaryInput) + 1);
    char paddedBinary[strlen(binaryInput)+1];
    strcpy(paddedBinary, binaryInput);
    while (strlen(paddedBinary) % 4 != 0) {
        char temp[(strlen(paddedBinary) + 2)];
        strcpy(temp, "0");
        strcat(temp, paddedBinary);
        memset(paddedBinary, 0, strlen(binaryInput));
        strcpy(paddedBinary, temp);
        memset(temp, 0, strlen(temp));
    }
    char hexString[(strlen(paddedBinary) / 4 + 1)];
    hexString[strlen(hexString) - 1] = '\0';
    for (int i = 0; i < strlen(paddedBinary); i += 4) {
        char nibble[5];
        strncpy(nibble, paddedBinary + i, 4);
        nibble[4] = '\0';
        int decimal = strtol(nibble, NULL, 2);
        char hexDigit[2];
        sprintf(hexDigit, "%X", decimal);
        strcat(hexString, hexDigit);
    }
    //free(paddedBinary);
    strcpy(pt, hexString);
    pt[strlen(hexString)] = '\0';
    return pt;
}

char* stringToBinary(char* input) {
    char* binaryString = (char*)malloc(strlen(input) * 8 + 1);
    binaryString[0] = '\0';
    for (int i = 0; i < strlen(input); i++) {
        char byteStr[9];
        sprintf(byteStr, "%s", byteToBinary(input[i]));
        strcat(binaryString, byteStr);
    }
    return binaryString;
}

char* stringToHex(char* input) {
    char* hexString = (char*)malloc(strlen(input) * 2 + 1);
    hexString[0] = '\0';
    for (int i = 0; i < strlen(input); i++) {
        char hexDigit[3];
        sprintf(hexDigit, "%02X", input[i]);
        strcat(hexString, hexDigit);
    }
    return hexString;
}

char* hexToString(char* hexString) {
    char* result = (char*)malloc(strlen(hexString) / 2 + 1);
    result[0] = '\0';
    for (int i = 0; i < strlen(hexString); i += 2) {
        char hexDigit[3];
        strncpy(hexDigit, hexString + i, 2);
        hexDigit[2] = '\0';
        int decimal = strtol(hexDigit, NULL, 16);
        result[i / 2] = decimal;
    }
    result[strlen(hexString) / 2] = '\0';
    return result;
}

char* binaryToString(char* binaryInput) {
    char* result = (char*)malloc(strlen(binaryInput) / 8 + 1);
    result[0] = '\0';
    for (int i = 0; i < strlen(binaryInput); i += 8) {
        char byteStr[9];
        strncpy(byteStr, binaryInput + i, 8);
        byteStr[8] = '\0';
        int decimal = strtol(byteStr, NULL, 2);
        result[i / 8] = decimal;
    }
    result[strlen(binaryInput) / 8] = '\0';
    return result;
}

char* convertDecimalToBinary(int decimal) {
    char* binary = (char*)malloc(5);
    binary[4] = '\0';
    int index = 3;
    while (decimal != 0) {
        binary[index] = (decimal % 2 == 0 ? '0' : '1');
        decimal = decimal / 2;
        index--;
    }
    while (index >= 0) {
        binary[index] = '0';
        index--;
    }
    return binary;
}

int convertBinaryToDecimal(char* binary) {
    int decimal = 0;
    int counter = 0;
    int size = strlen(binary);
    for (int i = size - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += 1 << counter;
        }
        counter += 1;
    }
    return decimal;
}

char* shift_left_once(char* key_chunk) {
    char* shifted = (char*)malloc(strlen(key_chunk) + 1);
    strcpy(shifted, key_chunk + 1);
    shifted[strlen(key_chunk) - 1] = key_chunk[0];
    shifted[strlen(key_chunk)] = '\0';
    return shifted;
}

char* shift_left_twice(char* key_chunk) {
    char* shifted = (char*)malloc(strlen(key_chunk) + 1);
    strcpy(shifted, key_chunk + 2);
    strncat(shifted, key_chunk, 2);
    shifted[strlen(key_chunk)] = '\0';
    return shifted;
}

char* Xor(char* a, char* b) {
    char* result = (char*)malloc(strlen(a) + 1);
    result[0] = '\0';
    for (int i = 0; i < strlen(b); i++) {
        if (a[i] != b[i]) {
            strcat(result, "1");
        } else {
            strcat(result, "0");
        }
    }
    return result;
}

void generate_keys(char* key) {
    int pc1[56] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
    };
    int pc2[48] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    };
    char perm_key[57];
    perm_key[56] = '\0';
    for (int i = 0; i < 56; i++) {
        perm_key[i] = key[pc1[i] - 1];
    }
    char left[29];
    char right[29];
    strncpy(left, perm_key, 28);
    left[28] = '\0';
    strncpy(right, perm_key + 28, 28);
    right[28] = '\0';
    for (int i = 0; i < 16; i++) {
        if (i == 0 || i == 1 || i == 8 || i == 15) {
            char* temp = shift_left_once(left);
            //free(left);
            strcpy(left, temp);
            temp = shift_left_once(right);
            //free(right);
            strcpy(right, temp);
        } else {
            char* temp = shift_left_twice(left);
            //free(left);
            strcpy(left, temp);
            temp = shift_left_twice(right);
            //free(right);
            strcpy(right, temp);
        }
        char combined_key[57];
        combined_key[56] = '\0';
        strcpy(combined_key, left);
        strcat(combined_key, right);
        char round_key[49];
        round_key[48] = '\0';
        for (int j = 0; j < 48; j++) {
            round_key[j] = combined_key[pc2[j] - 1];
        }
        strcpy(round_keys[i], round_key);
    }
}

char* desEnc(char* block) {
    int initial_permutation[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };
    int expansion_table[48] = {
        32, 1, 2, 3, 4, 5, 4, 5,
        6, 7, 8, 9, 8, 9, 10, 11,
        12, 13, 12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21, 20, 21,
        22, 23, 24, 25, 24, 25, 26, 27,
        28, 29, 28, 29, 30, 31, 32, 1
    };
    int substition_boxes[8][4][16] = {
        {
            {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
            {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
            {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
            {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
        },
        {
            {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
            {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
            {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
            {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7}
        },
        {
            {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
            {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
            {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
            {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
        },
        {
            {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
            {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
            {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
            {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
        },
        {
            {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
            {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
            {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
            {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
        },
        {
            {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
            {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
            {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
            {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1}
        },
        {
            {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
            {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
            {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
            {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
        },
        {
            {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
            {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
            {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
            {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
        }
    };
    int permutation_tab[32] = {
        16, 7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9,
        19, 13, 30, 6, 22, 11, 4, 25
    };
    int inverse_permutation[64] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
    };
    char perm[65];
    perm[64] = '\0';
    for (int i = 0; i < 64; i++) {
        perm[i] = block[initial_permutation[i] - 1];
    }
    char left[33];
    char right[33];
    strncpy(left, perm, 32);
    left[32] = '\0';
    strncpy(right, perm + 32, 32);
    right[32] = '\0';
    for(int j= 0; j < 3; j++)
    {
        for (int i = 0; i < 16; i++) 
        {
            char right_expanded[49];
            right_expanded[48] = '\0';
            for (int j = 0; j < 48; j++) 
            {
                right_expanded[j] = right[expansion_table[j] - 1];
            }
            char* xored = Xor(round_keys[i], right_expanded);
            char res[33];
            res[32] = '\0';
            for (int j = 0; j < 8; j++) 
            {
                char row1[3];
                row1[0] = xored[j * 6];
                row1[1] = xored[j * 6 + 5];
                row1[2] = '\0';
                int row = convertBinaryToDecimal(row1);
                char col1[5];
                strncpy(col1, xored + j * 6 + 1, 4);
                col1[4] = '\0';
                int col = convertBinaryToDecimal(col1);
                int val = substition_boxes[j][row][col];
                strcat(res, convertDecimalToBinary(val));
            }
            char perm2[33];
            perm2[32] = '\0';
            for (int j = 0; j < 32; j++) 
            {
                perm2[j] = res[permutation_tab[j] - 1];
            }
            xored = Xor(perm2, left);
            strcpy(left, xored);
            if (i < 15) 
            {
                char temp[33];
                strcpy(temp, right);
                strcpy(right, xored);
                strcpy(left, temp);
            }
        }
        char combined_text[65];
        combined_text[64] = '\0';
        strcpy(combined_text, left);
        strcat(combined_text, right);
        char* ciphertext = (char*)malloc(65);
        ciphertext[64] = '\0';
        for (int i = 0; i < 64; i++) 
        {
            ciphertext[i] = combined_text[inverse_permutation[i] - 1];
        }
        return ciphertext;
    }
}

char* desDecryption(char* ciphertext) {
    int i = 15;
    int j = 0;
    while (i > j) {
        char temp[49];
        strcpy(temp, round_keys[i]);
        strcpy(round_keys[i], round_keys[j]);
        strcpy(round_keys[j], temp);
        i -= 1;
        j += 1;
    }
    char* decrypted = desEnc(ciphertext);
    return decrypted;
}

char* genKey() {
    int keySize = 64;
    long keyBits = rand() & ((1L << keySize) - 1);
    char* key = (char*)malloc(keySize + 1);
    key[keySize] = '\0';
    for (int i = keySize - 1; i >= 0; i--) {
        key[i] = (keyBits & 1) + '0';
        keyBits >>= 1;
    }
    return key;
}

char* pad(char* input_str) {
    int padding_size = 8 - (strlen(input_str) % 8);
    if (padding_size != 8) {
        char* temp = (char*)malloc(strlen(input_str) + padding_size + 1);
        strcpy(temp, input_str);
        for (int i = 0; i < padding_size; i++) {
            temp[strlen(input_str) + i] = padding_size + '0';
        }
        temp[strlen(input_str) + padding_size] = '\0';
        return temp;
    }
    return input_str;
}

char* des_encrypt_text(char* pt_string) {
    char* padded_pt = pad(pt_string);
    
    // Calculate the number of blocks
    size_t num_blocks = strlen(padded_pt) / 8;

    // Allocate memory for pointers to blocks
    char** blocks = (char**)malloc(num_blocks * sizeof(char*));
    if (blocks == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    // Allocate memory for each block
    for (size_t i = 0; i < num_blocks; i++) {
        blocks[i] = (char*)malloc(9); // Allocate space for 8 characters + null terminator
        if (blocks[i] == NULL) {
            // Handle memory allocation failure
            // Free previously allocated memory before returning
            for (size_t j = 0; j < i; j++) {
                free(blocks[j]);
            }
            free(blocks);
            return NULL;
        }
        // Copy each block into allocated memory
        strncpy(blocks[i], padded_pt + i * 8, 8);
        blocks[i][8] = '\0';
    }

    // Allocate memory for encrypted blocks
    char** encrypted_blocks = (char**)malloc(num_blocks * sizeof(char*));
    if (encrypted_blocks == NULL) {
        // Handle memory allocation failure
        // Free previously allocated memory before returning
        for (size_t i = 0; i < num_blocks; i++) {
            free(blocks[i]);
        }
        free(blocks);
        return NULL;
    }

    // Encrypt each block
    for (size_t i = 0; i < num_blocks; i++) {
        char* ct = desEnc(stringToBinary(blocks[i]));
        if (ct == NULL) {
            // Handle encryption failure
            // Free allocated memory before returning
            for (size_t j = 0; j < i; j++) {
                free(encrypted_blocks[j]);
            }
            free(encrypted_blocks);
            for (size_t j = 0; j < num_blocks; j++) {
                free(blocks[j]);
            }
            free(blocks);
            return NULL;
        }
        encrypted_blocks[i] = ct;
    }

    // Calculate the length of the encrypted text
    size_t encrypted_text_length = num_blocks * 64;

    // Allocate memory for encrypted text
    char* encrypted_text = (char*)malloc(encrypted_text_length + 1);
    if (encrypted_text == NULL) {
        // Handle memory allocation failure
        // Free allocated memory before returning
        for (size_t i = 0; i < num_blocks; i++) {
            free(encrypted_blocks[i]);
            free(blocks[i]);
        }
        free(encrypted_blocks);
        free(blocks);
        return NULL;
    }
    encrypted_text[encrypted_text_length] = '\0'; // Null-terminate the string

    // Concatenate encrypted blocks to form encrypted text
    for (size_t i = 0; i < num_blocks; i++) {
        strcat(encrypted_text, encrypted_blocks[i]);
        free(encrypted_blocks[i]); // Free memory allocated for each encrypted block
    }

    // Free allocated memory
    free(encrypted_blocks);
    for (size_t i = 0; i < num_blocks; i++) {
        free(blocks[i]);
    }
    free(blocks);

    return encrypted_text;
}

char* des_decrypt_text(char* ct_string) 
{
    //printf("LEN: %ld", strlen(ct_string));
    char** blocks = (char**)malloc(strlen(ct_string) / 64 * sizeof(char*));
    for (int i = 0; i < strlen(ct_string); i += 64) {
         blocks[i / 64] = (char*)malloc(65);
         strncpy(blocks[i / 64], ct_string + i, 64);
         blocks[i / 64][64] = '\0';
     }
     char** decrypted_blocks = (char**)malloc(strlen(ct_string) / 64 * sizeof(char*));
     for (int i = 0; i < strlen(ct_string) / 64; i++) {
         char* block = blocks[i];
         char* decrypted = desDecryption(block);
         decrypted_blocks[i] = decrypted;
     }
     char* decrypted_text = (char*)malloc(strlen(ct_string) + 1);
     decrypted_text[0] = '\0';
     for (int i = 0; i < strlen(ct_string) / 64; i++) {
         strcat(decrypted_text, decrypted_blocks[i]);
     }
    decrypted_text = realloc(decrypted_text, strlen(decrypted_text) + 1);
    return decrypted_text;
}


int main() 
{

    printf (" =========================== 3DES (C) =================================== \n");
    char my_key[256] = "101010101011101100001001000110000010011100110110110011001101110110101010101110110000100100011000001001110011011011001100110111011010101010111011000010010001100000100111001101101100110011011101";
    char *ptString = "I got 1 in ASEL ";
    printf ("Plaintext is:  %s\n ", stringToHex(ptString));

    if (strlen(my_key) == 192 && strlen(ptString) > 0) 
    {
        char key1[65], key2[65], key3[65];
        strncpy(key1, my_key, 64);
        key1[64] = '\0';
        strncpy(key2, my_key + 64, 64);
        key2[64] = '\0';
        strncpy(key3, my_key + 128, 64);
        key3[64] = '\0';

        generate_keys(key1);
        char* encrypted_text = des_encrypt_text(ptString);

        generate_keys(key2);
        encrypted_text = des_decrypt_text(encrypted_text);

        generate_keys(key3);
        encrypted_text = des_encrypt_text(binaryToString(encrypted_text));
        printf("Encrypte text is: %s\n", binaryToHex(encrypted_text));
        char* decrypted_text = des_decrypt_text(encrypted_text);

        generate_keys(key2);
        decrypted_text = des_encrypt_text(binaryToString(decrypted_text));

        generate_keys(key1);
        decrypted_text = des_decrypt_text(decrypted_text);

        printf("Decrypted Text is: %s\n",binaryToHex(decrypted_text));
    }
    return 0;
}