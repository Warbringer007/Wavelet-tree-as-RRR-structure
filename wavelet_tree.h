#ifndef WAVELET_TREE_H
#define WAVELET_TREE_H

#include "rrr_struct.h"
#include <stdint.h>
#include <fstream>
#include <iostream>

class Wavelet_tree
{
    public:

        //Constructor
        Wavelet_tree(std::string file);

        //Destructor
        ~Wavelet_tree();

        //Calculates rank from tree
        uint32_t Rank(char letter, uint32_t number);

        //Calculates select from tree
        uint32_t Select(char letter, uint32_t number);
    private:

        //Bitvectors of root, left and right branch
        std::vector<bool> root;
        std::vector<bool> left;
        std::vector<bool> right;

        RRRStruct root_RRR;
        RRRStruct left_RRR;
        RRRStruct right_RRR;

        //Get string from file
        void GetStringFromFile(std::string file);

        //Create RRR from bitvector
        void CreateRRRFromBitVector(RRRStruct* struct_, std::vector<bool> vector_);

        //Convert bit vector to integer
        std::string ConvertBitVectorToString(std::vector<bool> bitvector);
};

#endif // WAVELET_TREE_H
