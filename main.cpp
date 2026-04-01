#include "adjacency.h"

// matt if you see this i moved your code to the adjacency.cpp : ) 

using namespace std;

int main(int argc, char** argv){

    vector<connectionStruct> connections = readConnectionFile("connections_princeton.csv", "GNG");

    adjMat object(connections);

    object.makeMatrix(connections);


    return 0;
}