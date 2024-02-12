# Makefile for CS50 Tiny Search Engine
#
# Arizbeth Rojas

#creating macros/shortcuts
C = ../common
L = ../libcs50
LLIBS = $C/common.a $L/libcs50.a

#.o files required for executable indexer
OBJS = indexer.o indextest.o

#compile flags
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

#default target
all: indexer indextest

#how to build indexer
indexer: indexer.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

#these are the dependencies 
indexer.o: $L/webpage.h $L/mem.h $L/hashtable.h $L/file.h $C/pagedir.h $C/word.h $C/index.h

#how to build indextest
indextest: indextest.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

#these are the dependencies 
indextest.o: $L/hashtable.h $C/index.h 

.PHONY: test valgrind clean

#test
test: testing.sh
	bash -v testing.sh 

valgrind: indexer
	$(VALGRIND) ./indexer ../common/data/letters ../common/data/letters.index
#clean
clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f indexer
	rm -f indextest
	rm -f core
