#ifndef __HW10GRAPH_H__

#define __HW10GRAPH_H__

#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Graph {
    int origin;
    vector<unordered_map<int, int>> in_edges;
    vector<unordered_map<int, int>> out_edges;
};

typedef struct Graph Graph;

#endif
