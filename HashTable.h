#include "VoteNode.h"

#ifndef HASHTABLEDEF
#define HASHTABLEDEF

    typedef struct BucketNode{
        int pin;
        VoteNode* node;
    } BucketNode;

    typedef struct bucket{
        BucketNode** nodes;
        int bucket_size;
        struct bucket* next;
    } Bucket;

    typedef struct hashtable{
        Bucket** buckets;
        int num_buckets;
        int init_num_buckets;
        int round_num;
        int split_val;
        int split_max_val;
    }HashTable;

    /*
    *  Creates a BucketNode holding the pin and pointer to a node
    *
    *  @param pin The pin of the new user
    *  @param node a pointer to the new user's node
    *
    *  @return A pointer to the newly made BucketNode
    */
    BucketNode* createBucketNode(int pin, VoteNode*node);

    /*
    *  Creates a Bucket with no elements
    *
    *  @param bucket_size How many elements should fit in the bucket
    *
    *  @return A pointer to the newly made Bucket with no elements
    */
    Bucket* createBucket(int bucket_size);

    /*
    *  Creates a HashTable with empty buckets
    * 
    *  @param num_buckets Number of buckets in the HashTable
    *  @param bucket_size How many elements should fit in the bucket
    *
    *  @return A pointer to the newly made HashTable with empty buckets.
    */
    HashTable* createHashTable(int num_buckets, int bucket_size);

    /*
    *  Hashes based on h sub i, using the table's current state
    * 
    *  @param pin The pin of the user
    *  @param table The HashTable to use the hash function for
    *
    *  @return The hashed value of pin and table
    */
    int hash_hi(int pin, HashTable* table);

    /*  
    *  Hashes based on h sub i+1, using the table's current state
    * 
    *  @param pin The pin of the user
    *  @param table The HashTable to use the hash function for
    *
    *  @return The hashed value of pin and table
    */
    int hash_hi1(int pin, HashTable* table);

    /*
    *  Decides and hashes based on h sub i and sub i+1, using the table's current state
    * 
    *  @param pin The pin of the user
    *  @param table The HashTable to use the hash function for
    *
    *  @return The hashed value of pin and table
    */
    int hash(int pin, HashTable* table);

    /*
    *  Finds a VoteNode* with pin from the HashTable
    * 
    *  @param table The HashTable to find the user from
    *  @param pin The pin of the user to find
    *
    *  @return The VoteNode* of the user if found, if not, NULL
    */
    VoteNode* getVoter(HashTable* table, int pin);

    /*
    *  Adds a new bucket to the HashTable. Used when we see a page overflow
    * 
    *  @param table The HashTable to add the bucket to
    */
    void addNewBucket(HashTable* table);

    /*
    *  Inserts Voter to hash table.
    *  If nexthash == 1, use the h i+1 hashing (in the case of an overflow redistribution)
    * 
    *  @param node VoteNode* to insert
    *  @param table The HashTable to rearrange the elements
    *  @param nextHash Whether to use hi+1 or default hash
    * 
    *  @return 1 if voter cant be found or 0 if no error
    */
    int insertVoter(VoteNode* node, HashTable* table, int nextHash);

    /*
    *  Prints the contents of a HashTable bucket by bucket
    * 
    *  @param table The HashTable to print
    */
    void printTable(HashTable* table);

    /*
    *  Gets a voter from the HashTable and prints the voter if found.
    * 
    *  @param table The HashTable to print
    *  @param pin The pin of the user to print
    */
    void printVoter(HashTable* table, int pin);

    /*
    *  Redistribute elements using hash i+1 for when an overflow occurs.
    * 
    *  @param table The HashTable to redistribute the elements
    *  @param bucket_num The index of the bucket to redistribute from
    */
    void redistribute(HashTable* table, int bucket_num);

    /*
    *  N^2 2 pointer implementation to shift all elements leftwards so that there are no NULL spaces between elements.
    * 
    *  @param table The HashTable to rearrange the elements
    */
    void rearrangeBucketNodes(HashTable* table);

    /*
    *  Destroys a BucketNode
    * 
    *  @param node The BucketNode to destroy
    */
    void destroyBucketNode(BucketNode* node);

    /*
    *  Destroys a Bucket and its bucketnodes
    * 
    *  @param bucket The Bucket to destroy
    */
    void destroyBucket(Bucket* bucket);

    /*
    *  @param table The HashTable to destroy
    */
    void destroyHashtable(HashTable* table);

#endif
