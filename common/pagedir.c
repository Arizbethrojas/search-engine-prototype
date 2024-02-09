/*
 * pagedir.c - CS50 used in Tiny Search Engine
 *
 * Arizbeth Rojas, Winter 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "webpage.h"
#include "mem.h"
#include "pagedir.h"

bool pagedir_init(const char *pageDirectory);
void pagedir_save(const webpage_t *page, const char *pageDirectory, const int docID);
bool pagedir_validate(char *pageDirectory);

pagedir_load

bool pagedir_init(const char *pageDirectory)
{
    char *crawler = ".crawler";
    char pathname[strlen(pageDirectory) + strlen(crawler) + 1]; // create pageDirectory/.crawler pathname
    sprintf(pathname, "%s/%s", pageDirectory, crawler);
    // char *path = strcat(pageDirectory, crawler); //construct the pathname for the .crawler file in that directory
    if (pathname == NULL)
    {
        fprintf(stderr, "this is a NULL path\n");
        return false;
    }
    FILE *fp = fopen(pathname, "w"); // open the file for writing
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open this file for writing\n"); // on error of opening file, return false.
        return false;
    }
    else
    {
        // free(pathname);
        fclose(fp); // close the file and return true.
        return true;
    }
}

void pagedir_save(const webpage_t *page, const char *pageDirectory, const int docID) 
// pagedir_load
// load a page from a file in that directory but isnt that just this method? 
{
    char charId[20]; // the docID will go here
    sprintf(charId, "%d", docID);
    char *path = malloc(strlen(pageDirectory) + strlen(charId) + 3); // prepare memory for pageDirectory/docID
    sprintf(path, "%s/%s", pageDirectory, charId);                   // concatinate here
    FILE *fp = fopen(path, "w");                                     // open file
    if (fp != NULL)
    {
        fprintf(fp, "%s\n", webpage_getURL(page));   // print the URL
        fprintf(fp, "%d\n", webpage_getDepth(page)); // print the depth
        fprintf(fp, "%s\n", webpage_getHTML(page));  // print the HTML
        fclose(fp);                                  // close the file
        mem_free(path);
    }
    else
    {
        fprintf(stderr, "Error opening file");
        fclose(fp);     // close file
        mem_free(path); // free memory
        return;
    }
}

bool pagedir_validate(char *pageDirectory)
{ // verify whether dir is indeed a Crawler-produced directory
    char *crawlerDir = "./crawler";
    char *path = strCat(pageDirectory, crawlerDir);
    if (path == NULL)
    {
        return false; // failure allocating memory
    }
    FILE *crawlerFile = fopen(path, "r");
    if (crawlerFile == NULL)
    { // this file cannot be opened for reading
        free(path);
        fclose(crawlerFile);
        return false;
    }
    else
    { //this file can be opened for reading 
        free(path);
        fclose(crawlerFile);
        return false; 
    }
}
