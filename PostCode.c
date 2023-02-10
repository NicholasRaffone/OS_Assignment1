#include <stdlib.h>
#include <stdio.h>
#include "VoteNode.h"
#include "PostCode.h"

PostCodeNode* createPostCodeNode(VoteNode* votenode){
    PostCodeNode* node = (PostCodeNode*) malloc(sizeof(PostCodeNode));
    node->next = NULL;
    node->node = votenode;
    return node;
}

PostCode* createPostCode(int code){
    PostCode* node = (PostCode*) malloc(sizeof(PostCode));
    node->code = code;
    node->num_entries = 0;
    node->head = NULL;
    node->next = NULL;
    return node;
}

void insertToPostCode(PostCode* head, VoteNode* voter){
    // get head to PostCode with zip of voter
    PostCode* headPtr = head;
    while(headPtr->code != voter->zip){
        PostCode* next = headPtr->next;
        // if we reach end but still no zipcode, just create a new one at the tail with the desired zip to enter
        if(next == NULL){
            headPtr->next = createPostCode(voter->zip);
        }
        headPtr = headPtr->next;
    }

    // traverse over postcodenodes to find the next null one
    if(headPtr->head == NULL){
        headPtr->head = createPostCodeNode(voter);
    }else{
        PostCodeNode* currNode = headPtr->head;
        while(currNode->next != NULL){
            currNode = currNode->next;
        }
        currNode->next = createPostCodeNode(voter);
    }
    headPtr->num_entries += 1;
}

PostCode* mergePostCodes(PostCode* leftList, PostCode* rightList){
    PostCode* tempStart = createPostCode(-1);
    PostCode* dummy = tempStart;
    while(leftList!=NULL && rightList!=NULL){
        if(leftList->num_entries > rightList->num_entries){
            dummy->next = leftList;
            leftList = leftList->next;
        }else{
            dummy->next = rightList;
            rightList = rightList->next;
        }
        dummy = dummy->next;
    }
    if(rightList != NULL){
        dummy->next = rightList;
    }else if(leftList!=NULL){
        dummy->next = leftList;
    }
    PostCode* realStart = tempStart->next;
    destroyPostCode(tempStart);
    return realStart;
}

PostCode* sortPostCodes(PostCode* head){
    if(head == NULL || head->next == NULL){
        return head;
    }
    PostCode* prev = NULL;
    PostCode* slow = head;
    PostCode* fast = head;

    // split the list into half
    while(fast!=NULL && fast->next!=NULL){
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    //sever the link between 1 before the slow node
    prev->next = NULL;

    //recurse 😎
    PostCode* leftList = sortPostCodes(head);
    PostCode* rightList = sortPostCodes(slow);

    return mergePostCodes(leftList, rightList);

}

void printPostCodes(PostCode* head){
    printf("\n__POST CODE CHAIN__\n");
    while(head != NULL){
        if(head->code == -1){
            continue;
        }
        PostCodeNode* currNode = head->head;
        printf("ZIP Code: %d, num entries: %d \n", head->code, head->num_entries);
        head = head->next;
    }
}

void printPostCodeByZip(PostCode* head, int zip){
    PostCode* dummy = head;
    while(dummy!=NULL && dummy->code!=zip){
        dummy = dummy->next;
    }
    if(dummy==NULL){
        printf("COULD NOT FIND VOTERS FOR ZIP: %d\n", zip);
        return;
    }
    PostCodeNode* nodeHead = dummy->head;
    printf("VOTERS FOR ZIP: %d\n", zip);
    while(nodeHead!=NULL){
        printf("PIN: %d\n", nodeHead->node->pin);
        nodeHead=nodeHead->next;
    }
}

void destroyPostCodeNode(PostCodeNode* node){
    free(node);
}

void destroyPostCode(PostCode* postcode){
    PostCodeNode* nodeHead = postcode->head;
    while(nodeHead!=NULL && nodeHead->next){
        PostCodeNode* nextNode = nodeHead->next;
        free(nodeHead);
        nodeHead = nextNode;
    }
    free(postcode);
}

void destroyPostCodeChain(PostCode* head){
    PostCode* headPtr = head;
    while(headPtr != NULL){
        PostCode* nextNode = headPtr->next;
        if(nextNode != NULL){
            destroyPostCode(nextNode);
        }
        headPtr = nextNode;
    }
}
