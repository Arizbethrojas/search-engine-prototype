/*
 * pagedir.h - header file for CS50 pagedir.c file
 *
 * pageDirectory is the (existing) directory in which to write downloaded webpages
 * marks pageDirectory as a 'directory produced by the Crawler' by creating a file named .crawler in that directory.
 * Arizbeth Rojas, Winter 2024
 */

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**************** pagedir_init ****************/
/* Create a crawler directory in pagedirectory
 *
 * Caller provides:
 *   a valid char pointer to the desired pageDirectory
 * We guarantee:
 *   a NULL directory is ignored; 
 *   there is a directory ending in '/.crawler' created 
 * Caller is responsible for:
 *   having a good time! Yay
 */
bool pagedir_init(const char *pageDirectory);

/**************** pagedir_save ****************/
/* Create a docID directory in pagedirectory
 *
 * Caller provides:
 *   a valid char pointer to the desired pageDirectory, a valid webpage pointer to page, a valid int t
 * We guarantee:
 *   a NULL directory is ignored; 
 *   there is a directory for the corresponding docID created 
 * Caller is responsible for:
 *   having a good time! Yay
 */
void pagedir_save(const webpage_t *page, const char *pageDirectory, const int docID);

/**************** pagedir_validate ****************/
/* verify whether directory is indeed a Crawler-produced directory
 *
 * Caller provides:
 *   a valid char pointer to the desired pageDirectory
 * 
 * returns true if it is a readable crawler directory and false otherwise
 */
bool pagedir_validate(char *pageDirectory);

#endif // __PAGEDIR_H
