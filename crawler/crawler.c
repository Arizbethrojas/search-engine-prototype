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
        printf("You must provide four arguments in the form of: executable seedURL pageDirectory maxDepth");
        exit(1);
    }
    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
    {
        printf("User provided NULL arguments");
        exit(1);
    }
    *seedURL = malloc((strlen(argv[1]) + 1) * sizeof(char));
    if (*seedURL != NULL)
    {
        strcpy(*seedURL, argv[1]);
    }
    *pageDirectory = malloc((strlen(argv[2]) + 1) * sizeof(char));
    if (*pageDirectory != NULL)
    {
        strcpy(*pageDirectory, argv[2]);
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
    free(standardURL); // according to webpage.h I am repsonsible for freeing this
    if (pagedir_init(*pageDirectory) == false)
    {
        fprintf(stderr, "could not open file\n");
        exit(1);
    }
    else
    {
        pagedir_init(*pageDirectory);
    }
}

static void crawl(char *seedURL, char *pageDirectory, const int maxDepth)
{
    hashtable_t *pagesSeen = hashtable_new(200);
    char *initialURL = malloc(strlen(seedURL) + 1);
    strcpy(initialURL, seedURL);
    hashtable_insert(pagesSeen, initialURL, "");
    bag_t *pagesLeft = bag_new(); // these are actually the pages left to crawl
    webpage_t *firstPage = webpage_new(initialURL, 0, NULL);
    // thisPage = webpage_new(initialURL, maxDepth, NULL);
    // pass it in as depth 0
    bag_insert(pagesLeft, firstPage);
    int docID = 1;
    webpage_t *currPage = bag_extract(pagesLeft);
    while (currPage != NULL)
    {
        // webpage_t* currPage = bag_extract(pagesLeft);
        bool fetchedPage = webpage_fetch(currPage); // does it automatically stop for a sec or do i need to build that in?
        //docID = docID + 1;
        // confused about what to check here?
        if (fetchedPage == true)
        {
            printf("fetched: %s\n", webpage_getURL(currPage));
            pagedir_save(currPage, pageDirectory, docID);
            if (webpage_getDepth(currPage) < maxDepth) // should this be less than or equal to?
            {
                printf("scanning: %s\n", webpage_getURL(currPage));
                pageScan(currPage, pagesLeft, pagesSeen);
            }
            docID++; // increment the ID
        }
        
        // printf("found: %s\n", webpage_getURL(currPage));
        // printf("added: %s\n", webpage_getURL(currPage));
        webpage_delete(currPage);
        currPage = bag_extract(pagesLeft);
    }
    hashtable_delete(pagesSeen, NULL); // what goes in here?
    // make an internal delete program to delete strings // give it null as item
    bag_delete(pagesLeft, NULL); // is this NULL too? for webpage_delete
}

static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen)
{
    int pos = 0;
    char *nextURL = webpage_getNextURL(page, &pos); // pos is incremented within webpage_getNextURL
    while (nextURL != NULL)
    { // while there is another URL on the page
        char *standardURL = normalizeURL(nextURL);
        if (isInternalURL(standardURL) == true)
        { // if that URL is internal...
            mem_free(nextURL);
            int newDepth = webpage_getDepth(page) + 1;
            if (hashtable_insert(pagesSeen, nextURL, "") == true)
            {
                webpage_t *webpage = webpage_new(standardURL, newDepth, NULL); // create a webpage for that URL
                bag_insert(pagesToCrawl, webpage);
                printf("found: %s\n", webpage_getURL(webpage));
                printf("added: %s\n", webpage_getURL(webpage));
            }
            else
            {
                // this is a duplicate URL that we have already visited
                fprintf(stdout, "%s is a duplicate URL that we have already visited\n", nextURL);
            }
        }
        else
        {
            // this is not an internal URL
            fprintf(stdout, "%s is an external URL\n", nextURL);
            // free(nextURL);//do i free here? do i free in both places?
        }
        nextURL = webpage_getNextURL(page, &pos);
    }
}
