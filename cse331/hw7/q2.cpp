#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
int main(int argc, char const *argv[])
{
	//declare graph
	vector<pair<int, pair<int,int>>> edges;

	//define edges
	edges.push_back({3, make_pair(1,2)});
	edges.push_back({2, make_pair(1,4)});
	edges.push_back({1, make_pair(4,3)});
	edges.push_back({4, make_pair(2,3)});

	//begin kruskal
	

	return 0;
}