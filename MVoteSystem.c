#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VoteNode.h"
#include "PostCode.h"
#include "HashTable.h"
#include "MVoteSystem.h"

MVoteSystem* createMVoteSystem(int num_buckets, int bucket_size){
    MVoteSystem* newSystem = (MVoteSystem*) malloc(sizeof(MVoteSystem));
    newSystem->table = createHashTable(num_buckets, bucket_size);
    newSystem->postcodechain = NULL;
    newSystem->num_registered = 0;
    newSystem->num_voters = 0;
    return newSystem;
}

int registerVoter(MVoteSystem* system, int pin, int vote, char* fname, char* lname, int zip){
    VoteNode* node = createVoteNode(pin, vote, fname, lname, zip);
    int error = insertVoter(node, system->table, 0);
    if(error == 1){
        return error;
    }
    system->num_registered+=1;
    return error;
}

void updateVotervote(MVoteSystem* system, int pin){
    HashTable* table = system->table;
    VoteNode* retVoter = getVoter(table, pin);
    if(retVoter != NULL){
        if(retVoter->vote != 1){
            retVoter->vote = 1;
            if(system->postcodechain == NULL){
                system->postcodechain = createPostCode(retVoter->zip);
            }
            system->num_voters = system->num_voters+1;
            insertToPostCode(system->postcodechain, retVoter);
        }else{
            printf("Voter with pin %d already set to YES \n", pin);
        }
    }else{
        printf("Could not find voter with pin: %d \n", pin);
    }
}

void printVoterZipCodes(MVoteSystem* system){
    system->postcodechain = sortPostCodes(system->postcodechain);
    printPostCodes(system->postcodechain);
}

void destroyMVoteSystem(MVoteSystem* system){
    destroyHashtable(system->table);
    if(system->postcodechain){
        destroyPostCodeChain(system->postcodechain);
    }
    free(system);
}
