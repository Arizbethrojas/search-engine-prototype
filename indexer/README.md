# Indexer
## Arizbeth Rojas (Arizbethrojas)

The `indexer` indexes a provided directory that is the output from `crawler.c`. 

The index format is as follows (from indexer REQUIREMENTS.md): 
*   one line per word, one word per line
*   each line provides the word and one or more (docID, count) pairs, in the format
*   word docID count [docID count]...
*   where word is a string of lower-case letters,
*   where docID is a positive non-zero integer,
*   where count is a positive non-zero integer,
*   where the word and integers are separated by spaces;
*   note the [ ] brackets and elipses ... are not part of the file *    format – we use them here to indicate the docID count occurs one or more times.


# indextest

`indextest.c` tests if `indexer.c` is working properly. 

# Compliation

run `make`, then `make test`, and finally `make clean` 

# Usage 

Expecting this input: `indexer/indexer: pageDirectory indexFilename`

# Assumptions

Valid pagedirectories end in `crawler`

# Return values 

0 if all goes correctly, 1 if an error is encountered








`pageDirectory` is the (existing) directory in which to write downloaded webpages.

`Crawler` will save each explored webpage to a file, one webpage per file, using a unique `documentID` as the file name. The first `documentID` value is 1. 

`maxDepth` is an integer in range [0..10].

`crawler` prints nothing to stdout, other than logging its progress. 

The `Crawler` shall pause at least one second between page fetches.

The `helper modules` we use are: 
*   webpage contains all the data for a given webpage, the URL and its depth 
*   bag of pages we have yet to explore
*   hashtable of URLs we've seen so far

