# Querier
## Arizbeth Rojas (Arizbethrojas)

The `querier`  is a standalone program that reads the index file produced by the `Indexer`, and page files produced by the `Querier`, and answers search queries submitted via stdin.

The querier format is as follows 
*   one line waiting for user input
*   one line returning the normalized user input 

The querier correctly tokenizes and returns a normalized query to the user 
There are methods to support 'and' and 'or' operators, with precedence

# Compliation

run `make`, then `make test`, and finally `make clean` 

# Usage 

Expecting this input: `./querier pageDirectory indexFilename`

# Assumptions

Valid pagedirectories end in `crawler`

# Return values 

0 if all goes correctly
