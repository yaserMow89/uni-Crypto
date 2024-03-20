extern crate openssl;
extern crate hex;

use openssl::symm::{encrypt, decrypt, Cipher};

// Function to pad the input to a multiple of block size
fn pkcs7_pad(input: &[u8], block_size: usize) -> Vec<u8> {
    let padding_length = block_size - input.len() % block_size;
    let mut padded = input.to_vec();
    padded.extend(std::iter::repeat(padding_length as u8).take(padding_length));
    padded
}

// Function to remove PKCS7 padding
fn pkcs7_unpad(input: &[u8]) -> Result<Vec<u8>, openssl::error::ErrorStack> {
    let padding_length = input[input.len() - 1] as usize;
    if padding_length >= input.len() {
        return Err(openssl::error::ErrorStack::get());
    }
    let expected_padding = &input[input.len() - padding_length..];
    if !expected_padding.iter().all(|&x| x == padding_length as u8) {
        return Err(openssl::error::ErrorStack::get());
    }
    Ok(input[..input.len() - padding_length].to_vec())
}

fn main() {
    // Define plaintext, key, and IV
    let plaintext = "Hello World12345";
    let key = "123456789abcdefg";
    let iv = "0123456789abcdef";

    // Convert plaintext, key, and IV to bytes
    let plaintext_bytes = plaintext.as_bytes();
    let key_bytes = key.as_bytes();
    let iv_bytes = iv.as_bytes();

    // Define AES CBC cipher
    let cipher = Cipher::aes_128_cbc();

    // Encrypt the plaintext
    let ciphertext = encrypt(
        cipher,
        key_bytes,
        Some(iv_bytes),
        &pkcs7_pad(plaintext_bytes, 16), // Ensure plaintext is padded to a multiple of block size
    ).unwrap();

    // Print the resulting ciphertext
    println!("Ciphertext: {}", hex::encode(&ciphertext));

    // Decrypt the ciphertext
    let decrypted_plaintext = decrypt(
        cipher,
        key_bytes,
        Some(iv_bytes),
        &ciphertext,
    ).unwrap();

    // Remove PKCS7 padding from the decrypted plaintext
    let unpadded_plaintext = pkcs7_unpad(&decrypted_plaintext).unwrap();

    // Convert decrypted plaintext to string
    let decrypted_plaintext_str = String::from_utf8(unpadded_plaintext).unwrap();

    // Print plaintext and decrypted plaintext
    println!("Plaintext: {}", plaintext);
    println!("Decrypted Plaintext: {}", decrypted_plaintext_str);
}
