from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
import binascii

def pad_data(data):
    padder = padding.PKCS7(algorithms.TripleDES.block_size).padder()
    padded_data = padder.update(data) + padder.finalize()
    return padded_data

def unpad_data(data):
    unpadder = padding.PKCS7(algorithms.TripleDES.block_size).unpadder()
    unpadded_data = unpadder.update(data) + unpadder.finalize()
    return unpadded_data

def single_des_encrypt(input_data, key):
    cipher = Cipher(algorithms.TripleDES(key), mode=modes.ECB(), backend=default_backend())
    encryptor = cipher.encryptor()
    encrypted_data = encryptor.update(pad_data(input_data)) + encryptor.finalize()
    return encrypted_data

def single_des_decrypt(input_data, key):
    cipher = Cipher(algorithms.TripleDES(key), mode=modes.ECB(), backend=default_backend())
    decryptor = cipher.decryptor()
    decrypted_data = decryptor.update(input_data) + decryptor.finalize()
    return unpad_data(decrypted_data)

def main():
    print(" ================================== DES (PYTHON) =========================================")
    # Replace these key bytes with your actual Triple DES key
    key_bytes = b'\x01\x23\x45\x67\x89\xAB\xCD\xEF\xFE\xDC\xBA\x98\x76\x54\x32\x10'
    
    plaintext = b'I got 1 in ASEL '
    print("Plaintext is: ", plaintext.decode('utf-8'))
    # Use only the first 8 bytes of the key for single DES
    single_des_key = key_bytes[:8]

    # Encrypt the message using single DES
    encrypted_data = single_des_encrypt(plaintext, single_des_key)
    print("Ciphertext:", binascii.hexlify(encrypted_data).decode('utf-8'))

    # Decrypt the message using single DES
    decrypted_data = single_des_decrypt(encrypted_data, single_des_key)
    print("Decrypted:", decrypted_data.decode('utf-8'))

if __name__ == "__main__":
    main()
