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

bool pagedir_init(const char *pageDirectory)
{
    char *crawler = "/.crawler";
    char *path = strcat(pageDirectory, crawler); //construct the pathname for the .crawler file in that directory
    if (path == NULL)
    {
        fprintf(stderr, "this is a NULL path\n");
        return false;
    }
    FILE *fp = fopen(path, "w"); // open the file for writing
    if (fp == NULL)
    {
        free(path);
        fclose(fp);
        fprintf(stderr, "Cannot open this file for writing\n"); // on error of opening file, return false.
        return false;
    }
    else
    {
        free(path);
        fclose(fp); // close the file and return true.
        return true;
    }
}

void pagedir_save(const webpage_t *page, const char *pageDirectory, const int docID)
{
    char *path = mem_malloc(strlen(pageDirectory) + 20);
    if (path == NULL)
    {
        fprintf(stderr, "this is a NULL path or a memory allocation error\n");
    }
    // consider using malloc
    if (pageDirectory != NULL)
    {
        path[0] = '\0';
        // below, I will construct the pathname for the page file in pageDirectory
        sprintf(*path, "%s/%d", pageDirectory, docID); // I will manually add the slash character
        FILE *fp = fopen(*path, "w");                  // open that file for writing
        if (fp != NULL)                                // defensive programming
        {
            fprintf(fp, "%s\n", webpage_getURL(page));   // print the URL
            fprintf(fp, "%d\n", webpage_getDepth(page)); // print the depth
            fprintf(fp, "%s\n", webpage_getHTML(page));  // print the contents of the webpage
        }
        else
        { // file can't be opened
            fprintf(stderr, "you can't open the file");
        }
        fclose(fp);
        free(path);
    }
}
