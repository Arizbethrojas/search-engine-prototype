# Makefile for CS50 - tiny search engine
#   
# Arizbeth Rojas winter 2024

#modeled off of Libcs50 makefile

L = ../libcs50
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L 
CC=gcc
MAKE = make

OBJS = pagedir.o 
LIB = common.a
.PHONY: all clean 

#this is the target
all: common.a 

#creating archive
common.a: $(OBJS)
	ar cr $(LIB) $^

pagedir.o: pagedir.c pagedir.h $L/webpage.h 

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o

