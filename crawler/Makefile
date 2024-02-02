# Makefile for CS50 Tiny Search Engine
#
# Arizbeth Rojas

#creating macros/shortcuts
C = ../common
L = ../libcs50
LLIBS = $C/common.a $L/libcs50.a

#.o files required for executable crawler
OBJS = crawler.o

#compile flags
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

#default target
all: crawler

#how to build crawler
crawler: crawler.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: test valgrind clean

test: crawler testing.sh
	bash -v testing.sh 
#>& testing.out

valgrind: testing.sh
	$(VALGRIND) ./testing.sh

#clean
clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f crawler
	rm -f core
