#include "wavelet_tree.h"

wavelet_tree::wavelet_tree(){

}

wavelet_tree::~wavelet_tree(){

}

std::string wavelet_tree:: GetStringFromFile(std::string file){
    std::ifstream input ("example.txt");
    //std::ifstream input(file.c_str());

	std::string bzvz = "";
	std::string input_string = "";

	while (std::getline(input, bzvz)) {
			input_string += bzvz;
	}
	input.close();
	//std::cout <<input_string<<std::endl;
	return input_string;
}

std::vector<std::string> wavelet_tree::CreateTree(const std::string& input){
    std::string leftnode="";
    std::string rightnode="";
    uint32_t string_length = input.length();
    for ( int i = 0; i < string_length; i++) {
        if ( input[i] == 'a' || input[i]=='g') {
            leftnode+=input[i];
        } else {
            rightnode+=input[i];
        }
    }
    std::vector<std::string> nodes;
    nodes.push_back(leftnode);
    nodes.push_back(rightnode);
    return nodes;
}

std::vector<bool> wavelet_tree::ConvertStringToBitVectorMain(const std::string& input_string) {
    std::vector<bool> bitvector;
    uint32_t string_length = input_string.length();
    for ( int i = 0; i < string_length; i++) {
        if ( input_string[i] == 'a' ||input_string[i]=='g') {
            bitvector.push_back(true);
        } else {
            bitvector.push_back(false);
        }
    }
    return bitvector;
}

std::vector<bool> wavelet_tree::ConvertStringToBitVectorLeft(const std::string& input_string) {
    std::vector<bool> bitvector;
    uint32_t string_length = input_string.length();
    for ( int i = 0; i < string_length; i++) {
        if ( input_string[i] == 'a') {
            bitvector.push_back(true);
        } else {
            bitvector.push_back(false);
        }
    }
    return bitvector;
}

std::vector<bool> wavelet_tree::ConvertStringToBitVectorRight(const std::string& input_string) {
    std::vector<bool> bitvector;
    uint32_t string_length = input_string.length();
    for ( int i = 0; i < string_length; i++) {
        if ( input_string[i] == 't') {
            bitvector.push_back(true);
        } else {
            bitvector.push_back(false);
        }
    }
    return bitvector;
}
