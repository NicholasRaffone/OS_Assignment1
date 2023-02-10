#include "VoteNode.h"

#ifndef POSTCODEDEF
#define POSTCODEDEF

    typedef struct postcodenode{
        struct postcodenode* next;
        VoteNode* node;
    } PostCodeNode;

    typedef struct postcode{
        int code;
        PostCodeNode* head;
        int num_entries;
        struct postcode* next;
    } PostCode;

    PostCodeNode* createPostCodeNode(VoteNode* votenode);
    PostCode* createPostCode(int code);

    void insertToPostCode(PostCode* head, VoteNode* voter);
    void printPostCodes(PostCode* head);
    void printPostCodeByZip(PostCode* head, int zip);

    PostCode* mergePostCodes(PostCode* leftList, PostCode* rightList);
    PostCode* sortPostCodes(PostCode* head);

    void destroyPostCodeNode(PostCodeNode* node);
    void destroyPostCode(PostCode* postcode);
    void destroyPostCodeChain(PostCode* head);

#endif
