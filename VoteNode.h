#ifndef VoteNodeDEF
#define VoteNodeDEF
    /*
    *  Struct VoteNode declaration
    *  Contains the details of a given user
    *  
    *   int pin: the user's pin
    *   int vote: the user's vote status (1 = YES, 0 = NO)
    *   int zip: the user's zipcode
    *   char* fname: the user's first name
    *   char* lname: the user's last name
    */
    typedef struct votenode{
        int pin;
        int vote;
        int zip;
        char* fname;
        char* lname;
    } VoteNode;

    /*
    *  Creates a new VoteNode
    *  @param pin the user's pin
    *  @param vote the user's vote status (1 = YES, 0 = NO)
    *  @param zip the user's zipcode
    *  @param fname the user's first name
    *  @param lname the user's last name
    *
    *  @return A pointer to the newly made VoteNode
    */
    VoteNode* createVoteNode(int pin, int vote, char* fname, char* lname, int zip);

    /*
    *  Prints the details of a VoteNode
    *  @param node The node to print 
    */
    void printVodeNode(VoteNode* node);

    /*
    *  Destroys a VoteNode and its contents
    *  @param node The node to destroy 
    */
    void destroyVoteNode(VoteNode* node);

#endif
