#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <climits>


using namespace std;
class Solution
{
    public:
        Solution(unordered_map<int, vector<int>>);
        unordered_map<int, vector<int>> graph;
        vector<int> outputEdges();
};

Solution::Solution(unordered_map<int, vector<int>> _graph) : graph(_graph)
{
}


vector<int> Solution::outputEdges() {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> queue;

    //start prim
    //get graph size
    const int graph_size = graph.size();
    //anchor MST at root 0
    int root = 0;
    vector<int> parent(graph_size, -1);
    vector<int> key(graph_size, INT_MAX);
    vector<bool> mst_set(graph_size, false);

    key[root] = 0;

    queue.push(make_pair(0, root));

    while(!queue.empty()){
    	pair<int,int> current_pair = queue.top();
    	queue.pop();

    	int u = current_pair.second;

    	mst_set[u] = true;

    	vector<int> adjacency_list = graph.at(u);
    	
    	for(int i=0; i<adjacency_list.size(); i++){
    		int v = i;
    		int w = adjacency_list[i];

    		if(mst_set[v] == false && key[v] > w && w != -1){
    			key[v] = w;
    			queue.push(make_pair(key[v], v));
    			parent[v] = u;
    		}
    	}
    }

    return parent;
}
