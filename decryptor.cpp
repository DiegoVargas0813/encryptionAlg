#include <string>
#include <iostream>
#include <stdexcept>
#include <cstring>

using namespace std;

// Helper function to convert a hexadecimal string back to its original string
string hexToString(const string& input) {
    const auto len = input.length();
    if (len & 1) throw std::invalid_argument("Odd length");

    string output;
    output.reserve(len / 2);

    for (size_t i = 0; i < len; i += 2) {
        unsigned char hi = input[i];
        unsigned char lo = input[i + 1];

        hi = hi >= 'A' ? hi - 'A' + 10 : hi - '0';
        lo = lo >= 'A' ? lo - 'A' + 10 : lo - '0';

        output.push_back((hi << 4) | lo);
    }

    return output;
}

// Function to undo bit shifting and XOR during decryption
string BitShiftXORDecrypt(const string& message, const string& key) {
    string result = "";
    int key_len = key.length();

    for (size_t i = 0; i < message.length(); i++) {
        unsigned char encrypted_char = message[i];
        unsigned char key_char = key[i % key_len];

        // Reverse XOR with key_char
        unsigned char shifted_char = encrypted_char ^ key_char;

        // Rotate bits to the right by 2 positions
        unsigned char msg_char = (shifted_char >> 2) | (shifted_char << 6);

        result += msg_char;
    }

    return result;
}

// Function to undo the substitution during decryption
string SubstitutionDecrypt(const string& message, const string& key) {
    string original_message = "";
    int key_len = key.length();

    for (size_t i = 0; i < message.length(); i++) {
        char msg_char = message[i];
        char key_char = key[i % key_len];

        int shift_value = (int)key_char % 26;
        char original_char;

        // Reverse shift for uppercase letters
        if (isupper(msg_char)) {
            original_char = 'A' + (msg_char - 'A' - shift_value + 26) % 26;
        }
        // Reverse shift for lowercase letters
        else if (islower(msg_char)) {
            original_char = 'a' + (msg_char - 'a' - shift_value + 26) % 26;
        }
        // Leave non-alphabetic characters unchanged
        else {
            original_char = msg_char;
        }

        original_message += original_char;
    }
    return original_message;
}

// Function to decrypt the columnar transposition
string decryptColumn(int n_rows, int key_len, const string& message, const int columns_order[]) {
    int total_chars = (n_rows + 1) * key_len;
    char col_matrix[n_rows + 1][key_len];
    int x = 0;
    int y = 1;

    while (y <= key_len) {
        for (int i = 0; i < key_len; i++) {
            int k = columns_order[i];
            if (k == y) {
                for (int j = 0; j < n_rows + 1; j++) {
                    if (x < message.length()) {
                        col_matrix[j][i] = message[x];
                    } else {
                        col_matrix[j][i] = '_';
                    }
                    x++;
                }
                y++;
            }
        }
    }

    string true_message = "";

    for (int i = 0; i < n_rows + 1; i++) {
        for (int j = 0; j < key_len; j++) {
            if (col_matrix[i][j] == '_') {
                col_matrix[i][j] = ' ';
            }
            true_message += col_matrix[i][j];
        }
    }

    return true_message;
}

// The main decryption function
string decrypt(const string& cipher_hex, const string& key) {
    // Convert hex string back to original encrypted string
    string cipher = hexToString(cipher_hex);

    // First, reverse the bit shift and XOR operations
    string after_bitshift_xor = BitShiftXORDecrypt(cipher, key);

    // Next, reverse the substitution cipher
    string after_substitution = SubstitutionDecrypt(after_bitshift_xor, key);

    // Prepare the columns order based on the key
    int key_len = key.length();
    int columns_order[key_len];

    // Initialize columns_order
    int val = 1;
    int count = 0;
    int ind;

    memset(columns_order, 0, sizeof(columns_order));

    while (count < key_len) {
        int min = 999;
        for (int i = 0; i < key_len; i++) {
            if ((min > int(key[i])) && (columns_order[i] == 0)) {
                min = int(key[i]);
                ind = i;
            }
        }
        columns_order[ind] = val;
        count++;
        val++;
    }

    // Calculate the number of rows used during encryption
    int message_len = after_substitution.length();
    int n_rows = message_len / key_len;
    if (message_len % key_len != 0) {
        n_rows++;
    }
    n_rows -= 1;  // Adjust for the way rows are calculated in the original code

    // Finally, reverse the columnar transposition
    string original_message = decryptColumn(n_rows, key_len, after_substitution, columns_order);

    return original_message;
}

int main() {
    string cipher_hex;
    string key;

    cout << "Enter the encrypted message (in hex): " << endl;
    getline(cin, cipher_hex);

    cout << "Enter the key: " << endl;
    cin >> key;

    string decrypted_message = decrypt(cipher_hex, key);

    cout << "Decrypted message: " << decrypted_message << endl;

    return 0;
}
