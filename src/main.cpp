/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * CS202 Capstone Project                                                *                                 
 * Matt Bales and Brendan LeStrange                                      *
 * Description: This program searches for cyclic neural connections in   *
 * the fruit fly brain, as well as the shortest path between two neurons *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "adjacency.h"

using namespace std;

int main(int argc, char** argv){

    vector<connectionStruct> connections = readConnectionFile("./connections_princeton.csv", "GNG");

    adjMat object(connections);

    object.makeList(connections);

    cout << "\nThe full list of neurons in region GNG has been printed to adj_list.txt in the following format:\n";
    cout << "Root Node : {neighbor, number of synapses}\n\n";

    int cycleLength = 0;
    while(cycleLength < 2){
        cout << "Please enter desired cycle length (integer > 2): ";
        cin >> cycleLength;
    }
    object.findCyclesBFS(cycleLength);
    cout << "Cycles of length " << cycleLength << " found using BFS printed to BFS_cycles.txt\n\n";
    object.findCyclesDFS(cycleLength);
    cout << "Cycles of length " << cycleLength << " found using DFS printed to DFS_cycle.txt\n\n";

    int source = -1;
    int destination = -1;
    cout << "We now find a minimal path between two neurons." << endl; 
    while(source < 0 || source > 11021 ){
        cout << "Please enter a source neuron (0-11021): ";
        cin >> source;
    }
    while(destination < 0 || destination > 11021){
        cout << "Please enter a destination neuron (0-11021): ";
        cin >> destination;
    }
    object.findShortestPath(source, destination);

    return 0;
}
