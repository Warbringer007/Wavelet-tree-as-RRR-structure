#include "wavelet_tree.h"

//Constructor
Wavelet_tree::Wavelet_tree(std::string file) {
    Wavelet_tree::GetStringFromFile(file);
    Wavelet_tree::CreateRRRFromBitVector(&root_RRR, root);
    Wavelet_tree::CreateRRRFromBitVector(&left_RRR, left);
    Wavelet_tree::CreateRRRFromBitVector(&right_RRR, right);
}

Wavelet_tree::~Wavelet_tree(){

}

//Create RRR from bitvector
void Wavelet_tree::CreateRRRFromBitVector(RRRStruct* struct_, std::vector<bool> vector_){
    //whole=number of blocks in RRR structure
    int whole, remainder;
    int size_= vector_.size();
    //Calculate number of bits per block
    //And number of blocks per superblock
    struct_->DefineStruct(size_);
    uint32_t BitsPerBlock = struct_->GetBitsPerBlock();
    whole = size_ / BitsPerBlock;
    remainder = size_ % BitsPerBlock;
    //Creating RRR
    for ( int i = 0; i < whole; i++ ) {
        //First FOR is going block by block
        std::vector<bool> mine;
        for ( int j = 0; j< BitsPerBlock; j++){
            //Pushing bit by bit
            //i*BitsPerBlock = current block, j = current bit
            mine.push_back(vector_[i*BitsPerBlock+j]);
        }
        //Creating one block from pushed bits
        struct_->NewBlock(mine);
    }
    std::vector<bool> mine;
    //Pushing remainder bits
    for ( int i = 0; i < remainder; i++){
        //Same formula as before
        mine.push_back(vector_[whole*BitsPerBlock+i]);
    }
    struct_->NewBlock(mine);
}

//Rank on wavelet tree
uint32_t Wavelet_tree::Rank(char letter, uint32_t number) {
    //Example: Rank ( T,5 ) in string ATCTA, T and C are 0 in root, T is 1 in right branch
    //First we calculate rank ( 5,0 ) from root, which gives 3
    //Then we calculate rank ( 3,1 ) from right, which gives 2 ( right branch is TCT )
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
    //Example: Select ( T,2 ) in string ATCTA, T and C are 0 in root, T is 1 in right branch
    //First we calculate select1 ( 2 ) from right, which gives 3 ( right branch is TCT )
    //Then we calculate select0 ( 3 ) from root, which gives 4
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
	//Reading one char at the time until EOF
    while (input.get(one)) {
        //Ignoring descriptions
        if ( one == '>'){
            std::getline(input, description);
        }
        else if ( one!='\n') {
            //Pushing A and G to left root. pushing T and C to right root
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
    std::cout << "root size: " << root.size() << std::endl;
    //Printing root,left and right if root size is less than 100
    if ( root.size()<100){
        std::cout<<"root: "<<ConvertBitVectorToString(root)<<std::endl;
        std::cout<<"left: "<<ConvertBitVectorToString(left)<<std::endl;
        std::cout<<"right: "<<ConvertBitVectorToString(right)<<std::endl;
    }
	return input_string;
}

//Converts bitvector to string, used to print bitvectors which size is less than 100
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
