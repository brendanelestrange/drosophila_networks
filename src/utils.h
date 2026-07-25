#pragma once

#include "adjacency.h"

using namespace std;

pair<vector<int>, pair<int,int>> findKHeaviestCycle(string algorithm, int top_k, bool print_);
vector<pair<int,int>> readInWeights(string file);
vector<int> split(string s, const string& delimiter);
void maxHeapify(vector<pair<int,int>> &arr, int i, int n);
void saveHeapify(vector<pair<int,int>> &weights, string algorithm);
pair<int,int> extractMax(vector<pair<int,int>> &vec, int size);
// vector of pairs of the cycle (vector<int>) and index + weight of cycle
std::fstream& goToLine(std::fstream& file, unsigned int num);
pair<vector<int>, pair<int,int>> getCycle(pair<int,int> &max, string file, bool print);
vector<pair<vector<int>, pair<int, int>>> readInAllCycles(string file);


