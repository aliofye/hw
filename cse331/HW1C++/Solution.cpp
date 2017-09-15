#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
public:
	int n;
	map<int, vector<int>> men;
	map<int, vector<int>> women;
	vector<vector<pair<int, int>>> stableMatchings;
	Solution(int, map<int, vector<int>>, map<int, vector<int>>);
	vector<vector<pair<int, int>>> outputStableMatchings();
	bool is_stable(vector<pair<int, int>>);
};



/**
 * For use in CSE 331
 * Student Solution Stable Marriage Problem
 * Do not change the names of the classes or the functions. You can add other functions etc.
 */

Solution::Solution(int _n, map<int, vector<int>> _men, map<int, vector<int>> _women) {
/* Initialization: Do NOT change */
    n = _n;
    men = _men;
    women = _women;
}


vector<vector<pair<int,int>>> Solution::outputStableMatchings() {

	//declare vector that holds all stable matchings
	vector<vector<pair<int,int>>> stableMatchings;
	//instantiate vector with size n to hold initial permutation 
	//of all possible events
	vector<int> permute;

	for (int i = 1; i < n + 1; ++i){
			
		permute.push_back(i);
	}


	//generate permutations

	vector<vector<int>> permutations;

	do{

		//generate permuted vector of ints

		permutations.push_back(permute);

	} while(next_permutation(permute.begin(), permute.end()));


	//set up pairs
	
	for(int i = 0; i < permutations.size(); i++){		
		for(int j = 0; j < permutations.size(); j++){

			vector<pair<int,int>> currentMatching;

			for(int k = 0; k < n; k++){

				currentMatching.push_back(make_pair(permutations[i].at(k), permutations[j].at(k)));				
			}

			/*test print
			for (int s = 0; s < currentMatching.size(); s++)
			{
				cout << "(" << currentMatching[s].first << ", " << currentMatching[s].second << ")" << " ";
			}

			cout << endl;
			*/

			if(is_stable(currentMatching)){

				stableMatchings.push_back(currentMatching);
			}
		}
	}

    return {stableMatchings};
}


bool Solution::is_stable(vector<pair<int,int>> cur_match) {

	bool isStable = true;
	int man;
	int woman;
	int adulterer;
	int adultress;
	vector<int> mpref;
	vector<int> wpref;

	for (int i = 0; i < n; ++i){

		man = cur_match[i].first;
		woman = cur_match[i].second;

		mpref = men.at(man);
		wpref = women.at(woman);

		//if woman is on top of male preference list
		//continue to check other pairs
		if (woman == mpref.front()){
			continue;
		}

		//else check if there are better alternatives for man
		for (int j = 0; j < n; ++j){
			
			adulterer = cur_match[j].first;
			adultress = cur_match[j].second;
			//get pref list of adultress to see if she likes man
			//more than her husband
			vector<int> apref = women.at(adultress);
			//get index of adulterer in adultress list
			vector<int>::iterator iter = find(apref.begin(), apref.end(), adulterer);
			int adultererIndex = distance(apref.begin(), iter);
			//get index of adultress in man list
			iter = find(mpref.begin(), mpref.end(), adultress);
			int adultressIndex = distance(mpref.begin(), iter);
			//get index of man in adultress list
			iter = find(apref.begin(), apref.end(), man);
			int manIndex = distance(apref.begin(), iter); 
			//check if man is closer to adultress heart than adulterer
			if(adultressIndex < woman && manIndex < adultererIndex){
				isStable = false;
				break;
			}
		}

		if(isStable == false){
			cout << "failed marriage" << endl;
			break;
		}

	}
    return isStable;
}
