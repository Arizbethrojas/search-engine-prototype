# CS50 TSE
## Arizbeth Rojas (Arizbethrojas)

The assignment and Specs are in a [public repo](https://github.com/CS50DartmouthWI24/labs/tse).
Do not clone that repo; view it on GitHub.
Watch there for any commits that may represent updates to the assignment or specs.

Following the execution of `crawler.c` are errors from 18 contexts. I used GDB to debug some of these errors, but was unable to find them all. 

Crawler creates a hashtable of URLs with items that are empty strings `""`

We assume that the `hashtable` used in `crawler` will never need any more than 200 slots. 