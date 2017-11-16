#include "Solution.cpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Driver;

    unordered_map<int, vector<int>> readFile(string filename)
    {
      unordered_map<int, vector<int>> graph;
      ifstream inputFile;
      inputFile.open(filename);
      string line;
      if (inputFile.is_open())
      {
          int node = 0;
          while (getline(inputFile, line))
          {
              istringstream iss(line);
              vector<int> neighbors;
              int adj_node;
              while(iss >> adj_node) {
                neighbors.push_back(adj_node);
              }
              graph[node] = neighbors;
              node++;
          }
      }
      inputFile.close();

      return graph;
    }
    void printSolution(vector<int> sol) {
        cout << "[";
        for (int i = 0; i < sol.size(); i++) {
            cout << sol.at(i);
            if (i < sol.size()-1) {
                cout << " ";
            }
        }
        cout << "]" << endl;
    }

    int main(int argc, char** argv) {
        if(argc != 2) {
            printf("Please provide the input filename as the argument.\n");
            return 0;
        }

        unordered_map<int, vector<int>> graph = readFile(argv[1]);
        Solution studentSolution(graph);
        vector<int> output = studentSolution.outputEdges();

        cout << "Your Solution: " << endl;
        cout << "=========================================================" << endl;
        printSolution(output);
        cout << "=========================================================" << endl;
    }
