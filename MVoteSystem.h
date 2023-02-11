#include "PostCode.h"
#include "HashTable.h"

#ifndef MVOTESYSTEMDEF
#define MVOTESYSTEMDEF

    /*
    *  Struct MVoteSystem declaration
    *  Contains structures related to the whole vote system
    *  
    *  HashTable* table: Hashtable associated with vote system
    *  PostCode* postcodechain: PostCodes associated with the Vote System
    *  int num_voters: Counter of number of people who voted Y
    *  int num_registered: Counter of number of people who are in the HashTable
    */
    typedef struct mvotesystem{
        HashTable* table;
        PostCode* postcodechain;
        int num_voters;
        int num_registered;
    } MVoteSystem;

    /*
    *  Creates a new MVoteSystem with a HashTable and no postcode chain
    *
    *  @param num_buckets The number of buckets in the system HashTable
    *  @param bucket_size The number of elements per bucket in the system HashTable
    *
    *  @return A pointer to the newly made MVoteSystem
    */
    MVoteSystem* createMVoteSystem(int num_buckets, int bucket_size);

    /*
    *  Registers a voter in system, initially setting vote to NO
    *
    *  @param system System to update
    *  @param pin The pin of the user to register
    *  @param fname The user's first name
    *  @param lname The user's last name
    *  @param zip The user's zip
    *
    *  @return A pointer to the newly made MVoteSystem
    */
    int registerVoter(MVoteSystem* system, int pin, int vote, char* fname, char* lname, int zip);

    /*
    *  Updates a voter with pin in system to YES
    *
    *  @param system System to update
    *  @param pin The pin of the user to set vote to YES
    *
    *  @return A pointer to the newly made MVoteSystem
    */
    void updateVotervote(MVoteSystem* system, int pin);

    /*
    *  Print the postcode chain of system in decreasing order
    *
    *  @param system System print the chain from
    */
    void printVoterZipCodes(MVoteSystem* system);

    /*
    *  Destroys the system and its HashTable and Postcode chain
    *
    *  @param system The system to destroy
    */
    void destroyMVoteSystem(MVoteSystem* system);

#endif
