#include "wavelet_tree.h"
#include "rrr_struct.h"

Wavelet_tree::Wavelet_tree(std::string file) {
    Wavelet_tree::GetStringFromFile(file);
    std::cout << "root size: " << root.size() << std::endl;
    std::cout << "left size: " << left.size() << std::endl;
    std::cout << "right size: " << right.size() << std::endl;
    int wholeroot,remainderroot, wholeleft, remainderleft, wholeright, remainderright= 0;
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
    std::cout << "cjelobrojno dijeljenjeroot: " << wholeroot << std::endl;
    std::cout << "ostatakroot " << remainderroot << std::endl;
    //std::cout<<root_RRR.GetBitsPerBlock()<<std::endl;
    /*

    root

    */
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
     /*

    left

    */

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

     /*

    right

    */

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
    right_RRR.NewBlock(mojr);
    //RRRStruct left_RRR(5);
    //RRRStruct right_RRR(5);
    //std::cout << root_RRR.GetBitsPerBlock() << std::endl;
}

Wavelet_tree::~Wavelet_tree(){

}

std::string Wavelet_tree:: GetStringFromFile(std::string file){
    std::ifstream input(file.c_str());
	std::string input_string = "";
	char one;

    while (input.get(one)) {
            //std::cout << one << std::endl;
            if ( one=='a' || one=='g') {
                    //std::cout << "usoag" << std::endl;
                    root.push_back(true);
                if ( one=='a'){
                    //std::cout << "usoa" << std::endl;
                    left.push_back(true);
                }
                else left.push_back(false);
            }
            else {
                //std::cout << "usotc" << std::endl;
                root.push_back(false);
                if ( one=='t')
                    right.push_back(true);
                else right.push_back(false);
            }
			input_string += one;
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
    /*std::cout<<string_<<std::endl;
    std::cout<<root[0];
    std::cout<<root[1];
    std::cout<<root[2];
    std::cout<<root[3]<<std::endl;
    std::cout<<left[0];
    std::cout<<left[1];
    std::cout<<left[2];
    std::cout<<left[3]<<std::endl;
    std::cout<<right[0];
    std::cout<<right[1];
    std::cout<<right[2];
    std::cout<<right[3]<<std::endl;
	std::cout <<input_string<<std::endl;*/
	return input_string;
}
