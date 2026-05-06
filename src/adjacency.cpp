#include "adjacency.h"


// used in DFS implementation for keeping track of cycles.


// function for reading file defined below class functions
vector<connectionStruct> readConnectionFile(string filename, string filter_neuropil);

// implemented by brendan lestrange
adjMat::adjMat(vector<connectionStruct> &connections) { 
    N = remapNodes(connections);
    // initializes the matrix, but doesn't make it
    mat.resize(N, vector<int>(N, 0));
    // initializes the list, but doesn't make it
    list.resize(N, vector<pair<int,int>>());
}

// implemented by brendan lestrange
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
        if (unique.find(nodes[i]) != unique.end()) continue;
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

// implemented by brendan lestrange
void adjMat::makeMatrix(vector<connectionStruct> &connections) {
    
    for (int i = 0; i < connections.size(); i++) { 
        mat[connections[i].pre_root][connections[i].post_root] = connections[i].weight;
    }
    
    // here we get an INCREDIBLY sparse matrix.

}

// implemented by brendan lestrange
void adjMat::makeList(vector<connectionStruct> &connections) {
    for (int i = 0; i < connections.size(); i++) {
        int source = connections[i].pre_root;
        int destination = connections[i].post_root;
        int weight = connections[i].weight;
        list[source].push_back({destination, weight});
    }
}

// prints list and also makes txt file (bc full list can't load in terminal)
// implemented by brendan lestrange
void adjMat::printList(){ 
    // also saves to txt
    ofstream file("../outputs/adj_list.txt");
    for (int i = 0; i < list.size(); i++) {
        cout << i << " : ";
        file << i << " : "; 
        for (int j = 0; j < list[i].size(); j++) {
            cout << "{"<<list[i][j].first<<", "<<list[i][j].second<<"} ";
            file << "{"<<list[i][j].first<<", "<<list[i][j].second<<"} ";
        }
        cout << endl;
        file << endl;
    }
    file.close();
}


void adjMat::dfsHelper(int node, int root, int length, vector<pair<int,int>> &path, vector<bool> &visited, int weight, deque<Cycle> &cycles) {
    if (path.size() == length) {
        for(auto& neighbor : list[node]) {
            int child = neighbor.first;
            int edge_weight = neighbor.second;
            if (child == root) {
                Cycle c;
                c.cycle = path;
                c.total_weight = weight + edge_weight;
                cycles.push_back(c);
            }
        }
        return;
    }
    else {
        for (auto & neighbor : list[node]) {
            if (visited[neighbor.first] == false && neighbor.first >= root) {
                path.push_back({neighbor.first, neighbor.second});
                weight += neighbor.second;
                visited[neighbor.first] = true;
                dfsHelper(neighbor.first, root, length, path, visited, weight, cycles);
                path.pop_back();
                weight -= neighbor.second;
                visited[neighbor.first] = false;
            }
        }
    }
}

// lowkey had to dig into the weeds to get this algorithm!
// citation: https://doi.org/10.1137/0201010
// implemented by brendan lestrange
void adjMat::findCyclesDFS(int length) {
    
    clock_t start  = clock();

    ofstream dfs_cycle_file("../outputs/DFS_cycles.txt");
    
    // data structure is a deque :)))
    deque<Cycle> all_cycles;
    
    for (int i = 0; i < N; i++) {
        vector<pair<int, int>> path;
        vector<bool> visited(N, false);
        int current_weight = 0;

        path.push_back({i, 0});
        visited[i] = true;

        dfsHelper(i, i, length, path, visited, current_weight, all_cycles);

        visited[i] = false;
    }

    clock_t end = clock();

    clock_t duration = end - start;

    dfs_cycle_file << "Total runtime for DFS: " << (float)duration/CLOCKS_PER_SEC << endl;

    if(all_cycles.size() == 0){
        dfs_cycle_file << "No cycles of length " << length << " found." << endl;
        dfs_cycle_file.close();
        return;
    }

    for(int i = 0; i < all_cycles.size(); i++){
        dfs_cycle_file << "{";
        for(int j = 0; j < length; j++){
            dfs_cycle_file << all_cycles[i].cycle[j].first << " -> ";
        }
        dfs_cycle_file << all_cycles[i].cycle[0].first << "} Total edge weight: " << all_cycles[i].total_weight << endl;     
    }
    dfs_cycle_file.close();
}

// implemented by matt bales
void adjMat::findCyclesBFS(int length) {

    clock_t start = clock();
    ofstream bfs_cycle_file("../outputs/BFS_cycles.txt");

    // We look for cycles on each node
    for(int i = 0; i < N; i++){
        
        // We will store paths in a queue
        queue<vector<int>> q;
        int root = i;
        q.push({root});

        // While the queue is nonempty, we check if a path is a cycle
        while(q.size() != 0){

           // Consider last node on path
            vector<int> path = q.front();
            q.pop();
            int lastNode = path.back();

            // If length is correct, check for cycle
            if(path.size() == length){
                for(int j = 0; j < list[lastNode].size(); j++){
                    if(list[lastNode][j].first == root){
                        cycles.push_back(path);
                    }
                }
                continue;
            }
        
            // If the path is not of full-length, create new path with
            // each child and add new path to queue
            for(int j = 0; j < list[lastNode].size(); j++){
                int child = list[lastNode][j].first;

                // don't need to ensure unique cycle since graph is directed.
                // bool isUnique = true;
                // if(child < root){
                //     isUnique = false;
                // }
                
                // Ensure node to be added is not already on path to prevent loops
                // if(isUnique){
                if((find(path.begin(), path.end(), child)) == path.end()){
                    path.push_back(child);
                    q.push(path);
                    path.pop_back();
                }
                // }  
            }  
        }
    }

    // Write cycles to file, verifying cycles vector is nonempty
    if(cycles.size() == 0){
        bfs_cycle_file << "No cycles of length " << length << " found." << endl;
        bfs_cycle_file.close();
        return;
    }
    for(int i = 0; i < cycles.size(); i++){
        bfs_cycle_file << "{";
        for(int j = 0; j < length; j++){
            bfs_cycle_file << cycles[i][j] << " -> ";
        }
        bfs_cycle_file << cycles[i][0] << "}" << endl;
    }

    // Write runtime to file
    clock_t end = clock();
    clock_t duration = end - start;
    bfs_cycle_file << "Total runtime for BFS: " << (float)duration/CLOCKS_PER_SEC;
    bfs_cycle_file.close();

    return;

}

// implemented by matt bales
void adjMat::findShortestPath(int source, int destination){
    
    if(max(source, destination) > N || min(source, destination) < 0){
        cout << "Invalid neuron selection\n";
        return;
    }

    // Nodes to be visited
    queue<int> q;

    // Keep track of path we have taken
    map<int,int> parent;

    // Avoid revisiting node
    vector<bool> visited(N, false);

    q.push(source);
    visited[source] = true;

    int current;
    while(q.size() != 0){

        // Check if path is complete
        current = q.front();
        q.pop();
        visited[current] = true;
        
        // If destination node is found, reconstruct path
        if(current == destination){
            
            vector<int> path;
            int parentNode = parent[current];
            while(parentNode != source){
                path.push_back(parentNode);
                parentNode = parent[parentNode];
            }
            cout << "Minimal path from " << source << " to " << destination << ":\n";
            cout << source << " -> ";
            for(int i = path.size()-1; i >= 0; i--){
                cout << path[i] << "-> ";
            }
            cout << destination << endl;

            return;

        }
        
        // If not, add all children of current node to queue
        int child;
        for(int i = 0; i < list[current].size(); i++){
            child = list[current][i].first;
            if(!visited[child]){
                visited[child] = true;
                parent[child] = current;
                q.push(child);
            }
        }
    }

    cout << "No path exists between " << source << "and " << destination << endl;
    return;

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