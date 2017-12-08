#include <iostream>
#include <string>
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

void print(vector<unordered_map<int,int>> printable){
    for(int i=0; i<printable.size(); i++){
        for(int j=0; j<printable[i].size(); j++){
            cout << printable[i][j] << " ";
        }
        cout << endl;
    }
}


vector<int> Solution::outputShortestPath() {
    /*
     * Output a vector with shortest distances.
     */
    
    //change input
    vector<pair<pair<int,int>, int>> edges;

    for(int i=0; i<out_edges.size(); i++){
        for(int j=0; j<out_edges[i].size(); j++){
            int u = i;
            int v = j;
            int w1 = out_edges[u][v];
            int w2 = in_edges[u][v];

            /*cout << "(" << u << ", " << v << "): " << w1 << endl;
            cout << "(" << v << ", " << u << "): " << w2 << endl;  */

            
            edges.push_back(make_pair(make_pair(u,v), w1));
            //edges.push_back(make_pair(make_pair(v,u), w2));
              
        }
    }

    //declare distance array
    const int V = out_edges.size();
    int distance[V];
    bool visited[V];

    //init distance array to infinity
    for(int i=0; i<V; i++){
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    //set the distance at the origin to be 0
    distance[origin] = 0;
    visited[origin] = true;

    //iterate |V-1| times and find shortest path
    for(int i=1; i<=(V-1); i++){
        const int E = edges.size();
        
        for(int j=0; j<E; j++){
            pair<int,int> edge = edges[j].first;

            int u = edge.first;
            int v = edge.second;
            int w = edges[j].second;

            if( w != 0 && visited[u] == true && distance[u] + w < distance[v] ){
               distance[v] = distance[u] + w;
               visited[v] = true;
            }
        }
        
    }

    vector<int> output;

    for(int i=0; i<V; i++){
        if(distance[i] != INT_MAX){
            output.push_back(distance[i]);
        } else {
            output.push_back(0);
        }
    }


    return output;
}
