/* index.h - header file for CS50 index module
 *
 * An index maps words to (docID, count) pairs.  A user searches from words to find documents
 * This file includes a method to save indexes to files and to load indexes from files. 
 * 
 * Arizbeth Rojas, Winter 2024
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>
#include "counters.h"

/**************** global types ****************/
typedef struct index index_t; 

/**************** functions ****************/

/**************** indexNew ****************/
/* Create a new index.
 *
 * Caller provides:
 *   number of slots to be used, this value must be positive.
 *
 * We return:
 *   the newly created index or NULL if the num_slots provided is invalid 
 *
 * Caller is responsible for:
 *   later calling indexDelete.
 */
index_t *indexNew(const int num_slots);

/**************** indexInsert ****************/
/* Insert index, given a hashtable, key, and counter.
 *
 * Caller provides:
 * a valid word, index counter, meaning that the word must not be NULL and the count must not be negative
 * 
 *  We return:
 *   true if the index is correctly added, false otherwise 
 */
bool indexInsert(index_t *index, const char *word, void *counter);

/**************** indexFind ****************/
/* Return the count associated with the given word.
 *
 * Caller provides:
 *   valid pointer to an index, valid char pointer for the word.
 * We return:
 *   pointer to the count corresponding to the given word, if found;
 *   NULL if index is NULL, word is NULL, or word is not found.
 */
void *indexFind(index_t *index, const char *word);

/**************** indexLoad ****************/
/* Loads the index file into the index data structure
 *
 * Caller provides:
 *   a valid FILE,
 *   
 * We return:
 *   a pointer to the index
 *  
 */
index_t *indexLoad(FILE *fp);

/**************** indexWrite ****************/
/* Write the index type to the output file
 *
 * Caller provides:
 *   valid pointer to an index, 
 *   FILE open for writing,
 *   
 * We return:
 *   nothing, this method is void
 */
void indexWrite(index_t *index, FILE *fp);


/**************** indexDelete ****************/
/* Delete index and its associated memory 
 *
 * Caller provides:
 *   valid index_t pointer,
 * 
 * We do:
 *   if index==NULL, do nothing.
 *   free the index
 * 
 */
void indexDelete(index_t *index);

#endif // __INDEX_H
