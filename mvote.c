#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VoteNode.h"
#include "PostCode.h"
#include "HashTable.h"
#include "MVoteSystem.h"
#define MAX_LINE_LENGTH 1000
#define MAX_NAME_LEN 100
#define INITIAL_NUM_BUCKETS 4

void readRecordsFromFile(MVoteSystem* system, FILE* voterfp){
    char* curr_line = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));
    char* newuserlname = (char*) malloc(MAX_NAME_LEN * sizeof(char));
    char* newuserfname = (char*) malloc(MAX_NAME_LEN * sizeof(char));
    while (fgets(curr_line, MAX_LINE_LENGTH, voterfp) != NULL) {
        int newuserzip;
        int newuserpin;
        sscanf(curr_line, "%d,%[^,],%[^,],%d", &newuserpin, newuserlname, newuserfname, &newuserzip);
        registerVoter(system, newuserpin, 0, newuserfname, newuserlname, newuserzip);
    }
    free(newuserlname);

    free(newuserfname);

    free(curr_line);
}

int main(int argc, char* argv[]){
    if(argc != 5){
        printf("ERROR: Incorrect usage of ./mvote. Correct usage: ./mvote -f {voters.csv} -b {bucket_size} \n");
        return 1;
    }

    // voter filepath set by flag -f
    FILE* voterfp = fopen(argv[2], "r");

    // set by flag -b 
    int bucket_size = atoi(argv[4]);

    if (voterfp == NULL) {
        printf("ERROR: Unable to open file: %s", argv[2]);
        return 1;
    }

    int num_buckets = INITIAL_NUM_BUCKETS;

    MVoteSystem* system = createMVoteSystem(num_buckets, bucket_size);

    readRecordsFromFile(system, voterfp);

    fclose(voterfp);

    // Infinite loop for listening to commands


    updateVotervote(system, 100108);
    updateVotervote(system, 100350);
    updateVotervote(system, 101114);
    updateVotervote(system, 101183);
    updateVotervote(system, 100953);
    updateVotervote(system, 101295);
    updateVotervote(system, 100108);

    char* userInput = (char*) malloc(MAX_LINE_LENGTH*sizeof(char));

    while(1){
        fgets(userInput, MAX_LINE_LENGTH, stdin);
        if(userInput[0] == 'l'){
            int pin;
            int num_filled = sscanf(userInput, "l %d", &pin);
            if(num_filled != 1){
                printf("Incorrect usage of l <pin>\n");
                continue;
            }
            VoteNode* voter = getVoter(system->table, pin);
            if(voter==NULL){
                printf("Could not find voter with pin: %d\n", pin);
            }else{
                printVodeNode(voter);
            }
        }else if(strcmp(userInput, "exit\n")==0){
            break;
        }else if(userInput[0] == 'i'){
            int pin;
            int zip;
            char* newuserlname = (char*) malloc(MAX_NAME_LEN * sizeof(char));
            char* newuserfname = (char*) malloc(MAX_NAME_LEN * sizeof(char));
            int num_filled = sscanf(userInput, "i %d %s %s %d", &pin, newuserfname, newuserlname, &zip);
            if(num_filled != 4){
                printf("Incorrect usage of i <pin> <fname> <lname> <zip>\n");
                continue;
            }
            int error = registerVoter(system, pin, 0, newuserfname, newuserlname, zip);
            free(newuserlname);
            free(newuserfname);
            if(error == 1){
                break;
            }
        }else if(userInput[0] == 'r'){
            int pin;
            int num_filled = sscanf(userInput, "r %d", &pin);
            if(num_filled != 1){
                printf("Incorrect usage of r <pin>\n");
                continue;
            }
            updateVotervote(system, pin);
        }else if(userInput[0] == 'v'){
            printf("Num voted so far: %d\n", system->num_registered);
        }else if(strcmp(userInput, "perc\n") == 0){
            printf("Percentage YES: %.2f%%\n", (float) system->num_voters / system->num_registered);
        }else if(userInput[0] == 'z'){
            int zip;
            int num_filled = sscanf(userInput, "z %d", &zip);
            if(num_filled != 1){
                printf("Incorrect usage of z <zip>\n");
                continue;
            }
            printPostCodeByZip(system->postcodechain, zip);
        }else if(userInput[0] == 'b' && userInput[1] == 'v'){
            FILE* votekeys;

            char* bvfilename = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));
            int num_filled = sscanf(userInput, "bv %s", bvfilename);
            if(num_filled != 1){
                printf("Incorrect usage of bv <filename>\n");
                free(bvfilename);
                continue;
            }

            votekeys = fopen(bvfilename, "r");
            if(votekeys == NULL){
                printf("Couldnt open file %s\n", bvfilename);
                free(bvfilename);
                continue;
            }
            char* curr_line = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));
            while (fgets(curr_line, MAX_LINE_LENGTH, votekeys) != NULL) {
                int userpin;
                sscanf(curr_line, "%d", &userpin);
                updateVotervote(system, userpin);
            }

            fclose(votekeys);
            free(bvfilename);

        }else if(userInput[0] == 'o'){
            printVoterZipCodes(system);
        }else{
            printf("INVALID COMMAND: %s", userInput);
        }
    }

    destroyMVoteSystem(system);
    free(userInput);
    
    return 0;
}
