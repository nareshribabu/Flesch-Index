CC=gcc
CFLAGS=-Wall -std=c99 -g

fleschIndex : fleschIndex.o
	$(CC) -o fleschIndex fleschIndex.c -lm

fleschIndex.o : fleschIndex.c
	$(CC) $(CFLAGS) -c fleschIndex.c -lm

clean :
	rm fleschIndex fleschIndex.o

run :
	./fleschIndex

