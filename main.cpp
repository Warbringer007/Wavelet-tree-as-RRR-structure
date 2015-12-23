#include <iostream>
#include <vector>
#include <string>
#include "rrr_struct.h"

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
    novi = "atggtgacctgtcaagagctagctagctgacttgagctagctagctgacgagctagctagctgac";
    uint32_t string_length = novi.length();
    std::vector<bool> jedan;
    for ( int i = 0; i < string_length; i++) {
        if ( novi[i] == 'a' || novi[i] == 'g') {
            jedan.push_back(false);
        } else {
            jedan.push_back(true);
        }
    }
    RRRStruct rrr = RRRStruct(string_length);
    double novo = log2((double)string_length/2.0);
    uint32_t bits_per_block = (int) (floor(log2(string_length))/2);
    uint32_t blocks_per_superblock = bits_per_block * (int)(floor(log2(string_length)));
    cout << "Hello world!" << endl;
    novi = ConvertBitVectorToString(jedan);
    jedan = ConvertStringToBitVector(novi);
    cout << novo << "dasidaia" << endl;
    cout << novi << endl;
    cout << string_length << endl;
    cout << bits_per_block << endl;
    cout << blocks_per_superblock << endl;
    return 0;
}
