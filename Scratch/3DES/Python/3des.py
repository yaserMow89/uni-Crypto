import random

round_keys = ["" for _ in range(16)]


"""
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Since 3des is using DES under the hood, this file has got 
no comments, please refer to the des code for looking 
into the comments
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
"""

def byteToBinary(byte):
    bits = bin(byte)[2:].zfill(8)
    return bits

def binaryToHex(binaryinput):
    paddedBinary = binaryinput
    while len(paddedBinary) % 4 != 0:
        paddedBinary = "0" + paddedBinary
    hexstring = ""
    for i in range(0, len(paddedBinary), 4):
        nibble = paddedBinary[i:i+4]
        decimal = int(nibble, 2)
        hexdigit = format(decimal, "X")
        hexstring += hexdigit
    return hexstring

def stringToBinary(input):
    binaryString = ""
    for c in input:
        binaryString += byteToBinary(ord(c))
    return binaryString

def stringToHex(input):
    hexString = ""
    for c in input:
        hexdigit = format(ord(c), "02X")
        hexString += hexdigit
    return hexString

def hexToString(input):
    result = ""
    for i in range(0, len(input), 2):
        hexDigit = input[i:i+2]
        decimal = int(hexDigit, 16)
        result += chr(decimal)
    return result

def binaryToString(input):
    result = ""
    for i in range(0, len(input), 8):
        byteStr = input[i:i+8]
        decimal = int(byteStr, 2)
        result += chr(decimal)
    return result

def decimalToBinary(decimal):
    binary = ""
    index = 3
    while decimal != 0:
        binary += "1" if decimal % 2 != 0 else "0"
        decimal //= 2
        index -= 1
    while index >= 0:
        binary += "0"
        index -= 1
    return binary

def binaryTodecimal(input):
    decimal = 0
    size = len(input)
    counter = 0
    for i in range(size - 1, -1, -1):
        if input[i] == "1":
            decimal += 1 << counter
        counter += 1
    return decimal

def shift_left_once(keychunk):
    shifted = keychunk[1:] + keychunk[0]
    return shifted

def shift_left_twice(keychunk):
    shifted = keychunk[2:] + keychunk[:2]
    return shifted

def Xor(a, b):
    result = ""
    for i in range(len(b)):
        if a[i] != b[i]:
            result += "1"
        else:
            result += "0"
    return result

def generate_keys(key):
    pc1 = [
        57, 49, 41, 33, 25, 17, 9, 1,
        58, 50, 42, 34, 26, 18, 10, 2,
        59, 51, 43, 35, 27, 19, 11, 3,
        60, 52, 44, 36, 63, 55, 47, 39,
        31, 23, 15, 7, 62, 54, 46, 38,
        30, 22, 14, 6, 61, 53, 45, 37,
        29, 21, 13, 5, 28, 20, 12, 4
    ]
    pc2 = [
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32
    ]
    permKey = ""
    for i in range(56):
        permKey += key[pc1[i] - 1]
    left = permKey[:28]
    right = permKey[28:]
    for i in range(16):
        if i == 0 or i == 1 or i == 8 or i == 15:
            left = shift_left_once(left)
            right = shift_left_once(right)
        else:
            left = shift_left_twice(left)
            right = shift_left_twice(right)
        combinedKey = left + right
        roundKey = ""
        for j in range(48):
            roundKey += combinedKey[pc2[j] - 1]
        round_keys[i] = roundKey

def desEnc(block):
    initial_permutation = [
        58,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7
    ]
    expansion_table = [
        32,1,2,3,4,5,4,5,
        6,7,8,9,8,9,10,11,
        12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,
        22,23,24,25,24,25,26,27,
        28,29,28,29,30,31,32,1
    ]
    substition_boxes = [
        [
            [14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7],
            [0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8],
            [4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0],
            [15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13]
        ],
        [
            [15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10],
            [3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5],
            [13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1],
            [13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7]
        ],
        [
            [10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8],
            [13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1],
            [13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7],
            [1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12]
        ],
        [
            [7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15],
            [13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9],
            [10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4],
            [3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14]
        ],
        [
            [2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9],
            [14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6],
            [4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14],
            [11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3]
        ],
        [
            [12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11],
            [10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8],
            [9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6],
            [4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1]
        ],
        [
            [4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1],
            [13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7],
            [1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2],
            [6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12]
        ],
        [
            [13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7],
            [1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2],
            [6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12],
            [13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9]
        ]
    ]
    permutation_tab = [
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    ]
    inverse_permutation = [
        40,8,48,16,56,24,64,32,
        39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,
        37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,
        35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,
        33,1,41,9,49,17,57,25
    ]
    perm = ['0'] * 64
    for i in range(64):
        perm[i] = block[initial_permutation[i]-1]
    left = perm[:32]
    right = perm[32:32+32]
    for i in range(16):
        rightExpanded = ['0'] * 48
        for j in range(48):
            rightExpanded[j] = right[expansion_table[j]-1]
        xored = Xor(round_keys[i], rightExpanded)
        res = ['0'] * 32
        for j in range(8):
            row1 = xored[j*6] + xored[j*6 + 5]
            row = binaryTodecimal(row1)
            col1 = xored[j*6 + 1:j*6 + 5]
            col = binaryTodecimal(col1)
            val = substition_boxes[j][row][col]
            res += decimalToBinary(val)
        perm2 = ['0'] * 32
        for j in range(32):
            perm2[j] = res[permutation_tab[j]-1]
        xored = Xor(perm2, left)
        left = xored
        if i < 15:
            temp = right
            right = xored
            left = temp
    combinedText = left + right
    ciphertext = ['0'] * 64
    for i in range(64):
        ciphertext[i] = combinedText[inverse_permutation[i]-1]
    return ''.join(ciphertext)



def desDecryption(ciphertext):
    i = 15
    j = 0
    while i > j:
        temp = round_keys[i]
        round_keys[i] = round_keys[j]
        round_keys[j] = temp
        i -= 1
        j += 1
    decrypted = desEnc(ciphertext)
    return decrypted

def genKey():
    keySize = 64
    keyBits = random.randint(0, (1 << keySize) - 1)
    key = format(keyBits, "064b")
    return key

def pad(input_str):
    padding_size = 8 - (len(input_str) % 8)
    if padding_size != 8:
        temp = input_str
        for i in range(padding_size):
            temp += str(padding_size)
        return temp
    else:
        return input_str

def des_encrypt_text(pt_string):
    padded_pt = pad(pt_string)
    num_blocks = len(padded_pt) // 8
    blocks = [padded_pt[i*8:i*8+8] for i in range(num_blocks)]
    encrypted = ""
    for block in blocks:
        ct = desEnc(stringToBinary(block))
        encrypted += ct
    return encrypted

def des_decrypt_text(ct_string):
    blocks = [ct_string[i:i+64] for i in range(0, len(ct_string), 64)]
    decrypted = ""
    for block in blocks:
        decrypted += desDecryption(block)
    return decrypted

if __name__ == '__main__':
    
    print ("======================= 3DES (PYTHON) ==========================")
    my_key = "101010101011101100001001000110000010011100110110110011001101110110101010101110110000100100011000001001110011011011001100110111011010101010111011000010010001100000100111001101101100110011011101"
    ptString = "I got 1 in ASEL " 
    print("Plaintext: ", stringToHex(ptString))
    if len(my_key) == 192 and ptString:
        key1, key2, key3 = my_key[0:64],my_key[64:128], my_key[128:192] 
        generate_keys(key1)
        encrypted_text = des_encrypt_text(ptString)
        generate_keys(key2)
        encrypted_text = des_decrypt_text(encrypted_text)
        generate_keys(key3)
        encrypted_text = des_encrypt_text(binaryToString(encrypted_text))
        print("Encrypted Text: ", binaryToHex(encrypted_text))

        decrypted_text = des_decrypt_text(encrypted_text)
        generate_keys(key2)
        decrypted_text = des_encrypt_text(binaryToString(decrypted_text))
        generate_keys(key1)
        decrypted_text = des_decrypt_text(decrypted_text)
        print("Decrypted text: ",binaryToHex(decrypted_text))

