/* 
 * File:   main.cpp
 * Author: Khadiza Akter
 * Created on November 22, 2024, 12:46 AM
 * Purpose: Demonstrates a C++ program that encrypt and decrypts a
 *           message from the user based on Vigenere cipher.
 */
//System Libraries
#include <iostream> // Input and output library
#include <string>   // For working with strings
#include <cctype>   // For isalpha() and toupper()
#include <climits>  // INT_MAX for infinity
using namespace std;//STD Name-space where Library is compiled


//Function Prototypes
string preprocessKey(const string&);
string keyProcessor(const string&, const string&);
string encrypt(const string&, const string&);
string decrypt(const string&, const string&);

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Declare variables here
    string plaintext, keyword, ciphertext; // Strings for inputs and outputs
    int choice; // User's menu choice
    bool exit = false;

    // Loop to incorporate with menu choice
    while (!exit) {
        // Show menu options
        cout << "=== Vigenère Cipher Menu ===\n";
        cout << "1. Encrypt Text\n"; 
        cout << "2. Decrypt Text\n"; 
        cout << "3. Exit\n"; 
        cout << "Enter your choice: "; 
        cin >> choice; 
        
        // Input validation for choice
        if (cin.fail() || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue;
        }
        cin.ignore();// Ignore the newline after the choice input
        switch (choice) {
            case 1:  // Encryption option
                cout << "Enter Plaintext: "; // Ask for plain text
                getline(cin, plaintext); // Read the full line
                cout << "Enter keyword: "; // Ask for keyword
                getline(cin, keyword); // Read the full keyword
                ciphertext = encrypt(plaintext, keyword); // Encrypt the text
                cout << "Encrypted text: " << ciphertext << "\n"; // Show result
                break;
            
            case 2:  // Decryption option
                cout << "Enter Ciphertext: "; // Ask for cipher text
                getline(cin, ciphertext); // Read the full line
                cout << "Enter keyword: "; // Ask for keyword
                getline(cin, keyword); // Read the full keyword
                plaintext = decrypt(ciphertext, keyword); // Decrypt the text
                cout << "Decrypted text: " << plaintext << "\n"; // Show result
                break;
            
            case 3: // Exit the program
                exit = true;
                cout << "Exiting program. Goodbye!\n";
                break;
            
        } // End of switch case
    } // End of while loop

    return 0; // End the program
}

//********************************************************************
// Definition of preprocessKey function. This prepares key by removing
// non-alphabetic characters and converting all letters to uppercase.
// @param keyword The input keyword.
// @return A cleaned-up version of the keyword.
//********************************************************************
string preprocessKey(const string& keyword) {
    string cleanKey = "";            // Store the cleaned keyword
    for (char ch : keyword) { 
        if (isalpha(ch)) {           // Check if the character is a letter
            cleanKey += toupper(ch); // Convert to uppercase and add to cleanKey
        }
    }
    return cleanKey;                 // Return the processed keyword
}

//********************************************************************
// Definition of keyProcessor, creates a key as the same length of text
// The key repeats if it's shorter than the text. 
// @param text The input text (plain text or cipher-text).
// @param keyword The original keyword.
// @return A key string aligned with the length of the text.
//********************************************************************
string keyProcessor(const string& text, const string& keyword) {
    string key = preprocessKey(keyword); // Clean the keyword
    string result = "";                  // Final key to be returned
    int keyIndex = 0;                    // Position in the keyword

    for (char ch : text) { 
        if (isalpha(ch)) {               // Match key only for letters
            result += key[keyIndex % key.size()]; // Add the current key letter
            keyIndex++;                  // Move to the next key letter
        } else {
            result += ch;                // Keep non-letters unchanged
        }
    }
    return result;                       // Return the full key
}

//********************************************************************
// Definition of encrypt function. This function encrypts 
// given plain-text using the Vigenère cipher.
// @param plaintext The text to encrypt.
// @param keyword The keyword used for encryption.
// @return The encrypted cipher-text.
//********************************************************************
string encrypt(const string& plaintext, const string& keyword) {
    string key = keyProcessor(plaintext, keyword); // Generate the matching key
    string ciphertext = ""; // To store the encrypted result

    for (int i = 0; i < plaintext.size(); i++) {
        if (isalpha(plaintext[i])) { // Encrypt only letters
            char offset = isupper(plaintext[i]) ? 'A' : 'a'; 
            ciphertext += ((plaintext[i] - offset + 
                    (key[i] - 'A')) % 26) + offset; // Encrypt character
        } else {
            ciphertext += plaintext[i]; // Keep non-letters as-is
        }
    }
    return ciphertext; // Return the encrypted text
}

//********************************************************************
// Definition of Decrypt function. This function decrypt
// the given cipher-text using the Vigenère cipher.
// @param ciphertext The text to decrypt.
// @param keyword The keyword used for decryption.
// @return The decrypted plain text.
//********************************************************************
string decrypt(const string& ciphertext, const string& keyword) {
    string key = keyProcessor(ciphertext, keyword); // Generate the matching key
    string plaintext = ""; // To store the decrypted result

    for (int i = 0; i < ciphertext.size(); i++) {
        if (isalpha(ciphertext[i])) { // Decrypt only letters
            // Check case (uppercase or lowercase)
            char offset = isupper(ciphertext[i]) ? 'A' : 'a'; 
            plaintext += ((ciphertext[i] - offset - 
                    (key[i] - 'A') + 26) % 26) + offset; // Decrypt character
        } else {
            plaintext += ciphertext[i]; // Keep non-letters as-is
        }
    }
    return plaintext; // Return the decrypted text
}
