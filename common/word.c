/*
 * TSE - CS50 word.c
 *
 * see word.h for more information.
 *
 * Arizbeth Rojas, winter 2024
 */

#include <stdlib.h>
#include <ctype.h>
#include "word.h"

/**************** normalizeWord ****************/
/*
 * see index.h for description
 */
void normalizeWord(char *word)
{
    if (word != NULL)
    {
        for (char *i = word; i != '\0'; i++) //go through each letter until the null value
        {
            *i =tolower(*i);
        }
        return word; //this is the same word, but in lower case
    }
}