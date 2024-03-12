import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Main {
    private static List<String> round_keys = new ArrayList<>();

    public static void main(String[] args) {
        String my_key = "1010101010111011000010010001100000100111001101101100110011011101";
        generate_keys(my_key);
        String ptString = "The quick brown fox jumps over the lazy dog";
        System.out.println("Plaintext hex (JAVA: " + stringToHex(ptString));
        String encrypted_text = des_encrypt_text(ptString);
        String decrypted_text = des_decrypt_text(encrypted_text);
        System.out.println("encrypted Hex (JAVA): " + binaryToHex(encrypted_text));
        System.out.println("decrypted Text (JAVA): " + binaryToHex(decrypted_text));
    }

    public static String byteToBinary(char byteValue) {
        return String.format("%8s", Integer.toBinaryString(byteValue & 0xFF)).replace(' ', '0');
    }

    public static String binaryToHex(String binaryInput) {
        StringBuilder paddedBinary = new StringBuilder(binaryInput);
        while (paddedBinary.length() % 4 != 0) {
            paddedBinary.insert(0, '0');
        }
        StringBuilder hexString = new StringBuilder();
        for (int i = 0; i < paddedBinary.length(); i += 4) {
            String nibble = paddedBinary.substring(i, i + 4);
            int decimal = Integer.parseInt(nibble, 2);
            hexString.append(String.format("%X", decimal));
        }
        return hexString.toString();
    }

    public static String stringToBinary(String input) {
        StringBuilder binaryString = new StringBuilder();
        for (char c : input.toCharArray()) {
            binaryString.append(byteToBinary(c));
        }
        return binaryString.toString();
    }

    public static String stringToHex(String input) {
        StringBuilder hexString = new StringBuilder();
        for (char c : input.toCharArray()) {
            hexString.append(String.format("%02X", (int) c));
        }
        return hexString.toString();
    }

    public static String hexToString(String input) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < input.length(); i += 2) {
            String hexDigit = input.substring(i, i + 2);
            int decimal = Integer.parseInt(hexDigit, 16);
            result.append((char) decimal);
        }
        return result.toString();
    }

    public static String binaryToString(String input) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < input.length(); i += 8) {
            String byteStr = input.substring(i, i + 8);
            int decimal = Integer.parseInt(byteStr, 2);
            result.append((char) decimal);
        }
        return result.toString();
    }

    public static String decimalToBinary(int decimal) {
        StringBuilder binary = new StringBuilder();
        int index = 3;
        while (decimal != 0) {
            binary.insert(0, ((decimal % 2 == 0) ? '0' : '1'));
            decimal /= 2;
            index -= 1;
        }
        while (index >= 0) {
            binary.insert(0, '0');
            index -= 1;
        }
        return binary.toString();
    }

    public static int binaryToDecimal(String input) {
        int decimal = 0;
        int size = input.length();
        int counter = 0;
        for (int i = size - 1; i >= 0; i--) {
            if (input.charAt(i) == '1') {
                decimal += 1 << counter;
            }
            counter += 1;
        }
        return decimal;
    }

    public static String shift_left_once(String keyChunk) {
        StringBuilder shifted = new StringBuilder(keyChunk.substring(1));
        shifted.append(keyChunk.charAt(0));
        return shifted.toString();
    }

    public static String shift_left_twice(String keyChunk) {
        StringBuilder shifted = new StringBuilder(keyChunk.substring(2));
        shifted.append(keyChunk, 0, 2);
        return shifted.toString();
    }

    public static String Xor(String a, String b) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < b.length(); i++) {
            if (a.charAt(i) != b.charAt(i)) {
                result.append('1');
            } else {
                result.append('0');
            }
        }
        return result.toString();
    }

    public static void generate_keys(String key) {
        int[] pc1 = {
                57, 49, 41, 33, 25, 17, 9,
                1, 58, 50, 42, 34, 26, 18,
                10, 2, 59, 51, 43, 35, 27,
                19, 11, 3, 60, 52, 44, 36,
                63, 55, 47, 39, 31, 23, 15,
                7, 62, 54, 46, 38, 30, 22,
                14, 6, 61, 53, 45, 37, 29,
                21, 13, 5, 28, 20, 12, 4
        };
        int[] pc2 = {
                14, 17, 11, 24, 1, 5,
                3, 28, 15, 6, 21, 10,
                23, 19, 12, 4, 26, 8,
                16, 7, 27, 20, 13, 2,
                41, 52, 31, 37, 47, 55,
                30, 40, 51, 45, 33, 48,
                44, 49, 39, 56, 34, 53,
                46, 42, 50, 36, 29, 32
        };
        StringBuilder permKey = new StringBuilder();
        for (int i = 0; i < 56; i++) {
            permKey.append(key.charAt(pc1[i] - 1));
        }
        String left = permKey.substring(0, 28);
        String right = permKey.substring(28, 56);
        for (int i = 0; i < 16; i++) {
            if (i == 0 || i == 1 || i == 8 || i == 15) {
                left = shift_left_once(left);
                right = shift_left_once(right);
            } else {
                left = shift_left_twice(left);
                right = shift_left_twice(right);
            }
            String combinedKey = left + right;
            StringBuilder roundKey = new StringBuilder();
            for (int j = 0; j < 48; j++) {
                roundKey.append(combinedKey.charAt(pc2[j] - 1));
            }
            round_keys.add(roundKey.toString());
        }
    }

    public static String desEnc(String block) {
        int[] initial_permutation = {
                58, 50, 42, 34, 26, 18, 10, 2,
                60, 52, 44, 36, 28, 20, 12, 4,
                62, 54, 46, 38, 30, 22, 14, 6,
                64, 56, 48, 40, 32, 24, 16, 8,
                57, 49, 41, 33, 25, 17, 9, 1,
                59, 51, 43, 35, 27, 19, 11, 3,
                61, 53, 45, 37, 29, 21, 13, 5,
                63, 55, 47, 39, 31, 23, 15, 7
        };
        int[] expansion_table = {
                32, 1, 2, 3, 4, 5, 4, 5,
                6, 7, 8, 9, 8, 9, 10, 11,
                12, 13, 12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21, 20, 21,
                22, 23, 24, 25, 24, 25, 26, 27,
                28, 29, 28, 29, 30, 31, 32, 1
        };
        int[][][] substition_boxes = {
                {
                        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
                },
                {
                        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7}
                },
                {
                        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
                },
                {
                        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
                },
                {
                        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
                },
                {
                        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1}
                },
                {
                        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
                },
                {
                        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
                        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
                }
        };
        int[] permutation_tab = {
                16, 7, 20, 21, 29, 12, 28, 17,
                1, 15, 23, 26, 5, 18, 31, 10,
                2, 8, 24, 14, 32, 27, 3, 9,
                19, 13, 30, 6, 22, 11, 4, 25
        };
        int[] inverse_permutation = {
                40, 8, 48, 16, 56, 24, 64, 32,
                39, 7, 47, 15, 55, 23, 63, 31,
                38, 6, 46, 14, 54, 22, 62, 30,
                37, 5, 45, 13, 53, 21, 61, 29,
                36, 4, 44, 12, 52, 20, 60, 28,
                35, 3, 43, 11, 51, 19, 59, 27,
                34, 2, 42, 10, 50, 18, 58, 26,
                33, 1, 41, 9, 49, 17, 57, 25
        };
       StringBuilder perm = new StringBuilder(String.join("", Collections.nCopies(64, "0")));
        for(int i = 0; i < 64; i++) {
            perm.setCharAt(i, block.charAt(initial_permutation[i]-1));
        }
        String left = perm.substring(0, 32);
        String right = perm.substring(32, 32 + 32);
        for(int i = 0; i < 16; i++) {
            StringBuilder rightExpanded = new StringBuilder(String.join("", Collections.nCopies(48, "0")));
            for(int j = 0; j < 48; j++) {
                rightExpanded.setCharAt(j, right.charAt(expansion_table[j]-1));
            }
            String xored = Xor(round_keys.get(i), rightExpanded.toString());
            StringBuilder res = new StringBuilder(String.join("", Collections.nCopies(32, "0")));
            for(int j = 0; j < 8; j++) {
                StringBuilder row1 = new StringBuilder();
                row1.append(xored.charAt(j*6));
                row1.append(xored.charAt(j*6 + 5));
                int row = binaryToDecimal(row1.toString());
                String col1 = xored.substring(j*6 + 1, j*6 + 5);
                int col = binaryToDecimal(col1);
                int val = substition_boxes[j][row][col];
                res.append(decimalToBinary(val));
            }
            StringBuilder perm2 = new StringBuilder(String.join("", Collections.nCopies(32, "0")));
            for(int j = 0; j < 32; j++) {
                perm2.setCharAt(j, res.charAt(permutation_tab[j]-1));
            }
            String xored2 = Xor(perm2.toString(), left);
            left = right;
            right = xored2;
        }
        StringBuilder combine = new StringBuilder();
        combine.append(right);
        combine.append(left);
        StringBuilder result = new StringBuilder(String.join("", Collections.nCopies(64, "0")));
        for(int i = 0; i < 64; i++) {
            result.setCharAt(i, combine.charAt(inverse_permutation[i]-1));
        }
        return result.toString();
    }
    public static String pad(String input_str) {
        int padding_size = 8 - (input_str.length() % 8);
        if (padding_size != 8) {
            StringBuilder temp = new StringBuilder(input_str);
            for (int i = 0; i < padding_size; i++) {
                temp.append((char)(padding_size + '0'));
            }
            return temp.toString();
        } else {
            return input_str;
        }
    }
    public static String des_encrypt_text(String ptString) {
        StringBuilder cipherText = new StringBuilder();
        for (int i = 0; i < ptString.length(); i += 8) {
            String ptBlock = ptString.substring(i, Math.min(i + 8, ptString.length()));
            String binaryString = stringToBinary(pad(ptBlock));
            // while (binaryString.length() < 64) {
            //     binaryString += "00000000";
            // }
            String blockEncrypted = desEnc(binaryString);
            cipherText.append(blockEncrypted);
        }
        return cipherText.toString();
    }

    public static String des_decrypt_text(String cipherText) {
        StringBuilder plainText = new StringBuilder();
        for (int i = 0; i < cipherText.length(); i += 64) {
            String cipherBlock = cipherText.substring(i, Math.min(i + 64, cipherText.length()));
            String blockDecrypted = desEnc(cipherBlock);
            plainText.append(blockDecrypted);
        }
        return (plainText.toString());
    }
}
