#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

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
        vector<int> cycles; // stores vertex values of cycles
    public:
        adjMat(vector<connectionStruct> &connections);
        int remapNodes(vector<connectionStruct> &connections);
        void makeMatrix(vector<connectionStruct> &connections);
        void makeList(vector<connectionStruct> &connections);
        void printList();
        void findCyclesDFS(int); // 
        void findCyclesBFS(int); // 
        void prettyPrint();

};
