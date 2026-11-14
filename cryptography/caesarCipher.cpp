#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string caesarCipher(const string& text, int shift){
    string result = "";

    // Normalize shift to handle values >26 or negative shifts
    shift = (shift % 26 + 26) % 26; //mod26

    for (char ch : text){
        if (isupper(ch)){
            result += char((ch - 'A' + shift) % 26 + 'A');
        }
        else if (islower(ch)){
            result += char((ch - 'a' + shift) % 26 + 'a');
        }
        else {
            // Keep spaces, number, and punctuation unchanged
            result += ch;
        }
    }
    return result;
}

string decryptCaesar(const string& text, int shift){
    // Shifting the opposite direction
    return caesarCipher(text, -shift);
}

int main(){
    string message = "Hello Planet!";
    int shift = 5;
    
    string encrypted = caesarCipher(message, shift);
    string decrypted = decryptCaesar(encrypted, shift);

    cout << "Original Message   : " << message << endl;
    cout << "Encrypted          : " << encrypted << endl;
    cout << "Decrypted          : " << decrypted << endl;


    return 0;
}