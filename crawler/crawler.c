/*
 * crawler.c - CS50 used in Tiny Search Engine
 *
 * Arizbeth Rojas, Winter 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webpage.h"
#include "pagedir.h"
#include "hashtable.h"
#include "bag.h"
#include "mem.h"

int main(const int argc, char *argv[]);
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth);
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth);
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen);

/* **************************************** */
int main(const int argc, char *argv[])
{
    // initializing to place holder values
    char *seedURL = NULL;                                 // seedURL is the starting point
    char *pageDir = NULL;                                 // pageDir is the directory where the output will be stored
    int maxDepth = 0;                                     // depth of links to follow, value between 0 and 10 inclusive
    parseArgs(argc, argv, &seedURL, &pageDir, &maxDepth); // call parseArgs
    crawl(seedURL, pageDir, maxDepth);                    // call crawl
    return 0;                                             // exit 0
}

static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth)
{
    if (argc != 4) // expects 4 arguments
    {
        printf("You must provide four arguments in the form of: executable seedURL pageDirectory maxDepth\n");
        exit(1);
    }
    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) // defensive programming
    {
        printf("User provided NULL arguments\n");
        exit(1);
    }
    *seedURL = malloc((strlen(argv[1]) + 1) * sizeof(char));
    if (*seedURL != NULL)
    {
        strcpy(*seedURL, argv[1]); // assigning seedURL value
    }
    *pageDirectory = malloc((strlen(argv[2]) + 1) * sizeof(char));
    if (*pageDirectory != NULL)
    {
        strcpy(*pageDirectory, argv[2]); // assigning pageDirectory value
    }
    *maxDepth = atoi(argv[3]);
    if (*maxDepth < 0 || *maxDepth > 10) // maxDepth must be in specfified range
    {
        fprintf(stderr, "Max Depth must be a value between [0,10]\n");
        exit(1);
    }
    char *standardURL = normalizeURL(*seedURL); // normalize URL
    if (standardURL == NULL)
    {
        fprintf(stderr, "this is a null URL\n");
        exit(1);
    }
    if (isInternalURL(standardURL) == false) // verify it is an internal URL
    {
        fprintf(stderr, "this is not an internal URL\n");
        mem_free(standardURL);
        exit(1);
    }
    free(standardURL); // according to webpage.h, I am repsonsible for freeing this
    if (pagedir_init(*pageDirectory) == false)
    {
        fprintf(stderr, "could not open file\n");
        exit(1);
    }
    else
    {
        pagedir_init(*pageDirectory); // call pagedir_init
    }
}

static void crawl(char *seedURL, char *pageDirectory, const int maxDepth)
{
    hashtable_t *pagesSeen = hashtable_new(200); 
    char *initialURL = malloc(strlen(seedURL) + 1); //allocate memory 
    strcpy(initialURL, seedURL); //initialize
    hashtable_insert(pagesSeen, initialURL, "");
    bag_t *pagesLeft = bag_new(); // these are the pages left to crawl
    webpage_t *firstPage = webpage_new(initialURL, 0, NULL);
    bag_insert(pagesLeft, firstPage);
    int docID = 1;
    webpage_t *currPage = bag_extract(pagesLeft); //extract page
    while (currPage != NULL)
    {
        bool fetchedPage = webpage_fetch(currPage); // webpage_fetch automatically stop for one second to not overload server 
        if (fetchedPage == true)
        {
            printf("%d  Fetched: %s \n", webpage_getDepth(currPage), webpage_getURL(currPage));
            pagedir_save(currPage, pageDirectory, docID); //use pagesaver to write the webpage to the pageDirectory with a unique document ID
            if (webpage_getDepth(currPage) < maxDepth)  //if the webpage depth is < maxDepth, explore the webpage to find the links it contains:
            {
                printf("%d  Scanning: %s\n", webpage_getDepth(currPage), webpage_getURL(currPage));
                pageScan(currPage, pagesLeft, pagesSeen); //use pagescanner to parse the webpage to extract all its embedded URLs
            }
            docID++; // increment the ID
        }
        webpage_delete(currPage);
        currPage = bag_extract(pagesLeft);
    }
    hashtable_delete(pagesSeen, NULL); 
    bag_delete(pagesLeft, NULL); 
}

static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen)
{
    int pos = 0;
    char *nextURL = webpage_getNextURL(page, &pos); // pos is incremented within webpage_getNextURL
    while (nextURL != NULL)
    { // while there is another URL on the page
        char *standardURL = normalizeURL(nextURL); //normalize the URL 
        int newDepth = webpage_getDepth(page) + 1;
        if (isInternalURL(standardURL) == true)
        { // if that URL is internal...
            mem_free(nextURL);
            if (hashtable_insert(pagesSeen, nextURL, "") == true)
            {
                webpage_t *webpage = webpage_new(standardURL, newDepth, NULL); // create a webpage for that URL
                bag_insert(pagesToCrawl, webpage);
                printf("%d  Found: %s\n", webpage_getDepth(webpage), webpage_getURL(webpage));
                printf("%d  Added: %s\n", webpage_getDepth(webpage), webpage_getURL(webpage));
            }
            else
            {
                // this is a duplicate URL that we have already visited
                printf("%d  IgnDupl: %s\n", newDepth, standardURL);
            }
        }
        else
        {
            // this is not an internal URL
            printf("%d  IgnDupl: %s\n", newDepth, standardURL);
            
        }
        nextURL = webpage_getNextURL(page, &pos);
    }
}
