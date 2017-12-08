#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {

public:
	Solution(int origin, 
            vector<unordered_map<int, int>> in_edges, 
            vector<unordered_map<int, int>> out_edges);
	vector<int> outputShortestPath();
    vector<unordered_map<int, int>> in_edges;
    vector<unordered_map<int, int>> out_edges;
    int origin;
    vector<int> output;
};



Solution::Solution(int origin, 
                    vector<unordered_map<int, int>> in_edges, 
                    vector<unordered_map<int, int>> out_edges) :
	origin(origin), in_edges(in_edges), out_edges(out_edges)
{/* Nothing needs to be added here.*/}


vector<int> Solution::outputShortestPath() {
    /*
     * Output a vector with shortest distances.
     */
    
    //declare distance array
    const int V = out_edges.size();
    vector<int> distance(V, INT_MAX);
    vector<bool> visited(V, false);

    //set the distance at the origin to be 0
    distance[origin] = 0;
    visited[origin] = true;

    queue<int> q;
    q.push(origin);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        visited[u] = false;
        for(auto it = out_edges[u].begin(); it != out_edges[u].end(); ++it){
            int v = it->first;
            int w = out_edges[u][v];

            if(distance[u] + w < distance[v]){
                distance[v] = distance[u] + w;
                if(!visited[v]){
                    q.push(v);
                    visited[v] = true;
                }
            }
        }
    }

    return distance;
}
