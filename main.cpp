#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <sys/time.h>
#include "rrr_struct.h"
#include "wavelet_tree.h"

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

uint32_t ConvertBitVectorToInt(std::vector<bool> bitvector) {
    uint32_t result = 0;
    for ( int i = bitvector.size(); i > 0; i--) {
        if ( bitvector[bitvector.size()-i]) {
            result += pow(2, i-1);
        }
    }
    return result;
}

/*void RRRLookupTable(uint32_t block_length) {
    string permutation;
    std::vector<bool> permutation_vector;
    for ( int i = 0; i < block_length; i++) {
        permutation.append("0");
        permutation_vector.push_back(false);
    }
    table.push_back(permutation_vector);
    //cout << ConvertBitVectorToString(table[0]) << endl;
    //cout << "----" << endl;
    for ( int i = 0; i < block_length; i++) {
        permutation[block_length-i-1] = '1';
        permutation_vector.clear();
        do {
            std::vector<bool> current_permutation = ConvertStringToBitVector(permutation);
            for ( int j = 0; j < block_length; j++) {
                permutation_vector.push_back(current_permutation[j]);
            }
            //permutation_vector.push_back(ConvertStringToBitVector(permutation));
            //cout << ConvertBitVectorToString(permutation_vector) << endl;
        } while(next_permutation(permutation.begin(), permutation.end()));
        //cout << "----" << endl;
        table.push_back(permutation_vector);
        //cout << ConvertBitVectorToString(table[i+1]) << endl;
    }
}*/

uint8_t NumberOfOnes(std::vector<bool> block) {
    uint8_t result = 0;
    for ( int i = 0; i < block.size(); i++) {
        if ( block[i]) result += 1;
    }
    return result;
}

//Convert integer to bit vector
std::vector<bool> ConvertIntToBitVector(uint8_t number) {
    std::vector<bool> result;
    std::vector<bool> result_reverse;
    if ( number == 0) {
        result_reverse.push_back(false);
        return result_reverse;
    }
    while ( number > 1) {
        if ( ( number%2 ) == 0 ) result_reverse.push_back(false);
        else result_reverse.push_back(true);
        number /= 2;
    }
    result_reverse.push_back(true);
    //Integer is converted in it's bit representation
    //But in reverse order, it must be reversed
    uint8_t length = result_reverse.size();
    for ( int i = 0; i < length; i++ ) {
        result.push_back(result_reverse[length-i-1]);
    }
    return result;
}

int main() {
    struct timeval start_time, end_time;
    long us;
    bool success;
    uint32_t result = 0;
    string novi;
    string novi2;
    std::vector<std::string>rastavljeni;
    string file="";
    novi = "atggtgacctgtcaagagctagctagctgacttgagctagctagctgacgagctagctagctgac";
    //atggtgacctgtcaagagctagctagctgacttgagctagctagctgacgagctagctagctgac
    gettimeofday(&start_time,NULL);
    Wavelet_tree wt=Wavelet_tree("primjer2.fa");
    gettimeofday(&end_time,NULL);
    us = (long)((1000000 * end_time.tv_sec + end_time.tv_usec) -
                    (1000000 * start_time.tv_sec + start_time.tv_usec));
    cout <<us <<" us" <<endl;
    //novi2=wt.GetStringFromFile(file);
    //cout<<wt<< endl;
    /*uint32_t string_length = novi.length();
    std::vector<bool> jedan;
    for ( int i = 0; i < string_length; i++) {
        if ( novi[i] == 'a' || novi[i] == 'g') {
            jedan.push_back(false);
        } else {
            jedan.push_back(true);
        }
    }
    RRRStruct rrr = RRRStruct();
    rrr.DefineStruct(65);
    for ( int i = 0; i < 21; i++ ) {
        std:vector<bool> moj;
        moj.push_back(jedan[i*3]);
        moj.push_back(jedan[i*3+1]);
        moj.push_back(jedan[i*3+2]);
        rrr.NewBlock(moj);
    }
    std::vector<bool> moj;
    moj.push_back(jedan[63]);
    moj.push_back(jedan[64]);
    rrr.NewBlock(moj);
    /*cout << "rank 28:" << rrr.Rank(28,true) << endl;
    cout << "select1 2:" << rrr.Select1(2) << endl;
    cout << "select0 2:" << rrr.Select0(2) << endl;*/
    gettimeofday(&start_time,NULL);
    result=wt.Rank('A',11);
    cout << "rank 11, a:" << wt.Rank('A',4500000) << endl;
    cout << "rank 11, g:" << wt.Rank('G',4500000) << endl;
    cout << "rank 11, t:" << wt.Rank('T',4500000) << endl;
    cout << "rank 11, c:" << wt.Rank('C',4500000) << endl;
    gettimeofday(&end_time,NULL);
    us = (long)((1000000 * end_time.tv_sec + end_time.tv_usec) -
        	(1000000 * start_time.tv_sec + start_time.tv_usec));
    cout << us <<" us" <<endl;
    cout << "select 3, a:" << wt.Select('A',450000) << endl;
    cout << "select 3, g:" << wt.Select('G',450000) << endl;
    cout << "select 3, t:" << wt.Select('T',450000) << endl;
    cout << "select 3, c:" << wt.Select('C',450000) << endl;
    us = (long)((1000000 * end_time.tv_sec + end_time.tv_usec) -
        	(1000000 * start_time.tv_sec + start_time.tv_usec));
    cout << us <<" us" <<endl;
    return 0;
}
