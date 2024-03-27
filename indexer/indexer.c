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
#include "mem.h"

int main(const int argc, char *argv[]);
index_t *indexBuild(char *pageDirectory);
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
  FILE *fp = fopen(argv[2], "w");
  if (fp == NULL)
  {
    fprintf(stderr, "Usage: must provide output file that is writable");
    exit(1);
  }
  else
  {
    index_t *index = indexBuild(pageDirectory);
    indexWrite(index, fp);
    indexDelete(index);
    fclose(fp);
  }
  return 0;
}

index_t *indexBuild(char *pageDirectory) // builds an in-memory index from webpage files it finds in the provided pageDirectory
{
  // initialize index modules
  index_t *index = indexNew(900); //we arbitrarily choose 900 as this value 
  // loops over document ID numbers, counting from 1
  int id = 1;
  char* path = pagedir_load(pageDirectory, id); // creates the document file 'pageDirectory/id'
  FILE *fp = fopen(path, "r");
  if (pageDirectory==NULL){
    return NULL;
  }
  while (fp != NULL) //while this is a valid file...
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
    mem_free(currURL);
    mem_free(depth);
    mem_free(path);
    fclose(fp);
    webpage_delete(currPage);
    id++;
    path = pagedir_load(pageDirectory, id);
    fp = fopen(path, "r");
  }
  mem_free(path); //no leaks 
  indexWrite(index, fp); //once the index is built, write it 
  return index; 
  indexDelete(index); //delete the index when done 
}

void indexPage(index_t *index, webpage_t *webpage, int docID)
{
  if (index != NULL && webpage != NULL) // defensive programming
  {
    int position = 0;
    char *currWord = webpage_getNextWord(webpage, &position);
    while (currWord != NULL) // while you can scan a webpage document...
    {
      if (strlen(currWord) > 3) // skips trivial words (less than length 3),
      {
        char* normalized= normalizeWord(currWord);                // normalizes the word (converts to lower case),
        void* count = indexFind(index, normalized);
        if (count == NULL) // looks up the word in the index, if NULL, it does not exist yet
        {
          counters_t* newCount = counters_new(); //create a new counter 
          counters_add(newCount, docID);
          indexInsert(index, currWord, newCount); // add its words to the index
        }
        else // this already exists, so we will increment the count of occurences of this word in this docID
        {
          counters_add(count, docID);
        }
        free(currWord);
      }
      currWord = webpage_getNextWord(webpage, &position); // steps through each word of the webpage,
    }
  }
}
