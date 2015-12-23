#include <iostream>
#include <vector>
#include <string>

using namespace std;

string ConvertBitVectorToString(const std::vector<bool>& bitvector) {
    string string_;
    uint32_t vector_length = bitvector.size();
    for ( int i = 0; i < vector_length; i++) {
        if ( bitvector[i]) {
            string_.append("1");
        } else {
            string_.append("0");
        }
    }
    return string_;
}

std::vector<bool> ConvertStringToBitVector(const string& string_) {
    std:vector<bool> bitvector;
    uint32_t string_length = string_.length();
    for ( int i = 0; i < string_length; i++) {
        if ( string_[i] == '1') {
            bitvector.push_back(true);
        } else {
            bitvector.push_back(false);
        }
    }
    return bitvector;
}

int main() {
    string novi;
    novi = "atggtgacctg";
    uint32_t string_length = novi.length();
    std::vector<bool> jedan;
    for ( int i = 0; i < string_length; i++) {
        if ( novi[i] == 'a' || novi[i] == 'g') {
            jedan.push_back(false);
        } else {
            jedan.push_back(true);
        }
    }
    cout << "Hello world!" << endl;
    novi = ConvertBitVectorToString(jedan);
    jedan = ConvertStringToBitVector(novi);
    cout << novi << endl;
    novi = ConvertBitVectorToString(jedan);
    cout << novi << endl;
    return 0;
}
