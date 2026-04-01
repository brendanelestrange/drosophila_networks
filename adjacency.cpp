#include "adjacency.h"

// function for reading file defined below class functions
vector<connectionStruct> readConnectionFile(string filename, string filter_neuropil);

adjMat::adjMat(vector<connectionStruct> &connections) { 
    N = remapNodes(connections);
    mat.resize(N, vector<int>(N, 0));
}

int adjMat::remapNodes(vector<connectionStruct> &connections) {
    // get all nodes
    vector<int> nodes;
    for (int i = 0; i < connections.size(); i++) {
        
        nodes.push_back(connections[i].pre_root);
        nodes.push_back(connections[i].post_root);
    }
    // save all unique nodes with a map
    map<int, int> unique;
    int count = 0;
    for (int i = 0; i < nodes.size(); i++) {
        if (unique.contains(nodes[i])) continue;
        unique[nodes[i]] = count;
        count++;
    }

    // apply map to original connections

    for (int i = 0; i < connections.size(); i++) {
        auto it = unique.find(connections[i].pre_root);
        if (it != unique.end()) {
            connections[i].pre_root = it->second;
        }

        auto it1 = unique.find(connections[i].post_root);
        if (it1 != unique.end()) {
            connections[i].post_root = it1->second;
        }
    }

    return count;
}; 

void adjMat::makeMatrix(vector<connectionStruct> &connections) {
    
    for (int i = 0; i < connections.size(); i++) { 
        mat[connections[i].pre_root][connections[i].post_root] = connections[i].weight;
    }
    
    // here we get an INCREDIBLY sparse matrix.

}

// csv reader (made by matt bales)
vector<connectionStruct> readConnectionFile(string filename, string filter_neuropil) {
    //Open file as input filestream. Will parse using string stream
    ifstream fin(filename);
    string line;
    stringstream ss;

    //Will store parsed line in these before making struct
    string pre_root;
    string post_root;
    string neuropil;
    string weight_str;
    string nt_type;
    //Create vector of struct to store file in
    connectionStruct cs;
    vector<connectionStruct> connections_vec;

    //Get rid of header row
    getline(fin,line);
    
    //Read to end of file
    while(getline(fin, line)){

        //Make sure ss is empty and read in the line
        ss.str("");
        ss.clear();
        ss.str(line);

        //Get values for struct from ss
        getline(ss, pre_root, ',');
        getline(ss, post_root, ',');
        getline(ss, neuropil, ',');
        getline(ss, weight_str, ',');
        if (neuropil != filter_neuropil) {
            continue;
        }
        //Change values for struct variables
        cs.pre_root = stoul(pre_root);
        cs.post_root = stoul(post_root);
        // cs.neuropil = neuropil; needed only for filtering
        cs.weight = static_cast<ushort> (stoi(weight_str));

        //Add struct to return vector
        connections_vec.push_back(cs);

    }

    return connections_vec;
}
