#ifndef RRR_LOOKUP_TABLE_H_INCLUDED
#define RRR_LOOKUP_TABLE_H_INCLUDED
#include <vector>

//This class generates and contains RRR Lookup Table
//Which is needed for operations Rank and Select
class RRRLookupTable {

public:

    //Returns RRR Lookup table
    static std::vector<std::vector<bool> > GetLookupTable();

    //Constructor
    RRRLookupTable(uint32_t block_length);

    //Destructor
    ~RRRLookupTable();

private:

    //Generates minimum RRR Lookup table
    static void GenerateTable();

    // RRR table. First index is class, second is it's offset in table
	std::vector<std::vector<bool> > table_;
};

#endif // RRR_LOOKUP_TABLE_H_INCLUDED
