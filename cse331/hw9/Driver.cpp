#include "Solution.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <vector>
#include <set>

using namespace std;

class Solution;

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Please provide the input filename as the argument.\n");
		return 0;
	}

	string input_filename = argv[1];


	printf("============================================================================\n");
	cout << "Reading File: " << input_filename << "\n";

	// Load in the input
    ifstream input(input_filename, ifstream::in);

    vector<pair<int,int>> points_in;

    string line;
    getline(input, line);
    int n;
    istringstream iss(line);
    iss >> n;

    while(getline(input, line)){
        if(line != ""){
            istringstream iss(line);
            int a, b;
            iss >> a;
            iss >> b;
            pair<int,int> point(a, b);
            points_in.push_back(point);
        }
    }
    input.close();

	double time = 0;
	// Compute your  solution
	clock_t stu = clock();
	Solution* solutionObj = new Solution(points_in);
	double student_result = solutionObj->outputClosestDistance();

	time = ((double)(clock() - stu)) / CLOCKS_PER_SEC;

	printf("Student execution time: %lf secs\n", time);

	printf("========================================================\n");
	printf("Your solution:\n");
	//Print your output
	cout << "Output: " << student_result << endl;
}


