/*
 * TSE - CS50 querier.c
 *
 * Arizbeth Rojas, winter 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "counters.h"
#include "webpage.h"
#include "pagedir.h"
#include "hashtable.h"
#include "file.h"
#include "index.h"
#include "word.h"
#include "mem.h"

/* ******************* global functions ********************* */

int main(const int argc, char *argv[]);
void merge(counters_t *and, counters_t * or);
char **tokenize(char line[], int *wordsInQuery);
counters_t *sequences(char **words, index_t *indexT);
void minOfAnds(counters_t *and, counters_t *currCounter);
void addTheOrs(counters_t * or, counters_t *and);
int min(int x, int y);

/* **************************************** */

/**************** main function ****************/
int main(const int argc, char *argv[])
{
    if (argc != 3) // validate number of arguments
    {
        fprintf(stderr, "Usage: expecting input in the form of ./querier pageDirectory indexFilename");
        exit(1);
    }
    bool crawlerDir = pagedir_validate(argv[1]);
    if (crawlerDir == false) // this was not a crawler directory
    {
        fprintf(stderr, "Usage: Please use a crawler directory");
        exit(1);
    }
    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) // this is not a readable file
    {
        fprintf(stderr, "Usage: Please pass a readable index file");
        fclose(fp);
        exit(1);
    }
    index_t *indexT = indexLoad(fp);
    char input[1000]; // maximum query has 1000 characters
    char **query;     // array of words

    printf("Query? ");
    while (fgets(input, sizeof(input), stdin) != NULL) // checks to see if user has input query
    {
        for (int i = 0; input[i] != '\0'; i++) // loop through query characters
        {
            char chars[2];           // holds two characters at a time, representing the current character and a null terminator
            chars[0] = input[i];     // this is the curr character
            chars[1] = '\0';         // this is the null terminator
            char *currWord = chars;  // assign the array [] into a char* so that we can normalize it
            normalizeWord(currWord); // set to lowercase
            input[i] = currWord[0];  // assign it to the normalized character
        }
        int wordsInQuery;                       // tracks number of words in array of query words
        query = tokenize(input, &wordsInQuery); // constructs the array of query words
        printf("Query: ");
        for (int i = 0; i < wordsInQuery; i++)
        {
            printf("%s ", query[i]); // prints back the normalized query to the user
        }
        printf("\n"); // line break
        //counters_t *results = sequences(query, indexT);
        return 0;
    }
}

/**************** global types ****************/
typedef struct twoCounters
{
    counters_t *counterOne;
    counters_t *counterTwo;
} twoCounters_t;

/**************** local functions ****************/
/* not visible outside this file */

void orHelper(void *arg, const int key, const int count) // void* arg, const int key, const int count
{
    twoCounters_t *both = arg;
    int orCount = counters_get(both->counterTwo, key);
    int newCount = orCount + count;
    counters_set(both->counterOne, key, newCount);
}

void andHelper(void *arg, const int key, const int count)
{
    twoCounters_t *both = arg;
    int minimum = min(count, counters_get(both->counterTwo, key));
    counters_set(both->counterOne, key, minimum);
}

/* the functions below are visible outside of this file*/

char **tokenize(char line[], int *wordsInQuery)
{
    char **query = (char **)mem_malloc((strlen(line)) * sizeof(char *)); // casting here to avoid warnings
    if (query == NULL)                                                   // defensive programming
    {
        fprintf(stderr, "memory allocation failure");
        exit(1);
    }
    int index = 0;                        // index of the current word
    int start = 0;                        // represents the index of the start of a word
    for (int i = 0; line[i] != '\0'; i++) // loop through character in query
    {
        if (isalpha(line[i]) == false && isspace(line[i]) == false) // non alpha or space char error
        {
            fprintf(stderr, "Usage: Do not enter non alphabet characters or characters that are not spaces");
            exit(1);
        }
        if (isalpha(line[i])) // this is a letter
        {
            continue;
        }
        if (i > start)
        {
            int length = i - start;                                         // calculating length from current index to the start
            query[index] = (char *)mem_malloc((length + 1) * sizeof(char)); // allocating memory
            if (query[index] == NULL)                                       // defensive programming
            {
                fprintf(stderr, "memory allocation failure");
                exit(1);
            }
            strncpy(query[index], line + start, length); // copy completed word into the array
            query[index][length] = '\0';                 // set the final character to the null terminator
            index++;                                     // go through all indices
        }

        start = i + 1; // increment start
    }
    int length = strlen(line);
    if (start < length) // this must be the final word in the query
    {
        int finalLength = length - start;
        query[index] = (char *)malloc((finalLength + 1) * sizeof(char)); // allocate memory for adding this word in
        if (query[index] == NULL)
        {
            fprintf(stderr, "Error: Out of memory");
            exit(5);
        }

        strncpy(query[index], line + start, finalLength); // copy completed word into the array
        query[index][finalLength] = '\0';                 // set the final character to the null terminator
        index++;                                          // incremement because this is the last word
    }
    if ((strcmp(query[0], "and") == 0) || (strcmp(query[0], "or") == 0) || (strcmp(query[index - 1], "and") == 0) || (strcmp(query[index - 1], "or") == 0))
    {
        fprintf(stderr, "error: a query cannot end or begin in and/or\n");
        exit(1);
    }
    *wordsInQuery = index; // total number of words in query
    return query;
}

counters_t *sequences(char **words, index_t *indexT)
{
    counters_t *and = counters_new(); // this will hold the and sequences
    counters_t * or = counters_new(); // this will hold the GROUPS of and sequences
    bool fail = false;                // represents whether there exists a page with ALL words in the and sequence present in it
    for (int i = 0; i < 101; i++)     // loop over all words in the query, we assume there are at most 100
    {
        if (strcmp(words[i], "or") == 0)
        {
            merge(and, or); // add the andsequence seen so far to the orsequence
            fail = false;   // reset to false
            continue;       // now, skip to the next word. We are done working with the current word.
        }
        if (fail == true) // one of the words in the and sequence had no results, so the and sequence fails as a whole
        {
            continue; // now, skip to the next word until we reach "or" and fail is reset
        }
        if (strcmp(words[i], "and") == 0)
        {
            continue; // now, skip to the next word. We are done working with the current word.
        }
        else // the current word is a query word
        {
            void *idsAndScores = indexFind(indexT, words[i]);
            if (idsAndScores == NULL) // no pages contain currWord
            {
                fail = true;          // if "and" is the next operator, it will fail.
                counters_delete(and); // because and will fail, go ahead and delete everything in the and sequence so far
                and = NULL;
            }
            else // pages DO contain the currWord
            {
                if (and == NULL) // this is the first word in the and sequence
                {
                    and = counters_new();
                    addTheOrs(and, idsAndScores); // copy the currCounter to the current and sequence
                }
                else // this is NOT the first word in the and sequence
                {
                    minOfAnds(and, idsAndScores);
                }
            }
        }
    }
    merge(and, or); // final merge
    return or ;
}

void merge(counters_t *and, counters_t * or)
{
    if (and != NULL) // defensive programming
    {
        if (or == NULL) // have not saved any and sequences to or counter yet...
        {
            or = counters_new(); // make a new counter!!
        }
        addTheOrs(or, and);   // add the and sequence to the or sequence
        counters_delete(and); // reset the and sequence because it was just saved inside the or counter
        and = counters_new(); // set to NULL
    }
}

void addTheOrs(counters_t * or, counters_t *and)
{
    // add the counts for matching words, then store the results in the or counter
    twoCounters_t *both = mem_malloc(sizeof(twoCounters_t));
    if (both == NULL) // memory allocation failure
    {
        mem_free(both);
    }
    both->counterOne = or ;
    both->counterTwo = and;
    counters_iterate(or, both, orHelper);
}

void minOfAnds(counters_t *and, counters_t *currCounter)
{
    // for each document, take the minimum of word appearences
    twoCounters_t *two = mem_malloc(sizeof(twoCounters_t));
    if (two == NULL) // memory allocation failure
    {
        mem_free(two);
    }
    two->counterOne = and;
    two->counterTwo = currCounter;
    counters_iterate(and, two, andHelper);
}

int min(int x, int y)
{
    return (x < y) ? x : y;
}