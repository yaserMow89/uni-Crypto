#include <iostream>
#include <string>
#include <cstdlib>
#include <array>
#include <vector>
#include <bitset>

using namespace std;

vector<std::string> round_keys(16);


std::string byteToBinary(char byte) {
    std::bitset<8> bits(byte);
    return bits.to_string();
}

string binaryToHex(string binaryinput)
{
	string paddedBinary = binaryinput;

	while (paddedBinary.size() % 4 != 0)
		{
			paddedBinary = "0" + paddedBinary;
		}
	string hexstring;
	for (int i = 0; i < paddedBinary.length(); i += 4)
		{
			string nibble = paddedBinary.substr(i, 4);
			int decimal = stoi(nibble, nullptr, 2);
			char hexdigit[2];
			sprintf(hexdigit, "%X", decimal);
			hexstring += hexdigit;
		}
	return hexstring;
}

std::string stringToBinary(const std::string& input) {
    std::string binaryString;
    binaryString.reserve(input.length() * 8);

    for (char c : input) {
        binaryString += byteToBinary(c);
    }

    return binaryString;
}

string stringToHex(string input)
{
	string hexString;
	for (char c: input)
		{
			char hexDigit[3];
			sprintf(hexDigit, "%02X", c);
			hexString += hexDigit;
		}
	return hexString;
}

string hexToString(string input)
{
	string result;
	for (int i = 0; i < input.length(); i+=2)
		{
			string hexDigit = input.substr(i,2);
			int decimal = stoi(hexDigit, nullptr, 16);
			result += static_cast<char>(decimal);
		}
	return result;
}

string binaryToString(string input)
{
	string result;

	for (int i = 0; i < input.length(); i += 8)
		{
			string byteStr = input.substr(i, 8);
			int decimal = stoi(byteStr, nullptr, 2);
			result += static_cast<char>(decimal);
		}
	return result;
}

string decimalToBinary(int decimal)
{
	string binary;
	int index = 3;
	while (decimal != 0)
		{
			binary += ((decimal % 2 == 0)? '0' : '1');
			decimal /= 2;
			index -= 1;
		}
	while (index >= 0 )
		{
			binary += '0';
			index -= 1;
		}
	return binary;
}

int binaryTodecimal(string input)
{
	int decimal = 0;
	int size = input.length();
	int counter = 0;
	for (int i = size - 1; i >= 0; i--)
		{
			if (input[i] == '1')
				{
					decimal += 1 << counter;
				}
			counter += 1;
		}
	return decimal;
}

string shift_left_once(string keychunk)
{
	string shifted;
	shifted = keychunk.substr(1);
	shifted += keychunk[0];
	return shifted;
}

string shift_left_twice(string keychunk)
{
	string shifted = keychunk.substr(2);
	shifted += keychunk.substr(0, 2);
	return shifted;
}

string Xor(string a, string b)
{
    //cout <<"Strings "<<a<<" and "<<b<<endl;
	string result;
	for (int i = 0; i < b.length(); i++)
		{
			if(a[i] != b[i])
				{
					result += '1';
				}
			else
				{
					result += '0';
				}
		}
	return result;
}

void generate_keys(string key) {

    int pc1[56] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
    };
    int pc2[48] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    };

    std::string permKey(56, ' ');
    for (int i = 0; i < 56; i++) {
        permKey[i] = key[pc1[i] - 1];
    }

    std::string left = permKey.substr(0, 28);
    std::string right = permKey.substr(28, 28);

    for (int i = 0; i < 16; i++) {
        if (i == 0 || i == 1 || i == 8 || i == 15) {
            left = shift_left_once(left);
            right = shift_left_once(right);
        } else {
            left = shift_left_twice(left);
            right = shift_left_twice(right);
        }

        std::string combinedKey = left + right;

        std::string roundKey(48, ' ');
        for (int j = 0; j < 48; j++) {
            roundKey[j] = combinedKey[pc2[j] - 1];
        }

        round_keys[i] = roundKey;
    }
}
	

std::string desEnc(std::string block) {
    std::vector<int> initial_permutation = {
        58,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7
    };
    std::vector<int> expansion_table = {
        32,1,2,3,4,5,4,5,
        6,7,8,9,8,9,10,11,
        12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,
        22,23,24,25,24,25,26,27,
        28,29,28,29,30,31,32,1
    };
    std::vector<std::vector<std::vector<int>>> substition_boxes = {
        {
            {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
            {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
            {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
            {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
        },
        {
            {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
            {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
            {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
            {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7}
        },
        {
            {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
            {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
            {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
            {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
        },
        {
            {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
            {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
            {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
            {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
        },
        {
            {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
            {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
            {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
            {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
        },
        {
            {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
            {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
            {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
            {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1}
        },
        {
            {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
            {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
            {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
            {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
        },
        {
            {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
            {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
            {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},
            {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
        }
    };
    std::vector<int> permutation_tab = {
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    };
    std::vector<int> inverse_permutation = {
        40,8,48,16,56,24,64,32,
        39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,
        37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,
        35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,
        33,1,41,9,49,17,57,25
    };
    string perm(64, '0'); 

    for(int i = 0; i < 64; i++) {
        perm[i] = block[initial_permutation[i]-1];
    }
    
    string left = perm.substr(0, 32);
    string right = perm.substr(32, 32);
    
    for(int i = 0; i < 16; i++) {
    
        string rightExpanded(48, '0');
        
        for(int j = 0; j < 48; j++) {
            rightExpanded[j] = right[expansion_table[j]-1];
        }
        
        string xored = Xor(round_keys[i], rightExpanded); 
        
        string res(32, '0');
        
        for(int j = 0; j < 8; j++) {
        
            string row1; 
            row1 += xored[j*6];
            row1 += xored[j*6 + 5];
            
            int row = binaryTodecimal(row1);
            
            string col1 = xored.substr(j*6 + 1, 4);  
            
            int col = binaryTodecimal(col1);
            
            int val = substition_boxes[j][row][col];
            
            res += decimalToBinary(val);
        }
        
        string perm2(32, '0');
        
        for(int j = 0; j < 32; j++) {
            perm2[j] = res[permutation_tab[j]-1];
        }
        
        xored = Xor(perm2, left); 
        left = xored;
    
        if(i < 15) {
            string temp = right;
            right = xored;
            left = temp; 
        }
    }   
    
    string combinedText = left + right;
    string ciphertext(64, '0');  
    
    for(int i = 0; i < 64; i++) {
        ciphertext[i] = combinedText[inverse_permutation[i]-1]; 
    }
    
    return ciphertext;
}
string desDecryption(string ciphertext)
{
	int i = 15;
	int j = 0;
	while (i > j)
		{
			string temp = round_keys[i];
			round_keys[i] = round_keys[j];
			round_keys[j] = temp;
			i--;
			j++;
		}
	string decrypted = desEnc(ciphertext);
	return decrypted;
}

string genKey() 
{
    int keySize = 64;
    int keyBits = rand() % (1 << keySize);
    std::string key = std::bitset<64>(keyBits).to_string();
    return key;
}

string pad(string input_str)
{
	int padding_size = 8 - (input_str.length() % 8);
	if (padding_size != 8)
		{
			string temp  = input_str;
			for (int i = 0; i < padding_size; i++)
				{
					temp.push_back(padding_size + '0');
				}
			//cout<<"Padded temp "<<temp.length()<<endl;
			return temp;
		}
	else{
	    return input_str;
	}
}

string des_encrypt_text(string pt_string)
{
	string padded_pt = pad(pt_string);
	//cout<<"PAdded String "<<padded_pt<<endl;
	int num_blocks = padded_pt.length() / 8;
	//cout<<"Blocks Num "<<num_blocks<<endl;

	string blocks;
	for (int i = 0; i < num_blocks; i++)
		{
			blocks += padded_pt.substr(i * 8, 8);
		}
	string encrypted;
	for (int i = 0; i < num_blocks; i++)
		{
			string ct = desEnc(stringToBinary(blocks.substr(i*8, 8)));
			encrypted += ct;
		}
	return encrypted;
}

string des_decrypt_text(string ct_string)
{
	string blocks[ct_string.length()];
	for (int i = 0; i < ct_string.length(); i += 64)
		{
			blocks[i/64] = ct_string.substr(i, 64);
		}
	string decrypted;
	for (int i = 0; i < ct_string.length()/64; i++)
		{
			decrypted += desDecryption(blocks[i]);
		}
	return decrypted;
}

int main() 
{
    string my_key = "101010101011101100001001000110000010011100110110110011001101110110101010101110110000100100011000001001110011011011001100110111011010101010111011000010010001100000100111001101101100110011011101";
    generate_keys(my_key);
    string ptString = "The quick brown fox jumps over the lazy dog";
    std::cout << "Plain text (C++): " << stringToHex(ptString) << endl; 
    if (my_key.length() == 192 && !ptString.empty()) 
    {
        std::string key1 = my_key.substr(0, 64);
        std::string key2 = my_key.substr(64, 64);
        std::string key3 = my_key.substr(128, 64);

        generate_keys(key1.c_str());
        std::string encrypted_text = des_encrypt_text(ptString.c_str());

        generate_keys(key2.c_str());
        encrypted_text = des_decrypt_text(encrypted_text.c_str());

        generate_keys(key3.c_str());
        encrypted_text = des_encrypt_text(binaryToString(encrypted_text.c_str())); 
        std::cout << "Encrypted Text (C++): " << binaryToHex(encrypted_text) << endl;
        std::string decrypted_text = des_decrypt_text(encrypted_text.c_str());

        generate_keys(key2.c_str());
        decrypted_text = des_encrypt_text(binaryToString(decrypted_text.c_str()));

        generate_keys(key1.c_str());
        decrypted_text = des_decrypt_text(decrypted_text.c_str());

        std::cout << "Decrypted Text (C++): "<< binaryToHex(decrypted_text) << std::endl;
    }
    return 0;
}
