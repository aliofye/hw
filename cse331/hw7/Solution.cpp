#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;



class Solution {

	/*
	* Class data:
	* m_graph:
    *   unordered_map where the keys are node IDs and the values are agjacency lists
    *   *The first entry in each adjacency list is the weight of the key node
    * start_node & end_node:
    *   The id of the start and end node respectively 
	*/
public:

	Solution(int start_node, int end_node, unordered_map<int, vector<int>> in_graph);
	vector<int> outputPath();
	vector<int> m_output_path;
    unordered_map<int, vector<int>> m_graph;
    int m_start_node;
    int m_end_node;
};



Solution::Solution(int start_node, int m_end_node, unordered_map<int, vector<int>> in_graph) :
	m_graph(in_graph), m_start_node(start_node), m_end_node(m_end_node)
{/* Nothing needs to be added here.*/}

class compare_weight{
public:
    bool operator()(pair<int,int> a,pair<int,int> b) {
        return a.second > b.second;
    }
};

void construct_path(vector<int> &path, int node, vector<int> &output_path){
    if(path[node] == -1){
        return;
    }

    construct_path(path, path[node], output_path);
    
    output_path.push_back(path[node]);
}

vector<int> Solution::outputPath() {
    priority_queue<pair<int,int>, vector<pair<int,int>>, compare_weight> queue;
    unordered_set<int> visited;


    //inputs: start_node, end_node, in_graph
    
    //begin dijkstra's

    
    int graph_size = m_graph.size();
    
    //init min_distance vector
    vector<int> min_distance;
    min_distance.resize(graph_size, INT_MAX);
    min_distance[m_start_node] = 0;

    //init path
    vector<int> path;
    path.resize(graph_size, -1);

   	int start_node_weight = m_graph.at(m_start_node)[0];
    //push start_node to queue
    queue.push(make_pair(m_start_node, start_node_weight));
    
    //iterate through all nodes
    while(!queue.empty()){
    	//get node and its weight
    	pair<int, int> current_pair = queue.top();
    	
        int current_node = current_pair.first;
    	int weight = current_pair.second;
    	
        queue.pop();
    	
    	visited.insert(current_node);
    	
    	//get adjacency list
    	vector<int> adjacency_list = m_graph.at(current_node);
	
    	for(int i=1; i<adjacency_list.size(); i++){
    		int target_node = adjacency_list[i];
    		int target_weight = m_graph.at(target_node)[0];
    		

    		
            if(visited.find(target_node) == visited.end()){

                int distance = weight + target_weight;
    			if(distance < min_distance[target_node]){    
                    path[target_node] = current_node;
                    min_distance[target_node] = distance;
                    queue.push(make_pair(target_node, distance));
                }
    		}
    	} 	
    }

    construct_path(path, m_end_node, m_output_path);
    //if there is a path to end node
    if(m_output_path.size() != 0){
        m_output_path.push_back(m_end_node);
    }

    return m_output_path;
}
