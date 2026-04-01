#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

struct connectionStruct;
vector<connectionStruct> readConnectionFile(string filename, string filter_neuropil);

class adjMat {
    private:
        int N;
        vector<vector<int>> adj_mat;
    public:
        adjMat(int);
        void makeMatrix(string, string);
        void remapNodes(vector<connectionStruct> &connections);
        void findCycles(int);
        void prettyPrint();

};
