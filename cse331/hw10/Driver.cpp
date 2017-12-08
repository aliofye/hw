#include "Solution.cpp"
#include "Graph.h"
#include <fstream>

#include <sstream>
#include <vector>


Graph readFile(string filename) {
  struct Graph G;
  ifstream inputFile;
  inputFile.open(filename);
  string line;

  if (inputFile.is_open()) {

    if (getline(inputFile, line)) {
      istringstream iss(line);
      iss >> G.origin;
    }

    while (getline(inputFile, line)) {
      unordered_map<int, int> incoming;
      unordered_map<int, int> outgoing;

      istringstream iss(line);
      while (iss) {
        int vertex, weight;
        iss >> vertex;
        iss >> weight;
        incoming[vertex] = weight;
      }
      getline(inputFile, line);
      istringstream isa(line);
      while (isa) {
        int vertex, weight;
        isa >> vertex;
        isa >> weight;
        outgoing[vertex] = weight;
      }
      G.in_edges.push_back(incoming);
      G.out_edges.push_back(outgoing);
    }
  }
  inputFile.close();

  return G;
}


int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Please provide the input filename as the argument.\n");
    return 0;
  }

  Graph graph = readFile(argv[1]);
  Solution studentSolution(graph.origin,
                            graph.in_edges,
                            graph.out_edges);
  vector<int> path = studentSolution.outputShortestPath();

  cout << "Your Solution: " << endl;
  cout << "=========================================================" << endl;
  std::cout << "[ ";
  for (const auto& i: path) {
    std::cout << i << ' ';
  }
  std::cout << "]" << std::endl;
  cout << "=========================================================" << endl;
}
