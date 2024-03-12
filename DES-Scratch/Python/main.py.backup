import random

# Global Vars
round_keys = [None] * 16  # Global variable to store the round keys
pt = ''


def string_to_binary(input_str):
    binary_string = ""
    for char in input_str:
        binary_string += format(ord(char), '08b')
    return binary_string

def binary_to_hex(binary_input):
    # Make sure the binary string's length is a multiple of 4
    padded_binary = binary_input
    while len(padded_binary) % 4 != 0:
        padded_binary = "0" + padded_binary

    hex_string = ""
    for i in range(0, len(padded_binary), 4):
        nibble = padded_binary[i:i+4]
        decimal_value = int(nibble, 2)
        hex_string += format(decimal_value, 'x')

    return hex_string

def gen_key():
    key_size = 64
    key_bits = [random.choice([0, 1]) for _ in range(key_size)]
    
    # Convert the list of bits to a string
    key_string = ''.join(map(str, key_bits))
    
    return key_string

def generate_keys(key):
    # The PC1 table
    pc1 = [
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
    ]
    # The PC2 table
    pc2 = [
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    ]

    # 1. Compressing the key using the PC1 table
    perm_key = ''.join(key[i - 1] for i in pc1)

    # 2. Dividing the result into two equal halves
    left = perm_key[:28]
    right = perm_key[28:]

    # Generating 16 keys
    for i in range(16):
        # 3.1. For rounds 1, 2, 9, 16 the key_chunks
        # are shifted by one.
        if i in {0, 1, 8, 15}:
            left = shift_left_once(left)
            right = shift_left_once(right)
        # 3.2. For other rounds, the key_chunks
        # are shifted by two
        else:
            left = shift_left_twice(left)
            right = shift_left_twice(right)

        # 4. The chunks are combined
        combined_key = left + right
        round_key = ""
        
        # 5. Finally, the PC2 table is used to transpose
        # the key bits
        round_key = ''.join(combined_key[i - 1] for i in pc2)
        round_keys[i] = round_key

# Helper function for circular left shift by 1
def shift_left_once(key_chunk):
    return key_chunk[1:] + key_chunk[0]

# Helper function for circular left shift by 2
def shift_left_twice(key_chunk):
    return key_chunk[2:] + key_chunk[:2]

# The follwing function is only for test 
def print_keys():
    for i, key in enumerate(round_keys):
        print(f"Key {i + 1}: {key}")

def xor_strings(a, b):
    result = ""
    for char_a, char_b in zip(a, b):
        result += "1" if char_a != char_b else "0"
    return result

def convert_decimal_to_binary(decimal):
    binary = ""
    while decimal != 0:
        binary = ("0" if decimal % 2 == 0 else "1") + binary
        decimal //= 2
    while len(binary) < 4:
        binary = "0" + binary
    return binary

def convert_binary_to_decimal(binary):
    decimal = 0
    counter = 0
    size = len(binary)
    
    for i in range(size - 1, -1, -1):
        if binary[i] == '1':
            decimal += 2 ** counter
        counter += 1
    
    return decimal

def des_encryption(pt, round_keys):
    # The initial permutation table
    initial_permutation = [
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    ]

    # The expansion table
    expansion_table = [
        32, 1, 2, 3, 4, 5, 4, 5,
        6, 7, 8, 9, 8, 9, 10, 11,
        12, 13, 12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21, 20, 21,
        22, 23, 24, 25, 24, 25, 26, 27,
        28, 29, 28, 29, 30, 31, 32, 1
    ]

    # Substitution boxes
    substitution_boxes = [
        [
            [14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7],
            [0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8],
            [4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0],
            [15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13]
        ],
        # ... (similar lists for other substitution boxes)
    ]

    # The permutation table
    permutation_tab = [
        16, 7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9,
        19, 13, 30, 6, 22, 11, 4, 25
    ]

    # The inverse permutation table
    inverse_permutation = [
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
    ]

    # 1. Applying the initial permutation
    perm = ""
    for i in range(64):
        perm += pt[initial_permutation[i] - 1]

    # 2. Dividing the result into two equal halves
    left = perm[:32]
    right = perm[32:]

    # The plain text is encrypted 16 times
    for i in range(16):
        right_expanded = ""

        # 3.1. The right half of the plain text is expanded
        for j in range(48):
            right_expanded += right[expansion_table[j] - 1]

        # 3.3. The result is xored with a key
        xored = xor_strings(round_keys[i], right_expanded)

        res = ""

        # 3.4. The result is divided into 8 equal parts and passed
        # through 8 substitution boxes. After passing through a
        # substitution box, each box is reduced from 6 to 4 bits.
        for j in range(8):
            # Finding row and column indices to look up the
            # substitution box
            row1 = xored[j * 6] + xored[j * 6 + 5]
            row = convert_binary_to_decimal(row1)

            col1 = xored[j * 6 + 1:j * 6 + 5]
            col = convert_binary_to_decimal(col1)

            val = substitution_boxes[j][row][col]
            res += convert_decimal_to_binary(val)

        # 3.5. Another permutation is applied
        perm2 = ""
        for j in range(32):
            perm2 += res[permutation_tab[j] - 1]

        # 3.6. The result is xored with the left half
        xored = xor_strings(perm2, left)

        # 3.7. The left and the right parts of the plain text are swapped
        left = xored
        if i < 15:
            temp = right
            right = xored
            left = temp

    # 4. The halves of the plain text are applied
    combined_text = left + right
    ciphertext = ""

    # The inverse of the initial permutation is applied
    for i in range(64):
        ciphertext += combined_text[inverse_permutation[i] - 1]

    # Finally, we get the cipher text
    return ciphertext



def main(): 
  my_key = gen_key()
  # print(my_key)

  generate_keys(my_key)
#   print_keys()

  ptstring = "YASERMOW"

  pt= string_to_binary(ptstring)
  apt = pt
  
  ct = des_encryption(pt, )


if __name__=="__main__": 
  main() 

