#include "Solution.cpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

class Driver;

vector<pair<int,int>> readFile(string filename)
    {
        vector<pair<int,int>> rallies;
        ifstream inputFile;
        inputFile.open(filename);
        string line;
        if (inputFile.is_open())
        {
            getline(inputFile, line);
            while (getline(inputFile, line))
            {
                istringstream iss(line);
                pair<int,int> rally;
                int duration, deadline;
                iss >> duration;
                iss >> deadline;
                rallies.push_back(std::make_pair(duration,deadline));
            }
        }
        inputFile.close();

        return rallies;
    }
    void printSolution(vector<pair<int,int>> sol) {
        cout << "[";
        for (int i = 0; i < sol.size(); i++) {
            cout << "(";
            cout << sol.at(i).first;
            cout << ",";
            cout << sol.at(i).second;
            cout << ")";
            if (i < sol.size()-1) {
                cout << ",";
            }
        }
        cout << "]" << endl;
    }

    int main(int argc, char** argv) {
        if(argc != 2) {
            printf("Please provide the input filename as the argument.\n");
            return 0;
        }

        vector<pair<int,int>> rallies = readFile(argv[1]);
        Solution studentSolution(rallies);
        vector<pair<int,int>> schedule = studentSolution.outputRallies();

        cout << "Your Solution: " << endl;
        cout << "=========================================================" << endl;
        printSolution(schedule);
        cout << "=========================================================" << endl;
    }
