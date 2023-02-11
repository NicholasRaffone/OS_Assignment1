# mvote

Submitted by: **Nicholas Raffone (N17041914)**

mvote allows a user to register voters and modify their voter status, which can then be viewed through the standard output.
Behind the scenes, mvote uses [linear hashing](https://www.alexdelis.eu/M149/e_ds_linearhashing.pdf) to store the registered voters in a Hashtable, and a linked list to group the users by zipcode.


# Usage

There are multiple commands associated with mvote, which are as follows.

## Compilation and Cleanup
Use the `make` command to compile all of the files.
When done, use the `make clean` command to delete all files.

## Running mvote

mvote can be invoked in the following way: 

    ./mvote -f (csv_filename) -b {bucket_size}

All other invocations will fail.

### Commands while mvote is running

#### Lookup
    l {pin}

l looks up the hash-table for a voter with PIN: {pin}. 
If found, print the pertinent record out on the tty; otherwise, print an error indication. 

#### Insertion

    i {pin} {lname} {fname} {zip}

i inserts all information for a specific voter whose ID is {pin}, last and first names are and respectively, and she/he resides in . All inserted voters have their voting status initially set to NO. If already exists, abort and present an error message. 

#### Registration

    r {pin}

r registers the voter with ID {pin} as having already voted by changing her status to YES. If it is already marked as YES, no further action is needed and an appropriate message is displayed. 

#### Bulk Voting

    bv {fileofkeys}

bv bulk-votes for all the keys that appear in file {fileofkeys}. For each attempted vote marking, the operation has a similar behavior to that of “r ” just above. 

#### Number of Voters

    v

v present the number of people marked as having voted so far.

#### Voter Percentage

    perc

perc displays the percentage of people whose vote has been as YES over the number of poll participants who are part of the hash-table. 

#### View Voters by Zipcode

    z {zipcode}

z prints the number of all poll participants marked as having voted YES and lists one id per line. 

#### View Number of Voters

    o

o produces an output list of zip codes in decreasing order of the number of people who live in each zip code and have marked as Y(es). One zipcode and the number of voters marked as YES are displayed per line. 

#### Exit

    exit

exit terminates the program but before gracefully releasing all dynamically allocated memory.

## Design Choices

#### VoteNode
Each VoteNode contains the details of a given voter. All dynamically allocated memory is released on deletion

#### HashTable, Buckets, and BucketNodes
Each HashTable contains Buckets, which contain BucketNodes. By using [linear hashing](https://www.alexdelis.eu/M149/e_ds_linearhashing.pdf), the data for each user is efficiently stored. The bucket size is determined by a constant in the `mvote.c` file, but the number of buckets increases when there is a bucket overflow. Once there is a bucket overflow, a new bucket is added and elements are redistributed between two buckets using the `void  redistribute(HashTable* table, int  bucket_num)` function. Once the redistribution happens, the function `void rearrangeBucketNodes(HashTable* table)` is used to rearrange each bucket so that there are no NULL elements between two BucketNodes. This was included for cleanliness but adds overhead for the efficiency of the program.

#### PostCodes and PostCodeNodes
A given PostCode stores the data for all users living in a given zip code. There is a chain of PostCodeNodes that points to the users, and there also is a counter for the number of voters that live in the zip code. Once a voter's vote value is set to YES, its PostCodeNode gets added to its corresponding PostCode. Each PostCode has a pointer to the next one; the same goes for each PostCodeNode.

#### MVoteSystem
The MVoteSystem keeps track of the HashTable and a linked list of PostCodes of users who have voted. The MVoteSystem keeps track of the number of users registered and the number of users that have voted. The user can register and update the vote of a voter through the MVoteSystem. When the user decides to view all the PostCodes in decreasing order, a function is called to sort the PostCodes in decreasing order and then print. 

#### mvote
mvote initially creates an MVoteSystem with the users supplied by the -f flag with a HashTable of bucket_size supplied by the -b flag. The program reads from the CSV file and allows the user to supply the program with the commands listed above, handling for inputs with the wrong format. When mvote terminates, all dynamically allocated memory of the structures in MVoteSystem and strings are released.
