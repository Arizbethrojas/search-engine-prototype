/*
 * TSE - CS50 indexer.c
 *
 * indextest.c is a program to test indexer.c
 *
 * Arizbeth Rojas, winter 2024
 */

#include <stdlib.h>
#include <stdio.h>
#include "index.h"

int main(int argc, const char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: indexer/indexer: oldIndexFilename newIndexFilename");
        return 1;
    }
    char* oldIndexFilename = argv[1];
    char* newIndexFilename = argv[2];
    FILE* fp = fopen(newIndexFilename, "w");
    index_t* index = indexNew(900);
    //load oldIndexFilename into the file we will write to
    indexLoad(oldIndexFilename, fp);
    //write into that file
    indexWrite(index, fp);
    //close the file
    fclose(fp);
    indexDelete(index);

}

// Test indexer with various invalid arguments. 2. no arguments 3. one argument 4. three or more arguments 5. invalid pageDirectory (non-existent path) 5. invalid pageDirectory (not a crawler directory) 6. invalid indexFile (non-existent path) 7. invalid indexFile (read-only directory) 7. invalid indexFile (existing, read-only file)
// Run indexer on a variety of pageDirectories and use indextest as one means of validating the resulting index.

// what is the difference between index test and testing. sh?