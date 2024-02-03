#testing sh file for crawler! 
#Arizbeth Rojas, winter 2024

#execute from a command line with usage syntax './crawler seedURL pageDirectory maxDepth'
#seedURL is an 'internal' directory, to be used as the initial URL,
#pageDirectory is the (existing) directory in which to write downloaded webpages, and
#maxDepth is an integer in range [0..10] indicating the maximum crawl depth.

#Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.
echo "this is a bad ./crawler input" 
./crewler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../common/data/letters 1
echo " "
echo "this is a bad seedURL input" 
./crewler http://cs50tse.cs.dirtmouth.edu/tse/letters/index.html ../common/data/letters 1
echo " "
echo "this is a bad padeDir input" 
./crewler http://cs50tse.cs.dirtmouth.edu/tse/letters/index.html ../july/data/ladders 1
echo " "
echo "this is an invalid maxDepth input, too low" 
./crewler http://cs50tse.cs.dirtmouth.edu/tse/letters/index.html ../july/data/ladders -2
echo " "
echo "this is an invalid maxDepth input, too high" 
./crewler http://cs50tse.cs.dirtmouth.edu/tse/letters/index.html ../july/data/ladders 12
#Crawl a simple, closed set of cross-linked web pages like letters, at depths 0, 1, 2, or more. 
echo "This is the test for letters at depth 0" 
echo " " 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../common/data/letters 0
echo "This is the test for letters at depth 1" 
echo " " 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../common/data/letters 1
echo "This is the test for letters at depth 2" 
echo " " 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../common/data/letters 2
echo "This is the test for letters at depth 3" 
echo " " 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../common/data/letters 3
echo "This is the test for letters at depth 10" 
echo " " 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../common/data/letters 10
#Repeat with a different seed page in that same site.
echo "This is a test with a different seedURL" 
echo " " 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/H.html ../common/data/letters 1
#Point the crawler at one of our bigger playgrounds. 
echo "This is the test for toscrape at depth 0:" 
echo " " 
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../common/data/toscrape 0
echo "This is the test for wikipedia at depth 0:" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../common/data/wikipedia 0
echo "This is the test for toscrape at depth 1:" 
echo " " 
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../common/data/toscrape 1
echo "This is the test for wikipedia at depth 1:" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../common/data/wikipedia 1

