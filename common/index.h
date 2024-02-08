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
 *   true if this operation is successful and false otherwise.
 *
 * Caller is responsible for:
 *   later calling indexDelete.
 */
index_t* indexNew(const int num_slots);

/**************** indexInsert ****************/
/* Insert index, given a hashtable, key, and item.
 *
 * Caller provides:
 * a valid word and docID, meaning that the word must not be NULL and the docID must be positive
 * 
 *  * We return:
 *   nothing, this method is void 
 */
void indexInsert(index_t* index, char* word, const int docID);

/**************** indexCounter ****************/
/* Set the counter value for the provided word and docID. If the counter does not exist yet, we create a new one
 *
 * Caller provides:
 * a valid word and docID, meaning that the word must not be NULL and the docID must be positive
 * 
 * We return:
 *   nothing, this method is void 
 */
void indexCounter(index_t* index, char* word, const int docID);

/**************** indexFind ****************/
/* Return the item associated with the given word.
 *
 * Caller provides:
 *   valid pointer to an index, valid string for the word.
 * We return:
 *   pointer to the item corresponding to the given word, if found;
 *   NULL if index is NULL, word is NULL, or word is not found.
 * 
 */
void* indexFind(index_t* index, const char* word);

/**************** indexWrite ****************/
/* Write the index type to the output file
 *
 * Caller provides:
 *   valid pointer to an index, 
 *   FILE open for writing,
 *   
 * We return:
 *   true if successfully written to file, false if otherwise
 */
bool indexWrite(index_t* index, FILE* fp);

/**************** indexLoad ****************/
/* Loads the index file into the index data structure
 *
 * Caller provides:
 *   valid pointer to an index, 
 *   a valid FILE,
 *   
 * We return:
 *   nothing, this method is void 
 *  
 */
void indexLoad(index_t* index, FILE* fp);

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
void indexDelete(index_t* index);

#endif // __INDEX_H
