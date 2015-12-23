#ifndef RRR_STRUCT_H_INCLUDED
#define RRR_STRUCT_H_INCLUDED

#include <vector>
#include "rrr_block.h"
#include "rrr_lookup_table.h"

class RRRStruct {

public:

    //Constructor
    RRRStruct(uint32_t block_length);

    //Destructor
    ~RRRStruct();

    //Returns number of chosen bits from beginning till the bit with that index
	uint32_t Rank(uint32_t index, bool value);

	//Returns index of n-th appearance of chosen bit
	uint32_t Select(uint32_t n, bool value);

    //Adds new block in RRR sequence
	static void NewBlock(std::vector<bool> block);

private:

    //RRR blocks in structure
    std::vector<RRRBlock> blocks;

    //RRR superblocks in structure
    std::vector<uint32_t> superBlocks;

    //RRR lookup table
	RRRLookupTable* lookupTable;

};

#endif // RRR_STRUCT_H_INCLUDED
