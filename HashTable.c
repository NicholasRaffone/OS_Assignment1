#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"

BucketNode* createBucketNode(int pin, VoteNode*node){
    BucketNode* bucketNode = (BucketNode*) malloc(sizeof(bucketNode));
    bucketNode->node = node;
    bucketNode->pin = pin;
    return bucketNode;
}

Bucket* createBucket(int bucket_size){
    Bucket* bucket = (Bucket*) malloc(sizeof(Bucket));
    bucket->bucket_size = bucket_size;
    bucket->nodes = (BucketNode**) calloc(bucket_size, sizeof(BucketNode));
    for(int i = 0; i<bucket_size; i++){
        bucket->nodes[i] = NULL;
    }
    return bucket;
}

HashTable* createHashTable(int num_buckets, int bucket_size){
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->buckets = (Bucket**) calloc(num_buckets, sizeof(Bucket));
    table->num_buckets = num_buckets;
    table->init_num_buckets = num_buckets;
    table->round_num = 0;
    table->split_val = 0;
    table->split_max_val = num_buckets;
    for(int i = 0; i<num_buckets; i++){
        table->buckets[i] = createBucket(bucket_size);
    }
    return table;
}

//HASH HELPERS

int hash_hi(int pin, HashTable* table){
    int hi = 1;
    for(int i = 0; i<table->round_num; i+=1){
        hi *= 2;
    }
    hi = pin % (hi*table->init_num_buckets);
    return hi;
}

int hash_hi1(int pin, HashTable* table){
    int hi1 = 1;
    for(int i = 0; i<(table->round_num+1); i+=1){
        hi1 *= 2;
    }
    hi1 = pin % (hi1*table->init_num_buckets);
    return hi1;
}

int hash(int pin, HashTable* table){
    // hi
    int hi = hash_hi(pin, table);

    //hi+1
    int hi1 = hash_hi1(pin, table);
    
    if(hi >= table->split_val){
        return hi;
    }

    return hi1;
}


VoteNode* getVoter(HashTable* table, int pin){
    int hashed_val = hash(pin, table);

    Bucket* head = table->buckets[hashed_val];
    int bucket_size = head->bucket_size;
    // traverse over each bucket and overflow buckets until we find the desired user.
    while(head){
        for(int i=0; i < bucket_size && head->nodes[i]!=NULL; i++){
            VoteNode* currNode = head->nodes[i]->node;
            if(currNode->pin == pin){
               return currNode;
            }
        }
        head = head->next;
    }
    return NULL;
}

void addNewBucket(HashTable* table){
    int new_size = table->num_buckets+1;
    table->buckets = (Bucket **) realloc(table->buckets, new_size*sizeof(Bucket));
    table->buckets[new_size-1] = createBucket(table->buckets[0]->bucket_size);
    table->num_buckets = new_size;
}

void redistribute(HashTable* table, int bucket_num){
    Bucket* fromBucket = table->buckets[bucket_num];
    while(fromBucket != NULL){
        for(int j=0; j<fromBucket->bucket_size; j++){
            if(fromBucket->nodes[j]!=NULL && hash_hi1(fromBucket->nodes[j]->node->pin, table)!=bucket_num){
                VoteNode* nodeToInsert = fromBucket->nodes[j]->node;
                fromBucket->nodes[j] = NULL;
                insertVoter(nodeToInsert, table, 1);
            }
        }
        fromBucket = fromBucket->next;
    }
}

void rearrangeBucketNodes(HashTable* table){
    int num_buckets = table->num_buckets;
    for(int i=0; i<num_buckets; i++){
        Bucket* head = table->buckets[i];
        int bucket_size = table->buckets[i]->bucket_size;
        if(head == NULL){
            continue;
        }
        
        while(head != NULL){
            for(int j=0; j<bucket_size; j++){
                BucketNode* left = head->nodes[j];
                BucketNode* right = left;
                Bucket* rightHead = head;
                int right_idx = j;
                if(left == NULL){
                    while(right == NULL && rightHead != NULL){
                        right_idx+=1;
                        if(right_idx == rightHead->bucket_size){
                            right_idx = 0;
                            rightHead = rightHead->next;
                            if(rightHead == NULL){
                                break;
                            }
                        }
                        right = rightHead->nodes[right_idx];
                    }
                    if(right != NULL){
                        head->nodes[j] = rightHead->nodes[right_idx];
                        rightHead->nodes[right_idx] = NULL;
                    }
                }
            }
            head = head->next;
        }
    }
}

int insertVoter(VoteNode* node, HashTable* table, int nextHash){
    int pin = node->pin;
    int hashed_val;
    if(nextHash == 0){
        hashed_val = hash(pin, table);
    }else{
        hashed_val = hash_hi1(pin, table);
    }
    Bucket* head = table->buckets[hashed_val];
    int done = 0;
    int newPage = 0;
    while(done==0){
        int bucket_size = head->bucket_size;
        for(int i = 0; i < bucket_size; i++){
            if(head->nodes[i]==NULL){
                head->nodes[i] = createBucketNode(node->pin, node);
                done = 1;
                break;
            }else{
                if(head->nodes[i]->pin == node->pin){
                    printf("ERROR: PIN ALREADY EXISTS (pin: %d)\n", node->pin);
                    return 1;
                }
            }
        }
        if(head->next == NULL && done==0){
            newPage = 1;
            head->next = createBucket(bucket_size);
        }
        head = head->next;
    }
    

    // TRIGGER: New page has appeared when adding a new element. Let's redistribute (the elements) 👍
    if(newPage == 1 && nextHash == 0){
        addNewBucket(table);

        redistribute(table, table->split_val);

        rearrangeBucketNodes(table);

        table->split_val = (1+table->split_val)%(table->split_max_val);

        // start a new round if we've reached the end
        if(table->split_val == 0){
            table->split_max_val *= 2;
            table->round_num += 1;
        }

    }

    return 0;
}

void printTable(HashTable* table){
    int num_buckets = table->num_buckets;
    for(int i=0; i<num_buckets; i++){
        Bucket* head = table->buckets[i];
        printf("bucket num: %d\n", i);
        int bucket_size = table->buckets[i]->bucket_size;
        while(head != NULL){
            for(int j=0; j<bucket_size; j++){
                if(head->nodes[j]!=NULL){
                    printf("pin: %d\n", head->nodes[j]->node->pin);
                }else{
                    printf("EMPTY\n");
                }
            }
            printf("_______\n");
            head = head->next;
        }
        printf("\n\n");
    }
}

void printVoter(HashTable* table, int pin){
    VoteNode* retVoter = getVoter(table, pin);
    if(retVoter != NULL){
        printf("Voter Found: fname: %s lname: %s pin: %d vote: %d\n", retVoter->fname, retVoter->lname, retVoter->pin, retVoter->vote);
    }else{
        printf("Could not find voter with pin: %d \n", pin);
    }
}

// DESTROYER FUNCTIONS
void destroyBucketNode(BucketNode* node){
    destroyVoteNode(node->node);
    free(node);
}

void destroyBucket(Bucket* bucket){
    int bucket_size = bucket->bucket_size;
    for(int i = 0; i<bucket_size&&bucket->nodes[i]!=NULL; i++){
        destroyBucketNode(bucket->nodes[i]);
    }
    free(bucket);
}

void destroyHashtable(HashTable* table){
    int num_buckets = table->num_buckets;
    for(int i = 0; i<num_buckets; i++){
        Bucket* bucketHead = table->buckets[i];
        int bucket_size = table->buckets[i]->bucket_size;
        while(bucketHead!=NULL){
            Bucket* nextBucket = bucketHead->next;
            destroyBucket(bucketHead);
            bucketHead = nextBucket;
        }
    }
    free(table);
}
