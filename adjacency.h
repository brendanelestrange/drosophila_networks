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

class adjMat {
    private:
        int N;
        vector<vector<int>> mat;
    public:
        adjMat(vector<connectionStruct> &connections);
        int remapNodes(vector<connectionStruct> &connections);
        void makeMatrix(vector<connectionStruct> &connections);
        void findCycles(int);
        void prettyPrint();

};
