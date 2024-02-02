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
    printf("thirteenth reason\n");
    fflush(stdout);
    char *seedURL = NULL; // initializing to place holder values
    char *pageDir = NULL;
    int maxDepth = 0;
    parseArgs(argc, argv, &seedURL, &pageDir, &maxDepth);
    crawl(seedURL, pageDir, maxDepth);
    return 0;
}

static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth)
{
    if (argc != 4) // expecting userinput in format:  executable seedURL pageDirectory maxDepth
    {
        printf("You must provide four arguments in the form of: executable seedURL pageDirectory maxDepth");
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
        exit(1);
    }
    free(standardURL); // according to webpage.h I am repsonsible for freeing this
    if (pagedir_init(*pageDirectory) == false)
    {
        printf("PLSSSSSSSSSn\n");
        fflush(stdout);
        fprintf(stderr, "could not open file\n");
        exit(1);
    }
    printf("NOOOOOO\n");
    fflush(stdout);
}

static void crawl(char *seedURL, char *pageDirectory, const int maxDepth)
{
    hashtable_t *pagesSeen = hashtable_new(200);
    char *initialURL = malloc(strlen(seedURL) + 1);
    strcpy(initialURL, seedURL);
    hashtable_insert(pagesSeen, initialURL, "");
    bag_t *pagesLeft = bag_new(); // these are actually the pages left
    webpage_t *thisURL = mem_malloc(sizeof(thisURL));
    thisURL = webpage_new(initialURL, maxDepth, NULL);
    // pass it in as depth 0
    bag_insert(pagesLeft, initialURL);
    int docID = 0;
    webpage_t *currPage = bag_extract(pagesLeft);
    while (currPage != NULL)
    {
        // webpage_t* currPage = bag_extract(pagesLeft);
        bool fetchedPage = webpage_fetch(currPage); // does it automatically stop for a sec or do i need to build that in?
        docID = docID + 1;
        // confused about what to check here?
        if (fetchedPage == true)
        {
            pagedir_save(currPage, pageDirectory, docID);
            if (webpage_getDepth(currPage) < maxDepth) // should this be less than or equal to?
            {
                pageScan(currPage, pagesLeft, pagesSeen);
            }
        }
        currPage = bag_extract(pagesLeft);
        webpage_delete(currPage);
    }
    hashtable_delete(pagesSeen, NULL); // what goes in here?
    // make an internal delete program to delete strings // give it null as item
    bag_delete(pagesLeft, webpage_delete); // is this NULL too? for webpage_delete
}

static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen)
{
    int pos = 0;
    char *nextURL = webpage_getNextURL(page, &pos); // pos is incremented within webpage_getNextURL
    while (nextURL != NULL)
    { // while there is another URL on the page
        if (isInternalURL(nextURL) == true)
        { // if that URL is internal...
            // char* index =" ";
            if (hashtable_insert(pagesSeen, nextURL, &pos) == true)
            {                                                                                                          // insert that webpage into the hashtable also should the item be NULL or should it be ""?
                webpage_t *webpage = webpage_new(webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page)); // create a webpage for that URL
                bag_insert(pagesToCrawl, webpage);                                                                     // insert it
            }
            else
            {
                // this is a duplicate URL that we have already visited
                fprintf(stdout, "%s is a duplicate URL that we have already visited", nextURL);
            }
            // free(nextURL); am i supposed to be freeing here?
        }
        else
        {
            // this is not an internal URL
            fprintf(stdout, "%s is an external URL", nextURL);
            // free(nextURL);//do i free here? do i free in both places?
        }
    }
}
