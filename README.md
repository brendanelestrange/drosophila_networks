### Drosophila Networks

This project uses the connections_princeston.csv dataset from the FlyWire codex, which is a complete mapping of the Drosophila (fruit fly) brain. Please ensure that the csv file is in the directory for proper function.

Compile the program from the main directory using the make command. To run the program, enter
./run_code/graph_search from the main directory.

The program represents the fruit fly brain as a graph and finds cycles on the graph using DFS
and BFS search to illustrate the difference in performance between the two. The program also utilizes BFS to find the shortest path between two vertices. 

Follow the prompts in the terminal to conduct searches. Be advised that BFS stalls with cycles larger than 4 due to memory usage.

MUST BE IN MAIN DIRECTORY FOR PROGRAM TO WORK PROPERLY!!