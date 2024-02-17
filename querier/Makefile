# Makefile for CS50 Tiny Search Engine
#
# Arizbeth Rojas

#creating macros/shortcuts
C = ../common
L = ../libcs50
LLIBS = $C/common.a $L/libcs50.a

#.o files required for executable crawler
OBJS = querier.o

#compile flags
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

#default target
all: querier

#how to build crawler
querier: querier.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: test valgrind clean

#test
test: querier testing.sh
	bash -v testing.sh 

#test for memory leaks
valgrind: querier testing.sh
	$(VALGRIND) ./querier ../common/data/letters-10 ../common/data/letters-10.index

#clean
clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f querier
	rm -f core
