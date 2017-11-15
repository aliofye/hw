#ifndef __HW7GRAPH_H__

#define __HW7GRAPH_H__

#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Graph {
    int start;
    int end;
    unordered_map<int, vector<int>> graph;
};

typedef struct Graph Graph;

#endif
