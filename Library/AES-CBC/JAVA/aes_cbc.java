import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;

public class aes_cbc {
    public static void main(String[] args) throws Exception {
        String plaintext = "Hello World12345";
        String key = "123456789abcdefg";
        String iv = "0123456789abcdef";

        byte[] ciphertext = aesCbcEncrypt(plaintext, key, iv);
        String ciphertextHex = bytesToHex(ciphertext);

        String decryptedPlaintext = aesCbcDecrypt(ciphertext, key, iv);

        System.out.println("Plaintext: " + plaintext);
        System.out.println("Ciphertext (Hex): " + ciphertextHex);
        System.out.println("Decrypted Plaintext: " + decryptedPlaintext);
    }

    public static byte[] aesCbcEncrypt(String plaintext, String key, String iv) throws Exception {
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        SecretKeySpec secretKeySpec = new SecretKeySpec(key.getBytes(), "AES");
        IvParameterSpec ivParameterSpec = new IvParameterSpec(iv.getBytes());
        cipher.init(Cipher.ENCRYPT_MODE, secretKeySpec, ivParameterSpec);
        return cipher.doFinal(plaintext.getBytes());
    }

    public static String aesCbcDecrypt(byte[] ciphertext, String key, String iv) throws Exception {
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        SecretKeySpec secretKeySpec = new SecretKeySpec(key.getBytes(), "AES");
        IvParameterSpec ivParameterSpec = new IvParameterSpec(iv.getBytes());
        cipher.init(Cipher.DECRYPT_MODE, secretKeySpec, ivParameterSpec);
        byte[] decryptedBytes = cipher.doFinal(ciphertext);
        return new String(decryptedBytes);
    }

    public static String bytesToHex(byte[] bytes) {
        StringBuilder result = new StringBuilder();
        for (byte b : bytes) {
            result.append(String.format("%02X", b));
        }
        return result.toString();
    }
}
