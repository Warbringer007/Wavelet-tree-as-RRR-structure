#include "rrr_lookup_table.h"

//Constructor, generates RRR Lookup Table
RRRLookupTable::RRRLookupTable(uint32_t block_length) {
    block_length_ = block_length;
    //One of the possible permutations
    std::string permutation;
    //Permutation representation in bit vector
    std::vector<bool> permutation_vector;
    for ( int i = 0; i < block_length; i++) {
        permutation.append("0");
        permutation_vector.push_back(false);
    }
    //First permutation with only zeroes
    table.push_back(permutation_vector);
    for ( int i = 0; i < block_length; i++) {
        permutation[block_length-i-1] = '1';
        permutation_vector.clear();
        do {
            //Generate new permutation
            std::vector<bool> current_permutation = RRRLookupTable::ConvertStringToBitVector(permutation);
            //Add new permutation in bit vector
            for ( int j = 0; j < block_length; j++) {
                permutation_vector.push_back(current_permutation[j]);
            }
        } while(next_permutation(permutation.begin(), permutation.end()));
        //Adds one completed class to table
        table.push_back(permutation_vector);
    }
}

//Destructor
RRRLookupTable::~RRRLookupTable() {

}

//Converts string to bit vector
std::vector<bool> RRRLookupTable::ConvertStringToBitVector(const std::string& string_) {
    std::vector<bool> bitvector;
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
