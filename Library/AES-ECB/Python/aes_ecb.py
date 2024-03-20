from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import binascii

def aes_ecb_encrypt(plaintext, key):
    cipher = AES.new(key, AES.MODE_ECB)
    padded_plaintext = pad(plaintext.encode(), AES.block_size)
    ciphertext = cipher.encrypt(padded_plaintext)
    return ciphertext

def aes_ecb_decrypt(ciphertext, key):
    cipher = AES.new(key, AES.MODE_ECB)
    decrypted_plaintext = cipher.decrypt(ciphertext)
    unpadded_plaintext = unpad(decrypted_plaintext, AES.block_size)
    return unpadded_plaintext.decode()

plaintext = "Hello World12345"
key = b'123456789abcdefg'  # 16 bytes key for AES-128

ciphertext = aes_ecb_encrypt(plaintext, key)
decrypted_text = aes_ecb_decrypt(ciphertext, key)

print("Plaintext:", plaintext)
print("Ciphertext (hex):", binascii.hexlify(ciphertext).decode())
print("Decrypted Ciphertext:", decrypted_text)
