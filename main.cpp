#include <string>
#include <cstring>
#include <iostream>

using namespace::std;

string encryptColumn(int n_rows, int key_len, int message_len, string message, int columns_order[]){

    //Creating the matrix through columns -> Transposition
    int x = 0;

    char col_matrix[n_rows + 1][key_len];
    for(int i = 0; i < n_rows + 1; i++){
        for(int j = 0; j < key_len; j++){
            if(x >= message_len){
                col_matrix[i][j] = '_';
            } else {
                col_matrix[i][j] = message[x];
            }
            x++;
        }
    }
    
    int y = 1;
    string encrypted_text;

    while(y <= key_len){
        for(int i = 0; i < key_len; i++){
            int k = columns_order[i];
            if(k == y){
                for (int j = 0; j < n_rows + 1; j++){
                    encrypted_text += col_matrix[j][i];
                }
                y++;
            }
        }
    }
    return encrypted_text;
}

string decryptColumn(int n_rows, int key_len, string message, int columns_order[]){

    char col_matrix[n_rows + 1][key_len];

    int x = 0;
    int y = 1;

    while(y <= key_len){
        for(int i = 0; i < key_len; i++){
            int k = columns_order[i];
            if (k == y){
                for (int j = 0; j < n_rows + 1; j++){
                    col_matrix[j][i] = message[x];
                    x++;
                }
                y++;
            }
        }
    }

    string true_message = "";

    for(int i = 0; i < n_rows + 1; i ++){
        for(int j = 0; j < key_len; j++){
            if(col_matrix[i][j] == '_'){
                col_matrix[i][j] == ' ';
            }
            true_message += col_matrix[i][j];
        }
    }

    return true_message;
}


string SubstitutionEncrypt(string message, string key) {
    string substituted_message = "";
    int key_len = key.length();

    for (int i = 0; i < message.length(); i++) {
        // Get the current character and its corresponding key character
        char msg_char = message[i];
        char key_char = key[i % key_len];  // Repeat the key if the message is longer than the key

        // Shift the message character based on the key character's ASCII value
        int shift_value = (int)key_char % 26;  // Limit the shift to 26 for alphabetic characters
        char substituted_char;

        // Apply shift to uppercase letters
        if (isupper(msg_char)) {
            substituted_char = 'A' + (msg_char - 'A' + shift_value) % 26;
        }
        // Apply shift to lowercase letters
        else if (islower(msg_char)) {
            substituted_char = 'a' + (msg_char - 'a' + shift_value) % 26;
        }
        // For non-alphabetic characters, leave them unchanged
        else {
            substituted_char = msg_char;
        }

        substituted_message += substituted_char;
    }
    return substituted_message;
}

// Function to undo the substitution during decryption
string SubstitutionDecrypt(string message, string key) {
    string original_message = "";
    int key_len = key.length();

    for (int i = 0; i < message.length(); i++) {
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

string encrypt(int n_rows, int key_len, int message_len, string message, string key, int columns_order[]){
    string currentMes = message;
    currentMes = encryptColumn(n_rows, key_len, message_len, currentMes, columns_order);
    currentMes = SubstitutionEncrypt(currentMes,key);

    return currentMes;
}

string decrypt(int n_rows, int key_len, string cipher, string key, int columns_order[]){
    string currentMes = cipher;
    currentMes = SubstitutionDecrypt(currentMes, key);
    currentMes = decryptColumn(n_rows, key_len, currentMes, columns_order);

    return currentMes;
}

int main(){
    string message;
    string key;

    cout << "Enter message: " << endl;
    getline(cin, message);

    cout << "Enter key: " << endl;
    cin >> key;

    int key_len = key.length();
    int message_len = message.length();

    int val = 1; 
    int count = 0;
    int ind;


    int columns_order[key_len];

    memset(columns_order, 0, sizeof(columns_order));

    while(count < key_len){
        int min = 999;
        for (int i = 0; i < key_len; i++){
            if((min > int(key[i])) && (columns_order[i] == 0)){
                min = int(key[i]);
                ind = i;
            }
        }
        columns_order[ind] = val;
        count++;
        val++;
    }

    int n_rows = message_len / key_len;

    string ciphered_text = encrypt(n_rows, key_len, message_len, message, key, columns_order);

    cout << "Encrypted: " << ciphered_text << endl;

    string deciphered_text = decrypt(n_rows, key_len, ciphered_text, key, columns_order);

    cout << "Decrypted: " << deciphered_text << endl;

    return 1;
}