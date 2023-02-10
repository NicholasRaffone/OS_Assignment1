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

    
    BucketNode* createBucketNode(int pin, VoteNode*node);
    Bucket* createBucket(int bucket_size);
    HashTable* createHashTable(int num_buckets, int bucket_size);

    int hash_hi(int pin, HashTable* table);
    int hash_hi1(int pin, HashTable* table);
    int hash(int pin, HashTable* table);

    VoteNode* getVoter(HashTable* table, int pin);

    void addNewBucket(HashTable* table);
    int insertVoter(VoteNode* node, HashTable* table, int nextHash);
    void printTable(HashTable* table);
    void printVoter(HashTable* table, int pin);

    void redistribute(HashTable* table, int bucket_num);
    void rearrangeBucketNodes(HashTable* table);

    void destroyBucketNode(BucketNode* node);
    void destroyBucket(Bucket* bucket);
    void destroyHashtable(HashTable* table);

#endif
