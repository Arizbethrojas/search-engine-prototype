/*
 * TSE - CS50 'index' module
 *
 * see index.h for more information.
 *
 * Arizbeth Rojas, winter 2024
 */

#include <stdlib.h>
#include "hashtable.h"
#include "counters.h"
#include "index.h"
#include "word.h"
#include "file.h"
#include "mem.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
/* none */

/**************** global types ****************/
typedef struct index
{
  hashtable_t *hashtable;
  int num_slots; // default value of 900
} index_t;

/**************** local functions ****************/
/* not visible outside this file */

/**************** itemDelete() ****************/
/* this is the method that will be passed in as a parameter for the itemDelete method later in this code */
void itemDelete(void *counter)
{
  if (counter != NULL) // defensive programming
  {
    counters_t *count = counter; // assigning counter
    counters_delete(count);      // frees memory associated with given counter
  }
}

/**************** itemWriteCounters() ****************/
/* this is the method that will be passed in as a parameter for the other local method, itemWrite */
void itemWriteCounters(void *fp, const int key, const int counter)
{
  fprintf(fp, "%d %d", key, counter); // space seperating key and count values as per the design spec
}

void itemWrite(void *fp, const char *word, void *counter)
{
  fprintf(fp, "%s ", word);                         // write the word
  counters_iterate(counter, fp, itemWriteCounters); // write the key and counter pairs
  fprintf(fp, "\n");                                // new line
}

/* the functions below are visible outside of this file*/

/**************** indexNew() ****************/
/* see index.h for description */
index_t *indexNew(const int num_slots)
{
  index_t *index = mem_malloc(sizeof(index_t)); // allocating memory
  if (index == NULL)
  {
    mem_free(index); // no memory leaks
    return NULL;     // error allocating memory
  }
  index->hashtable = hashtable_new(num_slots); // creates new hashtable of desired number of slots
  index->num_slots = num_slots;
  return index;
}

/**************** indexInsert() ****************/
/* see index.h for description */
bool indexInsert(index_t *index, const char *word, void *counter)
{
  if (index != NULL && word != NULL && counter != NULL)
  {
    bool success = hashtable_insert(index->hashtable, word, counter); // increment counter
    return success;
  }
  return false; // NULL items were passed in, so it is impossible to successfully insert them
}

/**************** indexFind() ****************/
/* see index.h for description */
void *indexFind(index_t *index, const char *word)
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
    void *counter = hashtable_find(index->hashtable, word); // word is the key, return the item associated with that key
    return counter;
  }
}

/**************** indexLoad() ****************/
/* see index.h for description */
index_t *indexLoad(FILE *fp)
{
  if (fp != NULL) // defensive programming
  {
    index_t *index = indexNew(900); // default value of 900
    int docID = 1;                  // begin indexing at one
    int count = 0;                  // initially, the word has been seen zero times
    char *currWord = file_readWord(fp);
    while (currWord != NULL && (fscanf(fp, "%d %d", &docID, &count) == 2)) // while there are words and the docId and count values...
    {
      counters_t *currCount = counters_new();  // create a new counter
      counters_set(currCount, docID, count);   // assign it to the docID and count value
      indexInsert(index, currWord, currCount); // add it to the index
      mem_free(currWord);                      // no memory leaks!
      currWord = file_readWord(fp);            // loop through the words...
    }
    fclose(fp);
    return index;
  }
  fprintf(stderr, "The file is NULL");
  return NULL;
}

/**************** indexWrite() ****************/
/* see index.h for description */
void indexWrite(index_t *index, FILE *fp)
{
  if (fp != NULL && index != NULL) // defensive programming
  {
    hashtable_iterate(index->hashtable, fp, itemWrite); // writes to file
  }
}

/**************** indexDelete() ****************/
/* see index.h for description */
void indexDelete(index_t *index)
{
  if (index == NULL) // defensive programming
  {
    mem_free(index); // there is nothing to delete here
  }
  hashtable_delete(index->hashtable, itemDelete); // first free hashtable memory
  mem_free(index);                                // then, free index memory
}