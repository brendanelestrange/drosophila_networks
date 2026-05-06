## Drosophila Networks
### By Brendan LeStrange and Matt Bales

This project uses the connections_princeston.csv dataset from the FlyWire codex <a href="https://codex.flywire.ai/"> Flywire codex</a>, which is a complete mapping of the Drosophila (fruit fly) brain. Please ensure that the csv file is in the directory for proper function.

In this program we are analyzing the Gnathal Ganglion or GNG system in the Drosophilia brain. We use the knowledge from data structures in several ways. The primary way we utilize what we learned from CS202 is by using queues and deques in our cycle searching algorithms. We use an explicit version of BFS (made by Matt Bales) and recursive version of DFS (made by Brendan LeStrange) to find cycles. Additionally Matt has implemented a shortest path method between two different nodes.


We compile the program by doing

```zsh
make
```

from the main directory and run the program using

```zsh
./run_code/graph_search 
```

In the outputs you will find the run times at the beginning of the BFS and DFS txt files to evaluate performance.

Follow the prompts in the terminal to conduct searches. Be advised that BFS stalls with cycles larger than 4 due to memory usage. Although, if you disable BFS cycle finding in main.cpp you can see that DFS can find 4 cycles. Though time complexity scales quickly.

**MUST BE IN MAIN DIRECTORY FOR PROGRAM TO WORK PROPERLY!!**

Citations:


[1]J. C. Tiernan, “An efficient search algorithm to find the elementary circuits of a graph,” Communications of The ACM, vol. 13, no. 12, pp. 722–726, Dec. 1970, doi: https://doi.org/10.1145/362814.362819.


[2]P. Schlegel et al., “Whole-brain annotation and multi-connectome cell typing of Drosophila,” Nature, vol. 634, no. 8032, pp. 139–152, Oct. 2024, doi: https://doi.org/10.1038/s41586-024-07686-5.


[3]R. Tarjan, “Depth-First Search and Linear Graph Algorithms,” SIAM Journal on Computing, vol. 1, no. 2, pp. 146–160, Jun. 1972, doi: https://doi.org/10.1137/0201010.

