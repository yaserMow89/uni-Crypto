from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
import binascii

def aes_cbc_encrypt(plaintext, key, iv):
    cipher = AES.new(key, AES.MODE_CBC, iv)
    padded_plaintext = pad(plaintext.encode(), AES.block_size)
    ciphertext = cipher.encrypt(padded_plaintext)
    return ciphertext

def aes_cbc_decrypt(ciphertext, key, iv):
    cipher = AES.new(key, AES.MODE_CBC, iv)
    decrypted_plaintext = cipher.decrypt(ciphertext)
    unpadded_plaintext = unpad(decrypted_plaintext, AES.block_size)
    return unpadded_plaintext.decode()

plaintext = "Hello World12345"
key = b'123456789abcdefg'  # 16 bytes key for AES-128
iv = b'0123456789abcdef'   # 16 bytes IV

ciphertext = aes_cbc_encrypt(plaintext, key, iv)
decrypted_text = aes_cbc_decrypt(ciphertext, key, iv)

print("Plaintext:", plaintext)
print("Ciphertext (hex):", binascii.hexlify(ciphertext).decode())
print("Decrypted Ciphertext:", decrypted_text)
