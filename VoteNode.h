#ifndef VoteNodeDEF
#define VoteNodeDEF

    typedef struct votenode{
        int pin;
        int vote;
        int zip;
        char* fname;
        char* lname;
    } VoteNode;

    VoteNode* createVoteNode(int pin, int vote, char* fname, char* lname, int zip);
    void printVodeNode(VoteNode* node);
    void destroyVoteNode(VoteNode* node);

#endif
