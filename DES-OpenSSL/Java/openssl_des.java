import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;
import java.nio.charset.StandardCharsets;
import java.util.Base64;

public class Main {

    public static void main(String[] args) {
        // Replace these key bytes with your actual Triple DES key
        byte[] keyBytes = {(byte) 0x01, (byte) 0x23, (byte) 0x45, (byte) 0x67, (byte) 0x89, (byte) 0xAB, (byte) 0xCD, (byte) 0xEF,
                            (byte) 0xFE, (byte) 0xDC, (byte) 0xBA, (byte) 0x98, (byte) 0x76, (byte) 0x54, (byte) 0x32, (byte) 0x10};

        String plaintext = "The quick brown fox jumps over the lazy dog";

        // Use only the first 8 bytes of the key for single DES
        byte[] singleDesKeyBytes = new byte[8];
        System.arraycopy(keyBytes, 0, singleDesKeyBytes, 0, 8);

        try {
            // Encrypt the message using single DES
            byte[] encryptedData = singleDesEncrypt(plaintext, singleDesKeyBytes);
            System.out.println("Ciphertext: " + Base64.getEncoder().encodeToString(encryptedData));

            // Decrypt the message using single DES
            String decryptedData = singleDesDecrypt(encryptedData, singleDesKeyBytes);
            System.out.println("Decrypted: " + decryptedData);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] singleDesEncrypt(String input, byte[] keyBytes) throws Exception {
        Cipher cipher = Cipher.getInstance("DES/ECB/PKCS5Padding");
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DES");
        SecretKey key = keyFactory.generateSecret(new DESKeySpec(keyBytes));
        cipher.init(Cipher.ENCRYPT_MODE, key);
        return cipher.doFinal(input.getBytes(StandardCharsets.UTF_8));
    }

    private static String singleDesDecrypt(byte[] input, byte[] keyBytes) throws Exception {
        Cipher cipher = Cipher.getInstance("DES/ECB/PKCS5Padding");
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DES");
        SecretKey key = keyFactory.generateSecret(new DESKeySpec(keyBytes));
        cipher.init(Cipher.DECRYPT_MODE, key);
        byte[] decryptedBytes = cipher.doFinal(input);
        return new String(decryptedBytes, StandardCharsets.UTF_8);
    }
}
