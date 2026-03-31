#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

//The struct we use to store connections
struct connectionStruct{
    string pre_root;
    string post_root;
    string neuropil;
    ushort weight;
};

//Function for reading file
vector<connectionStruct> readConnectionFile(string filename);

int main(int argc, char** argv){

    vector<connectionStruct> connections = readConnectionFile("connections_princeton.csv");

    return 0;
}

vector<connectionStruct> readConnectionFile(string filename){

    //Open file as input filestream. Will parse using string stream
    ifstream fin(filename);
    string line;
    stringstream ss;

    //Will store parsed line in these before making struct
    string pre_root;
    string post_root;
    string neuropil;
    string weight_str;

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

        //Change values for struct variables
        cs.pre_root = pre_root;
        cs.post_root = post_root;
        cs.neuropil = neuropil;
        cs.weight = static_cast<ushort> (stoi(weight_str));

        //Add struct to return vector
        connections_vec.push_back(cs);

    }

    return connections_vec;
}
