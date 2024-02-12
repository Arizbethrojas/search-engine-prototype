/*
 * pagedir.c - CS50 used in Tiny Search Engine
 *
 * see pagedir.h for more information
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
bool pagedir_validate(const char *pageDirectory);
char *pagedir_load(const char *pageDirectory, const int docID);

/**************** pagedir_init() ****************/
/* see pagedir.h for description */
bool pagedir_init(const char *pageDirectory)
{
    char *crawler = ".crawler";                                 // append this char* later in the code...
    char pathname[strlen(pageDirectory) + strlen(crawler) + 2]; // create pageDirectory/.crawler pathname
    sprintf(pathname, "%s/%s", pageDirectory, crawler);
    FILE *fp = fopen(pathname, "w"); // open the file for writing
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open this file for writing\n"); // on error of opening file, return false.
        return false;
    }
    else
    {
        fclose(fp); // close the file and return true.
        return true;
    }
    return false; // something went wrong, return false
}

/**************** pagedir_save() ****************/
/* see pagedir.h for description */
void pagedir_save(const webpage_t *page, const char *pageDirectory, const int docID)
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

/**************** pagedir_validate() ****************/
/* see pagedir.h for description */
bool pagedir_validate(const char *pageDirectory)
{                              // verify whether dir is indeed a Crawler-produced directory
    if (pageDirectory != NULL) // defensive programming
    {
        char *crawlerDir = "/.crawler";
        char *path = malloc(strlen(pageDirectory) + strlen(crawlerDir) + 2); // allocate memory
        strcpy(path, pageDirectory);                                         // append provided pageDirectory
        strcat(path, crawlerDir);                                            // append /.crawler
        if (path == NULL)
        {
            return false; // failure allocating memory
        }
        FILE *fp = fopen(path, "r");
        if (fp == NULL)
        { // this file cannot be opened for reading
            mem_free(path);
            fclose(fp);
            return false;
        }
        else
        { // this file can be opened for reading
            free(path);
            fclose(fp);
            return true;
        }
    }
    return false;
}

char *pagedir_load(const char *pageDirectory, const int docID)
{
    char digits[20];
    sprintf(digits, "%d", docID);

    char *path = malloc(strlen(pageDirectory) + sizeof(digits)); // allocating memory
    strcpy(path, pageDirectory);                                 // append provided pageDirectory
    strcpy(digits, "/");                                         // add backslash symbol
    strcat(path, digits);                                        // append
    if (path != NULL)                                            // ensure valid path
    {
        return path;
    }
    return NULL; // encountered error
}
