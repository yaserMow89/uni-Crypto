use openssl::symm::{Cipher, Crypter, Mode};

fn main() {
    let plaintexts = b"The quick brown fox jumps over the lazy doggg";
    let key = b"\x00\x01\x02\x03\x04\x05\x06\x07\x00\x01\x02\x03\x04\x05\x06\x07\x00\x01\x02\x03\x04\x05\x06\x07";
    let data_len = plaintexts.len();

    print!("Plaintext Hex: ");
    for &byte in &plaintexts[0..plaintexts.len()] {
        print!("{:02X}", byte);
    }
    println!();

    let mut encrypter = Crypter::new(Cipher::des_ede3(), Mode::Encrypt, key, None).unwrap();

    let block_size = Cipher::des_ede3().block_size();
    let mut ciphertext = vec![0; data_len + block_size];

    let mut count = encrypter.update(plaintexts, &mut ciphertext).unwrap();
    
    count += encrypter.finalize(&mut ciphertext[count..]).unwrap();
    ciphertext.truncate(count);

    print!("Encrypted Hex: ");
    for &byte in &ciphertext[0..ciphertext.len()] {
        print!("{:02X}", byte);
    }
    println!();

    let data_len = ciphertext.len();
    let ciphertexts = [&ciphertext[..9], &ciphertext[9..]];

    let mut decrypter = Crypter::new(Cipher::des_ede3(), Mode::Decrypt, key, None).unwrap();
    let mut plaintext = vec![0; data_len + block_size];

    let mut count = decrypter.update(ciphertexts[0], &mut plaintext).unwrap();
    count += decrypter
        .update(ciphertexts[1], &mut plaintext[count..])
        .unwrap();
    count += decrypter.finalize(&mut plaintext[count..]).unwrap();
    plaintext.truncate(count);

    assert_eq!(&plaintexts[..], &plaintext[..]);
    print!("Decrypted Hex: ");
    for &byte in &plaintext[0..plaintext.len()] {
        print!("{:02X}", byte);
    }
    println!();
}
