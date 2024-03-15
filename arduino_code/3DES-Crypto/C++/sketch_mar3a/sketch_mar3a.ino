// This can only be ran after Installing the Crypto-Library: 
// https://github.com/Octoate/ArduinoDES
// Please give some time after flushing the code


#include <DES.h>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// Only Encrypts 64 bits of data (Library Limitation)

DES Des;

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long start_time = millis();
 
  cout << "======================= 3DES (C++) ========================= " << endl;
  three_des();
  std::cout << '\n'<< std::endl; 


  // Followings are for measurement purposes
  Serial.print("Free Heap: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");
  unsigned long end_time = millis();
  Serial.print("Execution Time: ");
  Serial.print(end_time - start_time);
  Serial.println("milliseconds");
  delay(20000);
}

void three_des()
{
  byte out_bytes[8];
                    // Not all the 128 bits are going to be Encrypted
                    // Only the first 64 bits are Encrypted
                    // The Library limitation
  byte in_bytes[] = { 01001001, 00100000, 01100111, 01101111, \
                      01110100, 00100000, 00110001, 00100000, \
                      01101001, 01101110, 00100000, 01000001, \
                      01010011, 01000101, 01001100, 00100000};
                      // Above correspons to "I got 1 in ASEL "
                      // Only first 8 Bytes are going under the 
                      // Operation, being: "I got 1 "
  byte key[] = { 0x62, 0x65, 0x64, 0x61, 0x6E, 0x67, 0x61, 0x74,
                0x5e, 0xf7, 0x20, 0x15, 0x37, 0x98, 0x38, 0x3b,
                0x62, 0x65, 0x64, 0x61, 0x6E, 0x67, 0x61, 0x74};

  
  cout << "plaintext Hex: " << endl;
  printArrayHex(in_bytes);
  std::cout << '\n'<< std::endl; 
  
  // Encryption
  cout << "Encrypted Hex: " << endl;
  Des.tripleEncrypt(out_bytes, in_bytes, key);
  printArrayHex(out_bytes);
  std::cout << '\n'<< std::endl; 
  //Replace contents of in with contents of out
  for (int i = 0; i < 8; i++)
  {
    in_bytes[i] = out_bytes[i];
  }
  cout << "Decrypted Hex: " << endl;
  
  // Decryption
  Des.tripleDecrypt(out_bytes, in_bytes, key);
  
  printArrayHex(out_bytes);
}


void printArrayHex(byte output[])
{
  for (int i = 0; i < 8; i++)
  {
    if (output[i] < 0x10)
    {
      Serial.print("0");
    }
    Serial.print(output[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}