echo "testing" 
#execute from a command line with usage syntax './crawler seedURL pageDirectory maxDepth'
#seedURL is an 'internal' directory, to be used as the initial URL,
#pageDirectory is the (existing) directory in which to write downloaded webpages, and
#maxDepth is an integer in range [0..10] indicating the maximum crawl depth.
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/letters 10