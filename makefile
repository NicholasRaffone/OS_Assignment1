all: mvote

clean:
	rm -f mvote.o VoteNode.o PostCode.o MVoteSystem.o HashTable.o mvote

mvote: mvote.o VoteNode.o PostCode.o MVoteSystem.o HashTable.o
	gcc mvote.o VoteNode.o PostCode.o MVoteSystem.o HashTable.o -o mvote

mvote.o: mvote.c MVoteSystem.h PostCode.h HashTable.h VoteNode.h
	gcc -c mvote.c

MVoteSystem.o: MVoteSystem.c MVoteSystem.h PostCode.h HashTable.h
	gcc -c MVoteSystem.c

HashTable.o: HashTable.c HashTable.h VoteNode.h
	gcc -c HashTable.c

PostCode.o: PostCode.c PostCode.h VoteNode.h
	gcc -c PostCode.c

VoteNode.o: VoteNode.c VoteNode.h
	gcc -c VoteNode.c

