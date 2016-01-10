#ifndef RRR_LOOKUP_TABLE_H_INCLUDED
#define RRR_LOOKUP_TABLE_H_INCLUDED
#include <vector>
#include <algorithm>
#include <string>
#include <stdint.h>

//This class generates and contains RRR Lookup Table
//Which is needed for operations Rank and Select
class RRRLookupTable {

public:

    //Returns RRR Lookup table
    std::vector<std::vector<bool> > GetLookupTable();

    //Constructor
    RRRLookupTable(uint32_t block_length);

    //Destructor
    ~RRRLookupTable();

private:

    //RRR table. It is represented as vector of vectors
    //Each vector represents all of the possible offsets for that class
    //Each offset starts at OFFSET * block_length bit of vector
	std::vector<std::vector<bool> > table_;

    //Block length
    uint32_t block_length_;

    //Converts string to bit vector
    std::vector<bool> ConvertStringToBitVector(const std::string& string_);
};

#endif // RRR_LOOKUP_TABLE_H_INCLUDED
