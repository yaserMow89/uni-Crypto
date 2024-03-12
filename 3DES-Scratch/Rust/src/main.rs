use std::fmt::Write;
use rand::Rng;

fn byte_to_binary(byte: u8) -> String {
    format!("{:08b}", byte)
}

fn binary_to_hex(binary_input: &str) -> String {
    let mut padded_binary = String::from(binary_input);
    while padded_binary.len() % 4 != 0 {
        padded_binary.insert(0, '0');
    }
    let mut hex_string = String::new();
    for i in (0..padded_binary.len()).step_by(4) {
        let nibble = &padded_binary[i..i+4];
        let decimal = u8::from_str_radix(nibble, 2).unwrap();
        write!(hex_string, "{:X}", decimal).unwrap();
    }
    hex_string
}

fn string_to_binary(input: &str) -> String {
    let mut binary_string = String::new();
    for c in input.chars() {
        binary_string.push_str(&byte_to_binary(c as u8));
    }
    binary_string
}

fn string_to_hex(input: &str) -> String {
    let mut hex_string = String::new();
    for c in input.chars() {
        write!(hex_string, "{:02X}", c as u8).unwrap();
    }
    hex_string
}

fn hex_to_string(input: &str) -> String {
    let mut result = String::new();
    for i in (0..input.len()).step_by(2) {
        let hex_digit = &input[i..i+2];
        let decimal = u8::from_str_radix(hex_digit, 16).unwrap();
        result.push(decimal as char);
    }
    result
}

fn binary_to_string(input: &str) -> String {
    let mut result = String::new();
    for i in (0..input.len()).step_by(8) {
        let byte_str = &input[i..i+8];
        let decimal = u8::from_str_radix(byte_str, 2).unwrap();
        result.push(decimal as char);
    }
    result
}

fn decimal_to_binary(decimal: u8) -> String {
    let mut binary = String::new();
    let mut index = 3;
    let mut temp = decimal;
    while temp != 0 {
        binary.push(if temp % 2 == 0 { '0' } else { '1' });
        temp /= 2;
        index -= 1;
    }
    while index >= 0 {
        binary.push('0');
        index -= 1;
    }
    binary
}

fn binary_to_decimal(input: &str) -> u8 {
    let mut decimal = 0;
    let size = input.len();
    let mut counter = 0;
    for i in (0..size).rev() {
        if &input[i..i+1] == "1" {
            decimal += 1 << counter;
        }
        counter += 1;
    }
    decimal
}

fn shift_left_once(key_chunk: &str) -> String {
    let mut shifted = String::from(&key_chunk[1..]);
    shifted.push(key_chunk.chars().next().unwrap());
    shifted
}

fn shift_left_twice(key_chunk: &str) -> String {
    let mut shifted = String::from(&key_chunk[2..]);
    shifted.push_str(&key_chunk[..2]);
    shifted
}

fn xor(a: &str, b: &str) -> String {
    let mut result = String::new();
    for (ca, cb) in a.chars().zip(b.chars()) {
        if ca != cb {
            result.push('1');
        } else {
            result.push('0');
        }
    }
    result
}

fn generate_keys(key: &str) -> Vec<String> {
    let pc1 = [
        57, 49, 41, 33, 25, 17, 9, 1,
        58, 50, 42, 34, 26, 18, 10, 2,
        59, 51, 43, 35, 27, 19, 11, 3,
        60, 52, 44, 36, 63, 55, 47, 39,
        31, 23, 15, 7, 62, 54, 46, 38,
        30, 22, 14, 6, 61, 53, 45, 37,
        29, 21, 13, 5, 28, 20, 12, 4
    ];
    let pc2 = [
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32
    ];
    let mut perm_key = String::with_capacity(56);
    for &index in &pc1 {
        perm_key.push(key.chars().nth(index - 1).unwrap());
    }
    let left = &perm_key[..28];
    let right = &perm_key[28..];
    let mut round_keys = Vec::with_capacity(16);
    for i in 0..16 {
        let combined_key = if i == 0 || i == 1 || i == 8 || i == 15 {
            shift_left_once(left) + &shift_left_once(right)
        } else {
            shift_left_twice(left) + &shift_left_twice(right)
        };
        let mut round_key = String::with_capacity(48);
        for &index in &pc2 {
            round_key.push(combined_key.chars().nth(index - 1).unwrap());
        }
        round_keys.push(round_key);
    }
    round_keys
}

fn des_enc(block: &str, round_keys: &[String]) -> String {
    let initial_permutation = [
        58,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7
    ];
    let expansion_table = [
        32,1,2,3,4,5,4,5,
        6,7,8,9,8,9,10,11,
        12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,
        22,23,24,25,24,25,26,27,
        28,29,28,29,30,31,32,1
    ];
    let substitution_boxes = [
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
    ];
    let permutation_tab = [
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    ];
    let inverse_permutation = [
        40,8,48,16,56,24,64,32,
        39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,
        37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,
        35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,
        33,1,41,9,49,17,57,25
    ];
    let perm = initial_permutation.iter().map(|&index| block.chars().nth(index - 1).unwrap()).collect::<String>();
    let left = &perm[..32];
    let right = &perm[32..];
    let mut left_clone = String::new();
    let mut right_clone = String::new();
    for i in 0..16 {
        let right_expanded = expansion_table.iter().map(|&index| right.chars().nth(index - 1).unwrap()).collect::<String>();
        let xored = xor(&round_keys[i], &right_expanded);
        let mut res = String::with_capacity(32);
        for j in 0..8 {
            let row1 = &xored[j*6..j*6+1];
            let row2 = &xored[j*6+5..j*6+6];
            let row = binary_to_decimal(&(row1.to_owned() + row2));
            let col = binary_to_decimal(&xored[j*6+1..j*6+5]);
            let val = substitution_boxes[j][row as usize][col as usize];
            res.push_str(&decimal_to_binary(val));
        }
        let mut perm2 = String::with_capacity(32);
        for &index in &permutation_tab {
            perm2.push(res.chars().nth(index - 1).unwrap());
        }
        let xored = xor(&perm2, left);
        left_clone = xored.clone().to_string();
        right_clone = right.clone().to_string();
        if i < 15
        {
            let temp = right_clone;
            right_clone = xored.clone().to_string();
            left_clone = temp.clone().to_string();
        }
        
    }
    let combined_text = left_clone.to_owned() + &right_clone;
    let mut ciphertext = String::with_capacity(64);
    for &index in &inverse_permutation {
        ciphertext.push(combined_text.chars().nth(index - 1).unwrap());
    }
    ciphertext
}

fn des_decryption(ciphertext: &str, round_keys: &[String]) -> String {
    let mut round_keys = round_keys.to_owned();
    round_keys.reverse();
    des_enc(ciphertext, &round_keys)
}


fn pad(input_str: &str) -> String {
    let padding_size = 8 - (input_str.len() % 8);
    if padding_size != 8 {
        let mut temp = String::from(input_str);
        for _ in 0..padding_size {
            temp.push((padding_size + '0' as usize) as u8 as char);
        }
        temp
    } else {
        String::from(input_str)
    }
}

fn des_encrypt_text(pt_string: &str, round_keys: &[String]) -> String {
    let padded_pt = pad(pt_string);
    let num_blocks = padded_pt.len() / 8;
    let mut blocks = String::new();
    for i in 0..num_blocks {
        blocks.push_str(&padded_pt[i * 8..(i + 1) * 8]);
    }
    let mut encrypted = String::new();
    for i in 0..num_blocks {
        let ct = des_enc(&string_to_binary(&blocks[i * 8..(i + 1) * 8]), round_keys);
        encrypted.push_str(&ct);
    }
    encrypted
}


fn des_decrypt_text(ct_string: &str, round_keys: &[String]) -> String {
    let mut blocks: Vec<String> = Vec::new();
    for i in (0..ct_string.len()).step_by(64) {
        blocks.push(ct_string[i..i + 64.min(ct_string.len() - i)].to_string());
    }
    let mut decrypted = String::new();
    for block in blocks.iter() {
        decrypted += &des_decryption(block, round_keys);
    }
    decrypted
}


fn main() {
    let key = "101010101011101100001001000110000010011100110110110011001101110110101010101110110000100100011000001001110011011011001100110111011010101010111011000010010001100000100111001101101100110011011101";
    let plaintext = "The quick brown fox jumps over the lazy dog";

    if key.len() == 192 && !plaintext.is_empty() {
        let key1 = &key[0..64];
        let key2 = &key[64..128];
        let key3 = &key[128..192];

        println!("Plaintext Hex: {}", &string_to_hex(plaintext));
        let round_keys1 = generate_keys(key1);
        let mut encrypted = des_encrypt_text(plaintext, &round_keys1);

        let round_keys2 = generate_keys(key2);
        println!("Encrypted Hex: {}", binary_to_hex(&encrypted));
        encrypted = des_decrypt_text(&encrypted, &round_keys2);
        
        let round_keys3 = generate_keys(key3);
        encrypted = des_encrypt_text(&binary_to_string(&encrypted), &round_keys3);

        let round_keys2 = generate_keys(key2);
        let mut decrypted = des_decrypt_text(&encrypted, &round_keys2);
        encrypted = des_encrypt_text(&binary_to_string(&decrypted), &round_keys2);

        let round_keys1 = generate_keys(key1);
        decrypted = des_decrypt_text(&encrypted, &round_keys1);

        println!("Decrypted Hex: {}", &binary_to_hex(&decrypted));
    }
}


