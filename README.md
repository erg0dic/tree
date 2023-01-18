## Interesting CS algorithms involving hierarchical data structures
Currently the following have been implemented
1.  A Huffman encoder-decoder based on an AVL tree priority queue
2. A decision diagram using a binary tree 


###  A Huffman encoder-decoder based on an AVL tree priority queue

**Caution**: The code is not optimized and is purely the outcome of an educational endeavour.

Things that can be added to make this more challenging if I have time: 

- [] Approximate count statistics to compute huffman frequencies
- [] Optimize for memory efficieny properly?
- [] Benchmark against standard techniques
- [] ...

#### Example usage:
Copy-pasta the following command string in the terminal:

````cpp
g++ -O3 bintree.cpp -o save_out
./save_out.o
````

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/erg0dic/tree)


### Binary decision diagram 
#### Example usage
````cpp
g++ bdd.cpp -o save_out.o
./save_out.o
````
