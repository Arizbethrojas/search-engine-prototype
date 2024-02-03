The `crawler` crawls a provided website and retrieves webpages starting with a specified URL, called `seedURL`. It parses the initial webpage, extracts any embedded URLs and retrieves those pages, and crawls the pages found at those URLs, but limiting itself to some threshold number of hops from the seedURL, and avoiding visiting any duplicate URL. It saves the pages, and the URL and depth for each, in files. When the crawler process is complete, the indexing of the collected documents can begin.

`pageDirectory` is the (existing) directory in which to write downloaded webpages.

`Crawler` will save each explored webpage to a file, one webpage per file, using a unique `documentID` as the file name. The first `documentID` value is 1. 

`maxDepth` is an integer in range [0..10].

`crawler` prints nothing to stdout, other than logging its progress. 

The `Crawler` shall pause at least one second between page fetches.

The `helper modules` we use are: 
*   webpage contains all the data for a given webpage, the URL and its depth 
*   bag of pages we have yet to explore
*   hashtable of URLs we've seen so far


