#ifndef RRR_BLOCK_H_INCLUDED
#define RRR_BLOCK_H_INCLUDED

#include <vector>

//This class represents one block in RRR structure
//It contains 2 elements: class ( number of ones if bit vector )
//And offset ( index of block in RRR table )
class RRRBlock {

public:

    //Constructor
    RRRBlock(std::vector<bool> ones, std::vector<bool> offset) {
        class_ = ones;
        offset_ = offset;
    }

    //Destructor
    ~RRRBlock() {};

    //Return block class
    std::vector<bool> GetClass() { return class_;}

    //Return block offset
    std::vector<bool> GetOffset() { return offset_;}

private:

    // Block class
	std::vector<bool> class_;

	// Block offset
	std::vector<bool> offset_;
};

#endif // RRR_BLOCK_H_INCLUDED
