#include "Solution.cpp"
#include "Graph.h"
#include <fstream>

#include <sstream>
#include <vector>


Graph readFile(string filename)
{
  struct Graph G;
  ifstream inputFile;
  inputFile.open(filename);
  string line;

  if (inputFile.is_open())
  {

    if (getline(inputFile, line)) {
      istringstream iss(line);                
      iss >> G.start;
    }
    if (getline(inputFile, line)) {
      istringstream iss(line);                
      iss >> G.end;
    }

    int node = 0;
    while (getline(inputFile, line))
    {
      istringstream iss(line);
      vector<int> prefList;
      int adjNode;
      while (iss >> adjNode)
      {
        prefList.push_back(adjNode);
      }
      G.graph[node] = prefList;

      node++;
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

  Graph inputGraph = readFile(argv[1]);
  Solution studentSolution(inputGraph.start, inputGraph.end, inputGraph.graph);
  vector<int> path = studentSolution.outputPath();

  cout << "Your Solution: " << endl;
  cout << "=========================================================" << endl;
  std::cout << "[ ";
  for (const auto& i: path) {
    std::cout << i << ' ';
  }
  std::cout << "]" << std::endl;
  cout << "=========================================================" << endl;
}
