#ifndef RRR_STRUCT_H_INCLUDED
#define RRR_STRUCT_H_INCLUDED

#include <vector>
#include <math.h>
#include "rrr_block.h"
#include "rrr_lookup_table.h"

//This class represent RRR structure
//It is composed of RRR blocks and superblocks
//It also have it's own RRR lookup table
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

	//Return calculated bits per block
    uint32_t GetBitsPerBlock() { return bits_per_block;}

    //Adds new block in RRR sequence
	void NewBlock(std::vector<bool> block);

private:

    //RRR blocks in structure
    std::vector<RRRBlock> blocks;

    //RRR superblocks in structure
    std::vector<uint32_t> super_blocks;

    //RRR lookup table
	std::vector<std::vector<bool> > lookup_table;

    uint32_t bits_per_block;

    uint32_t blocks_per_superblock;

    //Index of current block
    uint8_t current_block_index;

    //Number of ones in current super block
    uint8_t current_superblock_ones;

    //Calculate number of ones in current block
    uint8_t NumberOfOnes(std::vector<bool> block);

    //Convert integer to bit vector
    std::vector<bool> ConvertIntToBitVector(uint8_t number);

    std::string ConvertBitVectorToString(std::vector<bool>& bitvector);
};

#endif // RRR_STRUCT_H_INCLUDED
