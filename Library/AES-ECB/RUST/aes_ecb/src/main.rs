extern crate openssl;
extern crate hex;

use openssl::symm::{encrypt, decrypt, Cipher};

fn main() {
    // Define plaintext and key
    let plaintext = "Hello World12345";
    let key = "123456789abcdefg";

    // Convert plaintext and key to bytes
    let plaintext_bytes = plaintext.as_bytes();
    let key_bytes = key.as_bytes();

    // Create AES ECB encryptor
    let cipher = Cipher::aes_128_ecb();

    // Encrypt the plaintext
    let ciphertext = encrypt(
        cipher,
        key_bytes,
        None,
        plaintext_bytes,
    ).unwrap();

    // Decrypt the ciphertext
    let decrypted_plaintext = decrypt(
        cipher,
        key_bytes,
        None,
        &ciphertext,
    ).unwrap();

    // Convert decrypted plaintext to string
    let decrypted_plaintext_str = String::from_utf8(decrypted_plaintext).unwrap();

    // Print plaintext, ciphertext, and decrypted plaintext
    println!("Plaintext: {}", plaintext);
    println!("Ciphertext: {}", hex::encode(&ciphertext));
    println!("Decrypted Plaintext: {}", decrypted_plaintext_str);
}
