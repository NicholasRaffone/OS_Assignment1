#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "VoteNode.h"

VoteNode* createVoteNode(int pin, int vote, char* fname, char* lname, int zip){
    VoteNode* newNode = (VoteNode *) malloc(sizeof(VoteNode));
    newNode->pin = pin;
    newNode->vote = vote;
    newNode->zip = zip;
    newNode->fname = malloc(sizeof(char) * 1024);
    newNode->lname = malloc(sizeof(char) * 1024);
    strcpy(newNode->fname, fname);
    strcpy(newNode->lname, lname);
    return newNode;
}

void printVodeNode(VoteNode* node){
    char voted;
    if(node->vote==1){
        voted = 'Y';
    }else{
        voted = 'N';
    }
    printf("Voter PIN: %d Name: %s %s Zip: %d Voted: %c\n", node->pin, node->fname, node->lname, node->zip, voted);
}

void destroyVoteNode(VoteNode* node){
    free(node->fname);
    free(node->lname);
    free(node);
}
