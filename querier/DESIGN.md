# CS50 TSE Querier
## Design Spec

Here we focus on the core subset:

- User interface
- Inputs and outputs
- Functional decomposition into modules
- Pseudo code (plain English-like language) for logic/algorithmic flow
- Major data structures
- Testing plan

## User interface

The Querier's only interface with the user is on the command-line; it must always have three arguments.

```bash
$ ./querier pageDirectory indexFilename
```

## Inputs and outputs

*Input:* a pageDirectory produced by `crawler` and a readable index file produced by `indexer`

*Output:* a ranked output of pages corresponding with the given query. 

## Functional decomposition into modules

We anticipate the following modules or functions:

 1. *main*, which parses and validates arguments and initializes other methods in this file 
 2. *tokenize*, which creates an array of words a user's query 
 3. *sequences*, which sorts through or sequences and and sequences
 4. *merge*, which stores the and sequence in the or counter 
 4. *addTheOrs*, which adds the current totals for the provided counters
 5. *minOfAnds*, which takes the minimum of the word appearences for the two counters


And some helper modules that provide data structures:

  1. *index* of words, the number of times they appear, and a docID
  2. *counters* of and sequences, or sequences, and docID and word appearances

## Pseudo code for logic/algorithmic flow

The sequences will be built as follows:
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

## Major data structures

Helper modules provide all the data structures we need:

- *counters* of and sequences, or sequences, and docID and word appearances
- *index* of of words, the number of times they appear, and a docID


## Testing plan

The testing.sh file will provide valid and fuzz inputs 
