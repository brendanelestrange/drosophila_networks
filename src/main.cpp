#include "adjacency.h"

// matt if you see this i moved your code to the adjacency.cpp : ) 

using namespace std;

int main(int argc, char** argv){

    vector<connectionStruct> connections = readConnectionFile("../connections_princeton.csv", "GNG");

    adjMat object(connections);

    object.makeList(connections);

    // object.printList();

    // object.findShortestPath(0,4);
    
    // object.findCyclesBFS(3);

    object.findCyclesDFS(3);

    return 0;
}