#ifndef WAVELET_TREE_H
#define WAVELET_TREE_H
#include <stdint.h>

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class wavelet_tree
{
    public:

        //Constructor
        wavelet_tree();

        //Destructor
        ~wavelet_tree();

        //Get string from file
        std::string GetStringFromFile(std::string file);

        //Create Wavelet Tree
        std::vector<std::string> CreateTree(const std::string& input);

        //Convert string to bitvector(main)
        std::vector<bool> ConvertStringToBitVectorMain(const std::string& string_);

        //Convert string to bitvector(left)
        std::vector<bool> ConvertStringToBitVectorLeft(const std::string& string_);

        //Convert string to bitvector(right)
        std::vector<bool> ConvertStringToBitVectorRight(const std::string& string_);
    private:
};

#endif // WAVELET_TREE_H
