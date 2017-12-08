#include "Solution.cpp"
#include "Graph.h"
#include <fstream>

#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>

template <typename T> class basic_stopwatch
{
    typedef T clock;
    typename clock::time_point p;
    typename clock::duration   d;

public:
    void tick()  { p  = clock::now();            }
    void tock()  { d += clock::now() - p;        }
    void reset() { d  = clock::duration::zero(); }

    template <typename S> unsigned long long int report() const
    {
        return std::chrono::duration_cast<S>(d).count();
    }

    unsigned long long int report_ms() const
    {
        return report<std::chrono::microseconds>();
    }

    basic_stopwatch() : p(), d() { }
};

struct c_clock
{
    typedef std::clock_t time_point;
    typedef std::clock_t duration;
    static time_point now() { return std::clock(); }
};

template <> unsigned long long int basic_stopwatch<c_clock>::report_ms() const
{
  return 1000. * double(d) / double(CLOCKS_PER_SEC);
}

typedef basic_stopwatch<std::chrono::high_resolution_clock> stopwatch;
typedef basic_stopwatch<c_clock> cstopwatch;


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
  
  stopwatch sw;
  sw.tick();
  vector<int> path = studentSolution.outputShortestPath();
  sw.tock();
  std::cout << "This took " << sw.report_ms() << "ms.\n";

  cout << "Your Solution: " << endl;
  cout << "=========================================================" << endl;
  std::cout << "[ ";
  for (const auto& i: path) {
    std::cout << i << ' ';
  }
  std::cout << "]" << std::endl;
  cout << "=========================================================" << endl;
}
