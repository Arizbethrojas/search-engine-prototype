/* word.h - header file for CS50 word module
 *
 * Arizbeth Rojas, Winter 2024
 */

#ifndef __WORD_H
#define __WORD_H


/**************** normalizeWord ****************/
/* 
 * Caller provides:
 *   valid char pointer
 * 
 * We do:
 *   normalize this word so that it is all lowercase 
 */
char* normalizeWord(char* word);

#endif // __WORD_H