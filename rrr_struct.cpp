#include "rrr_struct.h"
#include "rrr_lookup_table.h"
#include "rrr_block.h"
#include <iostream>

//Constructor
RRRStruct::RRRStruct() {

}

//Define structure
void RRRStruct::DefineStruct(uint32_t sequence_length) {
    //Calculate number of bits per block
    //And number of blocks per superblock
    bits_per_block = (int) (floor(log2(sequence_length))/2);
    blocks_per_superblock = (int)(floor(log2(sequence_length)));
    //std::cout << bits_per_block << " " << blocks_per_superblock << std::endl;
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
    //Get index of block
    uint32_t block_index = index / bits_per_block;
    //Get index of super block
    uint32_t super_block_index = block_index / blocks_per_superblock;
    //Get value of previous super blocks
    uint32_t sum = super_blocks[super_block_index];
    //Calculate number of blocks preceding targeted block
    //In super block
    uint8_t preceding_blocks = block_index - super_block_index * blocks_per_superblock;
    for ( int i = 0; i < preceding_blocks; i++) {
        sum += ConvertBitVectorToInt(blocks[super_block_index * blocks_per_superblock + i].GetClass());
    }
    //Get current block from lookup table
    //And calculate number of ones till targeted index
    uint8_t current_block_index = index-preceding_blocks*bits_per_block-super_block_index*blocks_per_superblock*bits_per_block;
    if ( current_block_index > 0 ) {
        std::vector<bool> result = PullBitVector(blocks[super_block_index * blocks_per_superblock + preceding_blocks]);
        sum += NumberOfOnes(result, current_block_index);
    }
    //Rank returned depends if user asked for rank of zeros or for rank of ones
    if ( value) return sum;
    return index - sum;
}

//Select for one
uint32_t RRRStruct::Select1(uint32_t n) {
    //Find index of super block with sum higher than n
    uint32_t index = 0;
    while ( super_blocks[index+1] < n) {index++;}
    uint32_t sum = super_blocks[index];
    //Set index of starting block in super block
    uint32_t block_index = blocks_per_superblock * index;
    uint8_t i = 0;
    while ( n > sum + ConvertBitVectorToInt(blocks[block_index + i].GetClass())) {
        sum += ConvertBitVectorToInt(blocks[block_index + i++].GetClass());
    }
    //Pull bit vector from lookup table
    std::vector<bool> result_vector = PullBitVector(blocks[block_index + i]);
    uint8_t inside_index = 0;
    while ( sum < n) {
        if ( result_vector[inside_index++]) {
            sum++;
        }
    }
    //Return result
    return (block_index + i)*bits_per_block + inside_index - 1;
}

//Select for zero
uint32_t RRRStruct::Select0(uint32_t n) {
    //Find index of super block with sum higher than n
    uint32_t index = 0;
    while ( ( index + 1 ) * blocks_per_superblock * bits_per_block - super_blocks[index+1] < n) {index++;}
    uint32_t sum = index * blocks_per_superblock * bits_per_block - super_blocks[index];
    //Set index of starting block in super block
    uint32_t block_index = blocks_per_superblock * index;
    uint8_t i = 0;

    while ( n > sum + bits_per_block - ConvertBitVectorToInt(blocks[block_index + i].GetClass())) {
        sum += bits_per_block - ConvertBitVectorToInt(blocks[block_index + i++].GetClass());
    }
    //Pull bit vector from lookup table
    std::vector<bool> result_vector = PullBitVector(blocks[block_index + i]);
    uint8_t inside_index = 0;
    while ( sum < n) {
        if ( !result_vector[inside_index++]) {
            sum++;
        }
    }
    //Return result
    return (block_index + i)*bits_per_block + inside_index - 1;
}

//Adds new block in RRR sequence
void RRRStruct::NewBlock(std::vector<bool> block) {
    //If block length is less than calculated block length
    //It is the last block in whole RRR structure
    //Increase it's size to calculated block length
    //By adding zeros on the end
    if ( block.size() < bits_per_block) {
        uint8_t difference = bits_per_block - block.size();
        for ( int i = 0; i < difference; i++) {
            block.push_back(false);
        }
    }
    //Start of new super block
    if ( current_block_index == 0 ) {
        //Create new super block, it's value is
        //last_super block_ones + last_super block_value
        super_blocks.push_back(current_superblock_ones);
        current_superblock_ones = 0;
        if ( super_blocks.size() > 1 ) {
            super_blocks[super_blocks.size()-1] += super_blocks[super_blocks.size()-2];
        }
    }
    //Calculate number of ones in current block
    uint8_t number_of_ones = NumberOfOnes(block);
    //Increase number of ones in current super block
    current_superblock_ones += number_of_ones;
    //Convert number of ones to vector
    std::vector<bool> number_of_ones_vector = ConvertIntToBitVector(number_of_ones);
    //Get all offsets for current class ( number of ones )
    std::vector<bool> offsets = lookup_table[number_of_ones];
    //Calculate offset for block
    uint32_t offset = 0;
    uint32_t offsetnes = offsets.size()/bits_per_block;
    for ( offset; offset < offsetnes; offset++) {
        bool same = true;
        for ( int j = 0; j < bits_per_block; j++) {
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
}

//Calculate number of ones in current block
uint8_t RRRStruct::NumberOfOnes(std::vector<bool> block) {
    uint8_t result = 0;
    for ( int i = 0; i < block.size(); i++) {
        if ( block[i]) result += 1;
    }
    return result;
}

//Calculate number of ones in current block till targeted index
uint8_t RRRStruct::NumberOfOnes(std::vector<bool> block, uint8_t index) {
    uint8_t result = 0;
    for ( int i = 0; i < index; i++) {
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

//Convert bit vector to integer
uint32_t RRRStruct::ConvertBitVectorToInt(std::vector<bool> bitvector) {
    uint32_t result = 0;
    uint32_t vector_length = bitvector.size();
    for ( int i = vector_length; i > 0; i--) {
        if ( bitvector[vector_length-i]) {
            result += pow(2, i-1);
        }
    }
    return result;
}

//Pull bit vector from lookup table
std::vector<bool> RRRStruct::PullBitVector(RRRBlock block) {
    std::vector<bool> result;
    uint32_t class_ = ConvertBitVectorToInt(block.GetClass());
    uint32_t offset_ = ConvertBitVectorToInt(block.GetOffset());
    std::vector<bool> offsets = lookup_table[class_];
    for ( int i = 0; i < bits_per_block; i++) {
        result.push_back(offsets[offset_*bits_per_block+i]);
    }
    return result;
}
