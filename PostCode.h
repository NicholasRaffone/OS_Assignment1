#include "VoteNode.h"

#ifndef POSTCODEDEF
#define POSTCODEDEF

    /*
    *  Struct PostCodeNode declaration
    *  Contains a pointer to the VoteNode* of this voter and then next node in the chain
    *  
    *  postcodenode* next: Next voter with the same zip
    *  VoteNode* node: Node of the related user
    */
    typedef struct postcodenode{
        struct postcodenode* next;
        VoteNode* node;
    } PostCodeNode;

    /*
    *  Struct PostCode declaration
    *  Contains a list of voters for the same zip code
    *  
    *  int code: Associate zipcode
    *  PostCodeNode* head: Beginning of the chain of voters with zipcode code
    *  int num_entries: Current number of entries for this PostCode
    *  struct postcode* next: The next PostCode with a different zip
    */
    typedef struct postcode{
        int code;
        PostCodeNode* head;
        int num_entries;
        struct postcode* next;
    } PostCode;

    /*
    *  Creates a new PostCodeNode with an associated VoteNode
    *
    *  @param votenode The associated VoteNode
    *
    *  @return A pointer to the newly made PostCodeNode
    */
    PostCodeNode* createPostCodeNode(VoteNode* votenode);

    /*
    *  Creates a new PostCode with an associated zip
    *
    *  @param code The associated zip
    *
    *  @return A pointer to the newly made PostCode
    */
    PostCode* createPostCode(int code);

    /*
    *  Insert a new voter to its respective PostCode starting at head
    *
    *  @param head The current head of the PostCode chain
    *  @param voter The voter to insert
    */
    void insertToPostCode(PostCode* head, VoteNode* voter);

    /*
    *  Prints a chain of PostCodes from head
    *
    *  @param head The starting position to print out the PostCodes from
    */
    void printPostCodes(PostCode* head);

    /*
    *  Prints the PostCodeNodes with zip
    *
    *  @param head The starting position to print out find the correct PostCode* from
    *  @param zip The zipcode of users to print
    */
    void printPostCodeByZip(PostCode* head, int zip);

    // Sort helpers

    /*
    *  Merges two PostCode chains in decreasing order
    *
    *  @param leftList The first list to merge
    *  @param rightList The second list to merge
    * 
    *  @returns The starting node of the merge lists in decreasing order
    */
    PostCode* mergePostCodes(PostCode* leftList, PostCode* rightList);

    /*
    *  Sorts a PostCode chain starting at head by using a merge sort
    *  (ie. splitting and joining recursively)
    *
    *  @param head The starting PostCode to merge from
    * 
    *  @returns The starting node of the sorted lists in decreasing order
    */
    PostCode* sortPostCodes(PostCode* head);

    /*
    *  Destroys a PostCodeNode but NOT its related VoteNode*
    *
    *  @param node The PostCodeNode to destroy
    */
    void destroyPostCodeNode(PostCodeNode* node);

    /*
    *  Destroys a PostCode and its children PostCodeNodes
    *
    *  @param postcode The PostCode to destroy
    */
    void destroyPostCode(PostCode* postcode);

    /*
    *  Destroys a chain of postcodes starting at head
    *
    *  @param head The first PostCode to destroy
    */
    void destroyPostCodeChain(PostCode* head);

#endif
