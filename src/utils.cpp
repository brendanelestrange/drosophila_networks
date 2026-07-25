// utilities by @brendanelestrange
#include "utils.h"
#include <limits>
/* 
includes utilities for understanding the results

we can find the heaviest cycle and then the goal is to be able to visualize itß

might need to implement this into a Utility class, but i'm not sure yet
*/

using namespace std;

vector<pair<int,int>> readInWeights(string file);
void maxHeapify(vector<pair<int,int>> &arr, int i, int n);
pair<int,int> extractMax(vector<pair<int,int>> &vec);
// vector of pairs of the cycle (vector<int>) and index + weight of cycle
pair<vector<int>, pair<int,int>> getCycle(pair<int,int> &max, string file, bool print);
void saveHeapify(vector<pair<int,int>> &weights, string algorithm);

pair<vector<int>, pair<int,int>> findKHeaviestCycle(string algorithm, int top_k, bool print_){
    string file;
    if (algorithm == "DFS") {
        file = "./outputs/" + algorithm + "_cycles.txt";
    }
    else if (algorithm == "BFS") {
        file = "./outputs/" + algorithm + "_cycles.txt";
    }
    else {
        cerr << "Algorithms are only BFS or DFS" << endl; 
    }

    vector<pair<int,int>> weights = readInWeights(file);
    
    for (int i = weights.size()/2 - 1; i >= 0; i--) {
        maxHeapify(weights, i, weights.size());
    }
    // saveHeapify(weights, algorithm);
    pair<int, int> max;
    for (int i = 0; i < top_k; i++) {
        max = extractMax(weights);
    }
    return getCycle(max, file, print_);
}

vector<pair<int,int>> readInWeights(string file) {
    vector<pair<int, int>> weights;

    fstream fin(file);
    string line;
    getline(fin, line); // discard first line
    int idx = 1; //line 0 is algorithm compute time
    while(getline(fin, line)) {
        
        size_t colon = line.rfind(':');
        string weight_str = line.substr(colon + 1);

        weight_str.erase(remove(weight_str.begin(), weight_str.end(), ' '), weight_str.end());
        int weight = stoi(weight_str);
        weights.push_back(make_pair(idx, weight));
        idx++;
    }  
    return weights;
}

vector<int> split(string s, const string& delimiter) {
    vector<string> tokens;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    vector<int> to_ints;
    for (auto &st : tokens) {
        st.erase(remove(st.begin(), st.end(), ' '), st.end());
        to_ints.push_back(stoi(st));
        
    }
    return to_ints;
}

void maxHeapify(vector<pair<int,int>> &arr, int i, int n) {
    int largest = i;        
    int l = 2 * i + 1;      
    int r = 2 * i + 2;  

    // If left child exists and is larger than root
    if (l < n && arr[l].second > arr[largest].second)
        largest = l;

    // If right child exists and is larger than largest so far
    if (r < n && arr[r].second > arr[largest].second)
        largest = r;

    // If largest is not root, 
    // swap and continue heapifying
    if (largest != i) {
        swap(arr[i], arr[largest]);
        // Recursively heapify 
        maxHeapify(arr, largest, n);
    }
}

void saveHeapify(vector<pair<int,int>> &weights, string algorithm) {
    string file = "./outputs/weightsHeap" + algorithm + ".txt";
    ofstream weightsHeap(file);

    for (pair<int,int> weight : weights) {
        weightsHeap << "index: " << weight.first << " weight: " << weight.second << endl; 
    }

    weightsHeap.close();
}

pair<int,int> extractMax(vector<pair<int,int>> &vec) {
    pair<int,int> r = vec[0];
    // cerr << r << " ";
    int size = vec.size();
    vec[0] = vec[size - 1];
    vec.pop_back();
    maxHeapify(vec, 0, size);
    return r;
}

// taken from https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
fstream& goToLine(fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

pair<vector<int>, pair<int,int>> getCycle(pair<int,int> &weight, string file, bool print) {
    pair<vector<int>,pair<int, int>> cycle;

    fstream fin(file);
    goToLine(fin, weight.first);
    string max_line;
    getline(fin, max_line);
    fin.close();

    size_t open  = max_line.find('{');
    size_t close = max_line.find('}');
    // if (open == string::npos || close == string::npos || colon == string::npos)
    //     continue;            // skip malformed / blank max 

    string verts_str  = max_line.substr(open + 1, close - open - 1);

    vector<int> vertices = split(verts_str, "->");
    cycle = make_pair(vertices, weight);

    if (print) {
        for (int vertex : cycle.first) {
            cout << vertex << " ";
        }
        cout << "weight: " << cycle.second.second << endl;
    }

    return cycle;
}

vector<pair<vector<int>, pair<int, int>>> readInAllCycles(string file) {
    vector<pair<vector<int>,pair<int, int>>> cycles;

    ifstream fin(file);
    string line;
    getline(fin, line);
    int idx = 1; //line 0 is algorithm compute time
    while(getline(fin, line)) {
        size_t open  = line.find('{');
        size_t close = line.find('}');
        size_t colon = line.rfind(':');
        // if (open == string::npos || close == string::npos || colon == string::npos)
        //     continue;            // skip malformed / blank lines

        string verts_str  = line.substr(open + 1, close - open - 1);
        string weight_str = line.substr(colon + 1);

        vector<int> vertices = split(verts_str, "->");

        // strip spaces off the weight before converting
        weight_str.erase(remove(weight_str.begin(), weight_str.end(), ' '),
                         weight_str.end());
        int weight = stoi(weight_str);

        cycles.push_back(make_pair(vertices, make_pair(idx, weight)));
        idx++;
        
    }  
    return cycles;
}



// unfinished code



// node, vector of adjacent (node, weight)
vector<pair<int, vector<pair<int,int>>>> getAdjacentNodes(string adjListFile, vector<int> vertices) {
    vector<pair<int, vector<pair<int,int>>>> adjNodes;
    fstream fin(adjListFile);
    string line;
    for (int vertex : vertices) {
        goToLine(fin, vertex);
        getline(fin, line);

    }
}

// pair<int, vector<pair<int,int>>> readInAdjList(string file) {
//     fstream fin(file);
    

// }




// int main() {


//     pair<vector<int>, pair<int,int>> awesome = findKHeaviestCycle("DFS", 2);

//     for (auto num : awesome.first) {
//         cout << num << " ";
//     }
//     cout << "weight: " << awesome.second.second << endl;
//     return 0;
// }