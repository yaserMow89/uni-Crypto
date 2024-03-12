import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESedeKeySpec;
import java.nio.charset.StandardCharsets;
import java.util.Base64;

public class Main {

    public static void main(String[] args) {
        // Replace these key bytes with your actual Triple DES key
        byte[] keyBytes = {
            (byte) 0x01, (byte) 0x23, (byte) 0x45, (byte) 0x67, (byte) 0x89, (byte) 0xAB, (byte) 0xCD, (byte) 0xEF,
            (byte) 0xFE, (byte) 0xDC, (byte) 0xBA, (byte) 0x98, (byte) 0x76, (byte) 0x54, (byte) 0x32, (byte) 0x10,
            (byte) 0x01, (byte) 0x23, (byte) 0x45, (byte) 0x67, (byte) 0x89, (byte) 0xAB, (byte) 0xCD, (byte) 0xEF
        };

        String plaintext = "The quick brown fox jumps over the lazy dog";
        System.out.println("Plaintext (JAVA): " + plaintext);
        try {
            // Encrypt the message using Triple DES
            byte[] encryptedData = tripleDesEncrypt(plaintext, keyBytes);
            System.out.println("Ciphertext (JAVA): " + Base64.getEncoder().encodeToString(encryptedData));

            // Decrypt the message using Triple DES
            String decryptedData = tripleDesDecrypt(encryptedData, keyBytes);
            System.out.println("Decrypted (JAVA): " + decryptedData);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] tripleDesEncrypt(String input, byte[] keyBytes) throws Exception {
        Cipher cipher = Cipher.getInstance("DESede/ECB/PKCS5Padding");
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DESede");
        SecretKey key = keyFactory.generateSecret(new DESedeKeySpec(keyBytes));
        cipher.init(Cipher.ENCRYPT_MODE, key);
        return cipher.doFinal(input.getBytes(StandardCharsets.UTF_8));
    }

    private static String tripleDesDecrypt(byte[] input, byte[] keyBytes) throws Exception {
        Cipher cipher = Cipher.getInstance("DESede/ECB/PKCS5Padding");
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DESede");
        SecretKey key = keyFactory.generateSecret(new DESedeKeySpec(keyBytes));
        cipher.init(Cipher.DECRYPT_MODE, key);
        byte[] decryptedBytes = cipher.doFinal(input);
        return new String(decryptedBytes, StandardCharsets.UTF_8);
    }
}
