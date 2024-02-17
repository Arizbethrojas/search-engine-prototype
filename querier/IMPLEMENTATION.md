// it should describe implementation details specific to your implementation.

# CS50 TSE Querier
## Implementation Spec

In this document, we will focus on the following: 

-  Data structures
-  Control flow: pseudo code for overall flow, and for each of the functions
-  Detailed function prototypes and their parameters
-  Error handling and recovery
-  Testing plan

## Data structures 

We use two data structures: an 'index' produced by `indexer` and 'counters' which contain sequences of and searches, or sequences, or a record of word apperances and docIDs. or sequence and and sequence counters begin empty. 

For queriers, we assume that the longest possible word in a query is the length of the characters in the query itself. 

## Control flow

The Querier is implemented in one file `querier.c`, with five public functions and two private helper functions.

### main

The `main` function validates user input to verify that the provided directory is a `crawler` directory and that the provided file is readable. The `querier` expects input in the form of: `./querier pageDirectory indexFilename`. 

Then, from the provided file, we call `indexLoad` on it from the index module. Next, the user is prompted to enter their query and the normalized query is printed back to the screen. The query is then processed according to any and/ or operators contained in it. Finally, the memory for each word in the array of query words is freed. 

### tokenize

Given a query from the command line, extract the query words into an array. This is accomplished by looking at all the individual characters in a query. 

trach the index of the current word, which will later be compared to an int representing the index of the start of a word
    loop through character in query
      throw an error if a non alpha or space character is encountered 
      if you reach the start of a word: 
        calculate the length from current index to the start
        allocating memory for the completed word
        copy completed word into the array
        set the final character to the null terminator
        go through all indices
      increment start
    at the final word in the array, complete this process again individually 
    return the constructed array of query words 

We assume that a query will not have more than 100 words. 

### sequences

This is based on the fall 2022 Query expressions activity. I used it as the design for much of this method. However, I edited some of the processes. 

There is a boolean called fail to represent whether an and sequence is finished being built, i.e, there are no more query words to include in the and sequence.

Pseudocode:

 Loop over all words in query
      if: word == OR 
        orSequence holds the and sequences, so merge in the andSequence built so far
        because we have encountered an OR than means the and sequence built so far is finished, so set fail to false 
      if: shortCircuit 
        one word in the and sequence returned no results, so it the whole sequence will fail
      if: word == AND
        the query word following this will be included in the current and sequence 
      else: current word is a query word, not an operator word 
        find the relevant pages for this word using indexFind method from index module
        if: no pages contain this word
			Because this word was not found, the rest of the and sequence will fail 
            set fail to true
            if andSequence != NULL 
               delete andSequence
        else: pages contained this word!
            if andSequence == NULL
			   This is the first word in this and sequence, so make a new counter
            else: this is not first word in AND sequence
               find pages where all of these words occur  


### merge

Pseudocode:

	Check if either counter is NULL 
  if: or is NULL, 
    make a new counter 
  else: add the and sequence to the or sequence
    reset the and sequence because it was just saved inside the or counter
    set the and sequence to NULL

### addTheOrs

Pseudocode:
	add the counts for matching words, then store the results in the or counter

### minOfAnds

Pseudocode: 

  Loop over all documents
    store the minimum of word appearences

## Other modules

### pagedir

This is from the implementation.md file for crawler: 

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

Pseudocode for `pagedir_load`:

	construct the path for the using the docID
	Either return that path or return NULL

### index

We create a re-usable module `index.c`. We chose to write this as a separate module, in `../common`.

Pseudocode for `indexNew`:

  given a number of slots, we create a new index 

Pseudocode for `indexInsert`:

  if index is not NULL and the provided word is not NULL and counter is not NULL: 
    create a bool representing if `hashtable_insert` is successful for the parameters. 
    return that bool. 
  return false because NULL items were passed in, so it is impossible to successfully insert them

Pseudocode for `indexFind`:

  if index is NULL or its associated hashtable is NULL: 
    return NULL. 
  else: 
    using the word as the key, return the item associated with that key

Pseudocode for `indexLoad`:

  if the provided file is not NULL:
    make a new index 
    begin docID indexing at one 
    create a count for the number of times you have seen that word 
    loop through each word in the file: 
      create new counters and set their values 
      insert the index 
    close the file 
    return the index
  else: print an error message and return NULL

Pseudocode for `indexWrite`:

  if the provided file is not null and the index is not null: 
    perform hashtable iterate to write to that file

Pseudocode for `indexDelete`:

  first free hashtable memory
  then free the index memory 

### libcs50

We leverage the modules of libcs50, most notably `counters`.
The `counters` module allows us to track the docIDs and number of times we have seen a given word, the and sequences, and the or sequences. 

## Function prototypes

### querier

Detailed descriptions of each function's interface is provided as comments throughout the code in `querier.c` and is not repeated here.

```c
int main(const int argc, char *argv[]);
void merge(counters_t *and, counters_t * or);
char **tokenize(char line[], int *wordsInQuery);
counters_t *sequences(char **words, index_t *indexT);
void minOfAnds(counters_t *and, counters_t *currCounter);
void addTheOrs(counters_t * or, counters_t *and);
int min(int x, int y);
```

### pagedir

Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's declaration in `pagedir.h` and is not repeated here.

```c
bool pagedir_init(const char *pageDirectory);
void pagedir_save(const webpage_t *page, const char *pageDirectory, const int docID);
bool pagedir_validate(const char *pageDirectory);
char *pagedir_load(const char *pageDirectory, const int docID);
```

## Error handling and recovery

All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

All code uses defensive-programming tactics to catch and exit, e.g., if a function receives bad parameters.


## Testing plan

Here is an implementation-specific testing plan.

### Integration/system testing

We write a script `testing.sh` that provides several valid and invalid inputs to querier
