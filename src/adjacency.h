#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <queue>
#include <ctime>

using namespace std;

struct Cycle {
    vector<pair<int,int>> cycle;
    int total_weight;
};

struct connectionStruct{
    int pre_root;
    int post_root;
    // string neuropil; needed only for filtering
    ushort weight;
};
vector<connectionStruct> readConnectionFile(string filename, string filter_neuropil);

// adjacency matrix (made by brendan lestrange and matt)
class adjMat {
    private:
        int N;
        vector<vector<pair<int,int>>> list; // stores adj list
        vector<vector<int>> mat; // stores adj matrix
        vector<vector<int>> cycles; // stores vertex values of cycles
    public:
        adjMat(vector<connectionStruct> &connections);
        int remapNodes(vector<connectionStruct> &connections);
        void makeMatrix(vector<connectionStruct> &connections);
        void makeList(vector<connectionStruct> &connections);
        void printList();
        void dfsHelper(int, int, int, vector<pair<int,int>> &, vector<bool> &, int, deque<Cycle> &);
        void findCyclesDFS(int); // records cycles of given length using DFS
        void findCyclesBFS(int); // records cycles of given length using BFS
        void findShortestPath(int, int); // finds shortest path between two nodes
        void prettyPrint();

};
