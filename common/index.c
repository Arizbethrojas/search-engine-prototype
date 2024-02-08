/*
 * TSE - CS50 'index' module
 *
 * see index.h for more information.
 *
 * Arizbeth Rojas, winter 2024
 */

#include <stdlib.h>
#include "hashtable.h"
#include "counters. h"
#include "index.h"
#include "word.h"
#include "file.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
/* none */

/**************** global types ****************/
typedef struct index
{
  hashtable_t *hashtable;
  int num_slots;
} index_t;

/**************** local functions ****************/
/* not visible outside this file */

void itemDelete (void* item){
  counters_t* counter = item; 
  counters_delete(counter); //frees memory associated with given counter
}

void itemWriteCounters(void *arg, const int* key, int counter){
  //casting to avoid warnings
  FILE * fp = arg; 
  fprintf(fp, "%d %d", key, count); //space seperating key and count values
}

void itemWrite (void *arg, const char* word, void* counter){
  //casting below to avoid warnings
  FILE* fp = arg; 
  counters_t* counter2 = counter;
  fprintf(fp, "%s ", word);
  counters_iterate(counters2, fp, (*itemWriteCounters)); 
  fprintf(fp, "\n"); //new line
}

/**************** indexNew() ****************/
/* see index.h for description */
index_t *indexNew(const int num_slots)
{
  index_t *index = malloc(sizeof(index_t)); //allocating memory 
  //should i check here is index is null and then free the memory if so? 
  index->hashtable = hashtable_new(num_slots); //creates new hashtable of desired number of slots 
  index->num_slots = num_slots;
  return index;
}

/**************** indexInsert() ****************/
/* see index.h for description */
void indexInsert(index_t *index, char *word, int docID)
{
  if (index != NULL && word != NULL && docID >= 0) // defensive programming
  {
    counters_t *currCounter = hashtable_find(index->hashtable, word); // search if this counter exists already

    if (currCounter != NULL)
    {
      // if this counter already exists, increment it
      counters_add(currCounter, docID);
    }
    else
    {
      // otherwise, create new counter
      counters_t newCount = counters_new();
      counters_add(newCount, docID);
      hashtable_insert(index->hashtable, word, newCount); //insert it into the hashtable
    }
  }
}

/**************** indexCounter() ****************/
/* see index.h for description */
void indexCounter(index_t *index, const char *word, const int docID, int count)
{
  if (index != NULL && word != NULL & docID > 0) // defensive programming
  {
    counters_t findCount = hashtable_find(index->hashtable, word); //search for this counter
    if (findCount == NULL) // this counter does not exist yet
    {
      counters_t newCount = counters_new();
      counters_set(newCount, docID, count);
      hashtable_insert(index->hashtable, word, newCount);
    }
    else // this counter already exists 
    {
      counters_set(counter, docID, count);
    }
  }
}

/**************** indexFind() ****************/
/* see index.h for description */
void *indexFind(index_t *index, const char *word);
{
  if (index == NULL)
  {
    return NULL; // null index
  }
  else if (index->hashtable == NULL)
  {
    return NULL; // hashtable is empty
  }
  else
  {
    counters_t *item = hashtable_find(index->hashtable, word);
    return item;
  }
}

/**************** indexLoad() ****************/
/* see index.h for description */
void indexLoad(index_t *index, FILE *fp)
{
  if (fp != NULL && index != NULL) // defensive programming
  {
    int docID = 0; //temporary value 
    int count = 0; //temporary value
    while ((file_readWord(fp) != NULL) && (fscanf(fp, "%d %d", &docID, &count) == 2)) //while there are words and the docId and count values...
    {
      currWord = file_readWord(fp); //read the current word
      indexCounter(index, normalizeWord(currWord), docID, count); //sets counter value or creates a new counter struct if it does not already exist
      free(currWord); // should I free memory here?
    }
  }
}

/**************** indexWrite() ****************/
/* see index.h for description */
void indexWrite(index_t *index, FILE *fp)
{
  if (fp != NULL && index != NULL) // defensive programming
  {
    hashtable_iterate(index->hashtable, fp, (*itemwrite)); //writes to file
    // do i need a line of code like:    FILE *fp = fopen(pathname, "w"); to check if i can write? 
    return true;
  }
  return false; //unable to write to file 
}

/**************** indexDelete() ****************/
/* see index.h for description */
void indexDelete(index_t *index)
{
  hashtable_delete(index->hashtable, (*itemdelete)); //first free hashtable memory 
  free(index); //then, free index memory 
}