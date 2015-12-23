#include "rrr_struct.h"

//Constructor
RRRStruct::RRRStruct(uint32_t sequence_length) {
    //Calculate number of bits per block
    //And number of blocks per superblock
    bits_per_block = (int) (floor(log2(string_length))/2);
    blocks_per_superblock = bits_per_block * (int)(floor(log2(string_length)));
}

// Destructor
RRRStruct::~RRRStruct() {

}
