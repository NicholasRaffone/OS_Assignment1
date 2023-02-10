all: mvote

clean:
	rm -f mvote.o votenode.o postcode.o mvotesystem.o hashtable.o mvote

mvote: mvote.o votenode.o postcode.o mvotesystem.o hashtable.o
	gcc mvote.o votenode.o postcode.o mvotesystem.o hashtable.o -o mvote

mvote.o: mvote.c MVoteSystem.h PostCode.h HashTable.h VoteNode.h
	gcc -c mvote.c

mvotesystem.o: MVoteSystem.c MVoteSystem.h PostCode.h HashTable.h
	gcc -c MVoteSystem.c

hashtable.o: HashTable.c HashTable.h VoteNode.h
	gcc -c HashTable.c

postcode.o: PostCode.c PostCode.h VoteNode.h
	gcc -c PostCode.c

votenode.o: VoteNode.c VoteNode.h
	gcc -c VoteNode.c

