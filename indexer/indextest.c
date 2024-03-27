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

int main(const int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: indexer/indexer: oldIndexFilename newIndexFilename");
        return 1;
    }
    if (argv[1] != NULL && argv[2])
    {
        char *oldIndexFilename = argv[1];
        char *newIndexFilename = argv[2];
        FILE *old = fopen(oldIndexFilename, "r");
        FILE *new = fopen(newIndexFilename, "w");
        index_t *index = indexNew(900);
        // load oldIndexFilename into the file we will write to
        indexLoad(old);
        // write into that file
        indexWrite(index, new);
        // close the file
        fclose(old);
        fclose(new);
        // delete that index to avoid memory leaks
        indexDelete(index);
        return 0;
    }
    return 1; // encountered an error, return non zero
}

