#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
class Solution
{
    public:
        Solution(vector<pair<int,int>>);
        vector<pair<int,int>> rallies;
        vector<pair<int,int>> outputRallies();
};

Solution::Solution(vector<pair<int,int>> _rallies)
{
	rallies = _rallies;
}

bool compare(const pair<int,pair<int,int>> &a, const pair<int,pair<int,int>> &b){
    return (a.second.second < b.second.second);
}


/** Implement the solution in this function
 * Return a vector of pairs of int containing the Rally ID and start time of the schedule you computed
 * or an empty vector of pairs of int if there exists no valid schedule and Serena has to take the nuke option.
 *
 * Don't change any files but this one!
 */
vector<pair<int,int>> Solution::outputRallies()
{
    std::vector<std::pair<int,int>> schedule;
    std::vector<std::pair<int,std::pair<int,int>>> ordered_rallies;

    //populate order vector
    for(int i=0; i<rallies.size(); i++){
    	ordered_rallies.push_back(std::pair<int,std::pair<int,int>>(i,rallies[i]));
    }
    
    //first we sort by finish time
    std::sort(ordered_rallies.begin(), ordered_rallies.end(), compare);


    int end = ordered_rallies.back().second.second;
    //std::cout << "End: " << end << std::endl;
    
    int curr_time = 0;
    int last_time = 0;

    //we iterate through every pair
    for(int i=0; i<ordered_rallies.size(); i++){
    	
		std::pair<int, std::pair<int,int>> interval = ordered_rallies[i];
		std::pair<int,int> result(interval.first, curr_time);
		schedule.push_back(result);
		curr_time+=interval.second.first;
		
    	if(curr_time > end){
    		//std::cout << "Hey! I was called to clear dem schedules nahmean?!" << std::endl;
    		schedule.clear();
    		break;
    	}
    }

    //std::cout << "Start: " << start << std::endl;
    return schedule;
}
