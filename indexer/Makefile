# Makefile for CS50 Tiny Search Engine
#
# Arizbeth Rojas

#creating macros/shortcuts
C = ../common
L = ../libcs50
LLIBS = $C/common.a $L/libcs50.a

#.o files required for executable indexer
OBJS = indexer.o

#compile flags
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

#default target
all: indexer indexertest

#how to build indexer
indexer: indexer.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

#how to build indexertest
indexertest: indexertest.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: test valgrind clean

#test
test: indexer indexertest
	bash -v testing.sh 

#test for memory leaks
#valgrind: testing.sh
#$(VALGRIND) ./indexer 
# where do i get the pageDirectory, from examples? //pageDirectory testing.out

#clean
clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f crawler
	rm -f core
