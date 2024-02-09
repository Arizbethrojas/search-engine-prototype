#testing sh file for indexer! 
#Arizbeth Rojas, winter 2024

#execute from a command line with usage syntax './indexer pageDirectory indexFilename'
#pageDirectory is the file produced by indexer
#indexFilename is the output file

#Test indexer with various invalid arguments, like no arguments
./indexer 

#one argument
./indexer ../common/data/letters

#three or more arguments
./indexer ../common/data/letters john paul george and ringo 

#invalid pageDirectory (non-existent path) 
./indexer ../data/common/letters ../data/letters.index

#invalid pageDirectory (not a crawler directory) 
./indexer ../common/data/walker ../data/walker.index

#invalid indexFile (non-existent path) 
./indexer ../common/data/letters data/nonexistant 

#invalid indexFile (read-only directory) 
./indexer ../common/data/letters ../common/data/readOnly/readOnly.index

#invalid indexFile (existing, read-only file)
./indexer ../common/data/letters ../common/data/readOnly.index

#Run indexer on a variety of pageDirectories and use indextest as one means of validating the resulting index.
./indexer ../common/data/letters ../common/data/letters
