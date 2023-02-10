#include "PostCode.h"
#include "HashTable.h"

#ifndef MVOTESYSTEMDEF
#define MVOTESYSTEMDEF

    typedef struct mvotesystem{
        HashTable* table;
        PostCode* postcodechain;
        int num_voters;
        int num_registered;
    } MVoteSystem;

    MVoteSystem* createMVoteSystem(int num_buckets, int bucket_size);

    void updateVotervote(MVoteSystem* system, int pin);
    int registerVoter(MVoteSystem* system, int pin, int vote, char* fname, char* lname, int zip);

    void printVoterZipCodes(MVoteSystem* system);

    void destroyMVoteSystem(MVoteSystem* system);

#endif
