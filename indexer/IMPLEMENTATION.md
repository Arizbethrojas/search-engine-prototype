# Indexer, Implementation Spec
## Arizbeth Rojas (Arizbethrojas)

In this document, we will discuss 
*   Data structures 
*   Control flow: pseudo code for overall flow, and for each of the functions
*   Detailed function prototypes and their parameters
*   Error handling and recovery
*   Testing plan 

## Data structures 

We use two three structures: a `hashtable` where its elements are `set_t` types and each item is a `counters_t` where we use the docID as a key. The size of the number of slots in hashtable is impossible to determine, so we use 900. 

## Control flow 

The indexer is implemented in one file `indexer.c` with three functions. 

### Main 

The `main` function verifies that the user inputs are valid. Once this is known, we call indexBuild, which is a method that calls indexPage within it. If no errors are encountered, the program exits 1. 

### indexBuild 

Here is the pseudo code for indexBuild provided by the class `DESIGN.md` spec:

  creates a new 'index' object
  loops over document ID numbers, counting from 1
    loads a webpage from the document file 'pageDirectory/id'
    if successful, 
      passes the webpage and docID to indexPage

### indexPage

Here is the pseudo code for indexPage provided by the class `DESIGN.md` spec:

   steps through each word of the webpage,
   skips trivial words (less than length 3),
   normalizes the word (converts to lower case),
   looks up the word in the index,
     adding the word to the index if needed
   increments the count of occurrences of this word in this docID

## Other modules

### pagedir

From the Crawler IMPLEMENTATION.md spec: 

We create a re-usable module `pagedir.c` to handles the *pagesaver*  mentioned in the design (writing a page to the pageDirectory), and marking it as a Crawler-produced pageDirectory (as required in the spec).
We chose to write this as a separate module, in `../common`, to encapsulate all the knowledge about how to initialize and validate a pageDirectory, and how to write and read page files, in one place... anticipating future use by the Indexer and Querier.

Pseudocode for `pagedir_init`:

	construct the pathname for the .crawler file in that directory
	open the file for writing; on error, return false.
	close the file and return true.


Pseudocode for `pagedir_save`:

	construct the pathname for the page file in pageDirectory
	open that file for writing
	print the URL
	print the depth
	print the contents of the webpage
	close the file

Pseudocode for `pagedir_validate`:

	validates that pageDirectory is the pathname for a directory produced by the `Crawler`
    validates that indexFilename is the pathname of a file that can be written

### libcs50

This is also from the IMPLEMENTATION.md spec for crawler and it is applicable to indexer: 

We leverage the modules of libcs50, most notably `bag`, `hashtable`, and `webpage`.
See that directory for module interfaces.
The new `webpage` module allows us to represent pages as `webpage_t` objects, to fetch a page from the Internet, and to scan a (fetched) page for URLs; in that regard, it serves as the *pagefetcher* described in the design.
Indeed, `webpage_fetch` enforces the 1-second delay for each fetch, so our crawler need not implement that part of the spec.

We also use `file.c` to read individual words and lines. 

## Function prototypes

### indexer 

Detailed descriptions of each function's interface is provided comments throughout `indexer.c` methods, so there is no neeed to repeat them here. 

```c
int main(const int argc, char *argv[]);
void indexBuild(char *pageDirectory, FILE* indexFile);
void indexPage(index_t *index, webpage_t *webpage, int id);
```

### pagedir

This is also from the IMPLEMENTATION.md spec for crawler and it is applicable to indexer: 

Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's declaration in `pagedir.h` and is not repeated here.

```c
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
bool pagedir_validate(char *pageDirectory);
```

## Error handling and recovery

All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

All code uses defensive-programming tactics to catch and exit. 

## Testing plan

This is from the DESIGN.md spec for indexer: 

*Unit testing*.  A program *indextest* will serve as a unit test for the *index* module; it reads an index file into the internal *index* data structure, then writes the index out to a new index file.

*Integration testing*.  The *indexer*, as a complete program, will be tested by building an index from a pageDirectory, and then the resulting index will be validated by running it through the *indextest* to ensure it can be loaded.

1. Test `indexer` with various invalid arguments.
	2. no arguments
	3. one argument
	4. three or more arguments
	5. invalid `pageDirectory` (non-existent path)
	5. invalid `pageDirectory` (not a crawler directory)
	6. invalid `indexFile` (non-existent path)
	7. invalid `indexFile` (read-only directory)
	7. invalid `indexFile` (existing, read-only file)
0. Run *indexer* on a variety of pageDirectories and use *indextest* as one means of validating the resulting index.
0. Run *valgrind* on both *indexer* and *indextest* to ensure no memory leaks or errors.




