#include "HW1Utility.h"
#include "Solution.cpp"
#include <fstream>

// The Student Solution.
class Solution;

// Number of men and women.
int n;
// Stores both the men and women preferences.
map<int, vector<int>> men, women;
// Storing our result and student result.
vector<vector<pair<int,int>>> student_result;

double their_time=0;



// Processing the input using the filename.
void input(string input_filename) {
    freopen(input_filename.c_str(), "r", stdin);

    // Number of men and women.
    cin >> n;

    // Preferences of each woman.
    for(int i=1;i<=n;i++) {
        vector<int> cur;
        for(int j=0;j<n;j++) {
            int pref;
            cin >> pref;
            cur.push_back(pref);
        }
        women[i] = cur;
    }

    // Preferences of each man.
    for(int i=1;i<=n;i++) {
        vector<int> cur;
        for(int j=0;j<n;j++) {
            int pref;
            cin >> pref;
            cur.push_back(pref);
        }
        men[i] = cur;
    }

}

//Same as cmp in HW1_Utils.h but reproduced here so tahat we can sort the stable matchings by women before printing them

bool cmp2(const pair<int,int>& p1, const pair<int,int>& p2)
{
    if(p1.second == p2.second)
        return p1.first < p2.first;

    return p1.second < p2.second; }

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Please provide the input filename as the argument.\n");
        return 0;
    }

    string input_filename = argv[1];


    printf("============================================================================\n");
    cout << "Reading File: " << input_filename << "\n";

    // Load in the input
    input(input_filename);


    their_time=0;
    student_result.clear();
    // Compute your  solution
    clock_t stu = clock();
    Solution s(n, men, women);
    student_result = s.outputStableMatchings();
    their_time = ((double)(clock() - stu))/CLOCKS_PER_SEC;

    printf("Student execution time: %lf secs\n", their_time);

    printf("========================================================\n");
    printf("Your solution:\n");
    //Print your output
    for(int i=0; i<(int)student_result.size();i++)
    {
        vector<pair<int,int>> cur_match;
        cur_match = student_result[i];
        sort(cur_match.begin(), cur_match.end(), cmp2);
            cout << "[";
            for(int i=0;i<(int)cur_match.size();i++)
                cout << "("<<cur_match[i].first << "," << cur_match[i].second << ") ";
            cout << "]\n";
    }

    return 0;
}
