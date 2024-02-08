/*
 * TSE - CS50 indexer.c
 *
 * indexer uses outputs in the crawler directory and creates an index file with how often words occur
 *
 * Arizbeth Rojas, winter 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "webpage.h"
#include "pagedir.h"
#include "hashtable.h"
#include "file.h"
#include "index.h"
#include "word.h"

int main(const int argc, char *argv[]);
void indexBuild(char *pageDirectory, FILE* indexFile);
void indexPage(index_t *index, webpage_t *webpage, int id);
/* **************************************** */

int main(const int argc, char *argv[])
{
  // parse the command line, validate parameters,
  if (argc != 3)
  {
    fprintf(stderr, "Usage: indexer/indexer: pageDirectory indexFilename");
    exit(1);
  }
  char *pageDirectory = argv[1];
  if (pagedir_validate(pageDirectory) == false)
  {
    fprintf(stderr, "Usage: the pageDirectory must end with /.crawler");
    exit(1);
  }
  FILE *indexFile = fopen(argv[2], "w");
  if (indexFile == NULL)
  {
    fprintf(stderr, "Usage: must provide output file that is writable");
    exit(1);
  }
  else
  {
    indexBuild(pageDirectory, indexFile);
    fclose(indexFile);
  }
  return 0;
}

void indexBuild(char *pageDirectory, FILE* indexFile) // builds an in-memory index from webpage files it finds in the provided pageDirectory
{
  // initialize index modules
  index_t *index = indexNew(900);
  // loops over document ID numbers, counting from 1
  int id = 1;
  char *fileID;
  asprintf(&fileID, "/%d", id);
  // creates the document file 'pageDirectory/id'
  char *path = strcat(pageDirectory, fileID);
  FILE *fp = fopen(path, "r");
  while (fp != NULL)
  {
    // according to pagedir_save, this is the order lines are written in
    char *currURL = file_readLine(fp);
    char *depth = file_readLine(fp);
    int currDepth = atoi(depth); // casting to int type
    char *currHTML = file_readLine(fp);
    // loads a webpage from the document file 'pageDirectory/id'
    webpage_t *currPage = webpage_new(currURL, currDepth, currHTML);
    if (currPage != NULL)
    {
      indexPage(index, currPage, id); // if successful, passes the webpage and docID to indexPage
    }
    free(currURL);
    free(depth);
    free(fileID);
    free(path);
    fclose(fp);
    webpage_delete(currPage);
    id++;
    asprintf(&fileID, "/%d", id);
    path = strcat(pageDirectory, fileID);
    fp = fopen(path, "r");
  }
  free(fileID);
  free(path);
  indexWrite(index, indexFile);
  indexDelete(index);
}

void indexPage(index_t *index, webpage_t *webpage, int id)
{
  char *word;
  int position = 0;
  while (webpage_getNextWord(webpage, position) != NULL) // while you can scan a webpage document...
  {
    char *word = webpage_getNextWord(webpage, position);
    if (strlen(word) > 3) // skips trivial words (less than length 3),
    {
      normalizeWord(word);                // normalizes the word (converts to lower case),
      if (indexFind(index, word) == NULL) // looks up the word in the index, if NULL, it does not exist yet
      {
        indexInsert(index, word, id); // add its words to the index
      }
      else // this already exists, so we will increment the count of occurences of this word in this docID
      {
        indexCounter(index, word, id);
      }
      free(word);
    }
    position++; // steps through each word of the webpage,
  }
}