#include "wavelet_tree.h"

Wavelet_tree::Wavelet_tree(std::string file) {
    Wavelet_tree::GetStringFromFile(file);
    //std::cout << "root size: " << root.size() << std::endl;
    //std::cout << "left size: " << left.size() << std::endl;
    //std::cout << "right size: " << right.size() << std::endl;
    Wavelet_tree::CreateRRRFromBitVector(&root_RRR, root);
    Wavelet_tree::CreateRRRFromBitVector(&left_RRR, left);
    Wavelet_tree::CreateRRRFromBitVector(&right_RRR, right);
    /*int wholeroot,remainderroot, wholeleft, remainderleft, wholeright, remainderright= 0;
    root_RRR.DefineStruct(root.size());
    left_RRR.DefineStruct(left.size());
    right_RRR.DefineStruct(right.size());
    uint32_t BitsPerBlock = root_RRR.GetBitsPerBlock();
    uint32_t BitsPerBlockL = left_RRR.GetBitsPerBlock();
    uint32_t BitsPerBlockR = right_RRR.GetBitsPerBlock();
    std::cout<<"Bits per block: " << BitsPerBlock<<std::endl;
    wholeroot = root.size() / BitsPerBlock;
    remainderroot = root.size() % BitsPerBlock;
    wholeleft = left.size() / BitsPerBlockL;
    remainderleft = left.size() % BitsPerBlockL;
    wholeright = right.size() / BitsPerBlockR;
    remainderright = right.size() % BitsPerBlockR;
    //std::cout << "cjelobrojno dijeljenjeroot: " << wholeroot << std::endl;
    //std::cout << "ostatakroot " << remainderroot << std::endl;
    //std::cout<<root_RRR.GetBitsPerBlock()<<std::endl;


    for ( int i = 0; i < wholeroot; i++ ) {
        std::vector<bool> moj;
        for ( int j = 0; j< BitsPerBlock; j++){
            moj.push_back(root[i*BitsPerBlock+j]);
        }
        root_RRR.NewBlock(moj);
    }
    std::vector<bool> moj;
    for ( int i = 0; i < remainderroot; i++){
        moj.push_back(root[wholeroot*BitsPerBlock+i]);
    }
    root_RRR.NewBlock(moj);
    std::cout<<std::endl;


    for ( int i = 0; i < wholeleft; i++ ) {
        std::vector<bool> mojl;
        for ( int j = 0; j< BitsPerBlockL; j++){
            mojl.push_back(left[i*BitsPerBlockL+j]);
        }
        left_RRR.NewBlock(mojl);
    }
    std::vector<bool> mojl;
    for ( int i = 0; i < remainderleft; i++){
        mojl.push_back(left[wholeleft*BitsPerBlockL+i]);
    }
    left_RRR.NewBlock(mojl);
    std::cout<<std::endl;


    for ( int i = 0; i < wholeright; i++ ) {
        std::vector<bool> mojr;
        for ( int j = 0; j< BitsPerBlockR; j++){
            mojr.push_back(right[i*BitsPerBlockR+j]);
        }
        right_RRR.NewBlock(mojr);
    }
    std::vector<bool> mojr;
    for ( int i = 0; i < remainderright; i++){
        mojr.push_back(right[wholeright*BitsPerBlockR+i]);
    }
    right_RRR.NewBlock(mojr);*/
    //Wavelet_tree::Rank('a',10);
    //RRRStruct left_RRR(5);
    //RRRStruct right_RRR(5);
    //std::cout << root_RRR.GetBitsPerBlock() << std::endl;
}

Wavelet_tree::~Wavelet_tree(){

}

void Wavelet_tree::CreateRRRFromBitVector(RRRStruct* struct_, std::vector<bool> vector_){
    int whole, remainder;
    int size_= vector_.size();
    struct_->DefineStruct(size_);
    uint32_t BitsPerBlock = struct_->GetBitsPerBlock();
    whole = size_ / BitsPerBlock;
    remainder = size_ % BitsPerBlock;
    for ( int i = 0; i < whole; i++ ) {
        std::vector<bool> moj;
        for ( int j = 0; j< BitsPerBlock; j++){
            moj.push_back(vector_[i*BitsPerBlock+j]);
        }
        struct_->NewBlock(moj);
    }
    std::vector<bool> moj;
    for ( int i = 0; i < remainder; i++){
        moj.push_back(vector_[whole*BitsPerBlock+i]);
    }
    struct_->NewBlock(moj);
}
//Rank on wavelet tree
uint32_t Wavelet_tree::Rank(char letter, uint32_t number) {
    if ( letter == 'A') {
        return left_RRR.Rank(root_RRR.Rank(number,true),true);
    }
    if ( letter == 'G') {
        return left_RRR.Rank(root_RRR.Rank(number,true),false);
    }
    if ( letter == 'T') {
        return right_RRR.Rank(root_RRR.Rank(number,false),true);
    }
    if ( letter == 'C') {
        return right_RRR.Rank(root_RRR.Rank(number,false),false);
    }
}

//Select of wavelet tree
uint32_t Wavelet_tree::Select(char letter, uint32_t number) {
    if ( letter == 'A') {
        return (root_RRR.Select1(left_RRR.Select1(number)+1)+1);
    }
    if ( letter == 'G') {
        return (root_RRR.Select1(left_RRR.Select0(number)+1)+1);
    }
    if ( letter == 'T') {
        return (root_RRR.Select0(right_RRR.Select1(number)+1)+1);
    }
    if ( letter == 'C') {
        return (root_RRR.Select0(right_RRR.Select0(number)+1)+1);
    }
}

//Reads the file and converts string to bitvectors
std::string Wavelet_tree:: GetStringFromFile(std::string file){
    std::ifstream input(file.c_str());
	std::string input_string = "";
	std::string description = "";
	char one;
    while (input.get(one)) {
        if ( one == '>'){
            std::getline(input, description);
        }
        else if ( one!='\n') {
            if ( one=='A' || one=='G') {
                    root.push_back(true);
                if ( one=='A'){
                    left.push_back(true);
                }
                else left.push_back(false);
            }
            else {
                root.push_back(false);
                if ( one=='T')
                    right.push_back(true);
                else right.push_back(false);
            }
			input_string += one;
        }
	}
	input.close();
   std::string string_;
    for ( int i = 0; i < root.size(); i++) {
        if ( root[i]) {
            string_.append("1");
        } else {
            string_.append("0");
        }
    }
    //std::cout<<ConvertBitVectorToString(root)<<std::endl;
    //std::cout<<ConvertBitVectorToString(left)<<std::endl;
    //std::cout<<ConvertBitVectorToString(right)<<std::endl;
	return input_string;
}

//Converts bitvector to string
std::string Wavelet_tree::ConvertBitVectorToString(std::vector<bool> bitvector) {
    std::string string_;
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
