public class SimpleRSA {
    public static void main(String[] args) {
        // Example small prime numbers (Insecure! For demonstration only)
        int p = 61;
        int q = 53;
        int n = p * q;
        int phi = (p - 1) * (q - 1);

        // Choose e, d such that e*d == 1 (mod phi)
        int e = 17; // e is chosen such that 1 < e < phi and gcd(e, phi) = 1
        int d = 2753; // d is calculated from e such that d*e == 1 (mod phi)

        // Example message
        String message = "Hello World!"; // Original message as a string
        System.out.println("Original message: " + message);

        StringBuilder encryptedMessage = new StringBuilder();
        StringBuilder decryptedMessage = new StringBuilder();

        // Encrypt each character
        for (char character : message.toCharArray()) {
            int m = character; // Convert char to int
            int c = modPow(m, e, n); // Encrypt
            encryptedMessage.append(Integer.toHexString(c)).append(" "); // Append encrypted char as hex (for demonstration)
        }
        System.out.println("Encrypted message: " + encryptedMessage.toString().trim());

        // Decrypt each character
        String[] encryptedChars = encryptedMessage.toString().trim().split(" ");
        for (String encryptedChar : encryptedChars) {
            int c = Integer.parseInt(encryptedChar, 16); // Convert hex back to int
            int m = modPow(c, d, n); // Decrypt
            decryptedMessage.append((char) m); // Append decrypted char
        }
        System.out.println("Decrypted message: " + decryptedMessage);
    }

    // Method to perform modular exponentiation
    // It returns (base^exponent) mod modulus
    public static int modPow(int base, int exponent, int modulus) {
        int result = 1;
        base = base % modulus;
        while (exponent > 0) {
            if (exponent % 2 == 1)
                result = (result * base) % modulus;
            exponent = exponent >> 1;
            base = (base * base) % modulus;
        }
        return result;
    }
}
