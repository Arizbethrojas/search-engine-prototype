The crawler crawls a website and retrieves webpages starting with a specified URL. It parses the initial webpage, extracts any embedded URLs and retrieves those pages, and crawls the pages found at those URLs, but limiting itself to some threshold number of hops from the seed URL, and avoiding visiting any given URL more than once. It saves the pages, and the URL and depth for each, in files. When the crawler process is complete, the indexing of the collected documents can begin.