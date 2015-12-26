#include "rrr_struct.h"
#include "rrr_lookup_table.h"
#include "rrr_block.h"
#include <iostream>

//Constructor
RRRStruct::RRRStruct(uint32_t sequence_length) {
    //Calculate number of bits per block
    //And number of blocks per superblock
    bits_per_block = (int) (floor(log2(sequence_length))/2);
    blocks_per_superblock = (int)(floor(log2(sequence_length)));
    std::cout << bits_per_block << " " << blocks_per_superblock << std::endl;
    //Generate and save lookup table
    RRRLookupTable table_ = RRRLookupTable(bits_per_block);
    lookup_table = table_.GetLookupTable();
    //Set starting values
    current_block_index = 0;
    current_superblock_ones = 0;
}

//Destructor
RRRStruct::~RRRStruct() {

}

//Rank
uint32_t RRRStruct::Rank(uint32_t index, bool value) {
    return 5;
}

//Select
uint32_t RRRStruct::Select(uint32_t index, bool value) {
    return 5;
}

//Adds new block in RRR sequence
void RRRStruct::NewBlock(std::vector<bool> block) {
    //If block length is less than calculated block length
    //It is the last block in whole RRR structure
    //Increase it's size to calculated block length
    //By adding zeros on the end
    if ( block.size() < bits_per_block) {
        for ( int i = 0; i < ( bits_per_block - block.size()); i++) {
            block.push_back(false);
        }
    }
    //napravi nesto
    //Start of new super block
    if ( current_block_index == 0 ) {
        std::cout << "Ovdi sam" << std::endl;
        //Create new super block, it's value is
        //last_super block_ones + last_super block_value
        super_blocks.push_back(current_superblock_ones);
        current_superblock_ones = 0;
        if ( super_blocks.size() > 1 ) {
            super_blocks[super_blocks.size()-1] += super_blocks[super_blocks.size()-2];
        }
        std::cout << super_blocks[super_blocks.size()-1] << " " << super_blocks[super_blocks.size()-2] << std::endl;
    }
    //Calculate number of ones in current block
    uint8_t number_of_ones = NumberOfOnes(block);
    //Increase number of ones in current super block
    current_superblock_ones += number_of_ones;
    //Convert number of ones to vector
    std::vector<bool> number_of_ones_vector = ConvertIntToBitVector(number_of_ones);
    //Get all offsets for current class ( number of ones )
    std::vector<bool> offsets = lookup_table[number_of_ones];
    std::cout << ConvertBitVectorToString(offsets) << " sadada" << std::endl;
    //Calculate offset for block
    uint32_t offset = 0;
    for ( offset; offset < offsets.size()/bits_per_block; offset++) {
        bool same = true;
        for ( int j = 0; j < block.size(); j++) {
            if ( offsets[bits_per_block*offset + j] != block[j]) {
                same = false;
                break;
            }
        }
        if ( same ) break;
    }
    //Convert offset to bit vector
    std::vector<bool> offset_vector = ConvertIntToBitVector(offset);
    //Create new block and save it
    RRRBlock new_block = RRRBlock(number_of_ones_vector, offset_vector);
    blocks.push_back(new_block);
    //Increase index of current block
    current_block_index += 1;
    //Reset block index to 0 if current super block is full
    if ( current_block_index == blocks_per_superblock) current_block_index = 0;
    std::cout << offset << " sadada" << std::endl;
}

//Calculate number of ones in current block
uint8_t RRRStruct::NumberOfOnes(std::vector<bool> block) {
    uint8_t result = 0;
    for ( int i = 0; i < block.size(); i++) {
        if ( block[i]) result += 1;
    }
    return result;
}

//Convert integer to bit vector
std::vector<bool> RRRStruct::ConvertIntToBitVector(uint8_t number) {
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

std::string RRRStruct::ConvertBitVectorToString(std::vector<bool>& bitvector) {
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
