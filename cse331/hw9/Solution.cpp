#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <float.h>
#include <iostream>


using namespace std;

class Solution {

    /*
    * Class data:
    * points:
    *  - the location of the 2-D points for the problem
    */
public:

    Solution(vector<pair<int,int>> in_points);
    double outputClosestDistance();
    vector<pair<int,int>> points;
};



Solution::Solution(vector<pair<int,int>> in_points) :
    points(in_points)
{/* Nothing needs to be added here.*/}

bool compare_x(const pair<int,int> a, const pair<int,int> b){
	if(a.first == b.first){
		return a.second < b.second;
	} else {
		return a.first < b.first;
	}
}

bool compare_y(const pair<int,int> a, const pair<int,int> b){
	if(a.second == b.second){
		return a.first < b.first;
	} else {
		return a.second < b.second;
	}
}


double distance(const pair<int,int> a, const pair<int,int> b){
	int x1 = a.first;
	int x2 = b.first;
	int y1 = a.second;
	int y2 = b.second;

	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

double closest(vector<pair<int,int>> points, int n, double d)
{
    double min = d;  
 
    for (int i = 0; i < n; ++i){
        for (int j = i+1; j < n && (points[j].second - points[i].second) < min; ++j){
            if (distance(points[i],points[j]) < min){
                min = distance(points[i], points[j]);
            }
        }
    }
    return min;
}

double brute_compute(vector<pair<int,int>> points){
	int n = points.size();
	
	double min = DBL_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (distance(points[i], points[j]) < min)
                min = distance(points[i], points[j]);
    return min;
}

void print(vector<pair<int,int>> points){
	int n = points.size();

	for(int i=0; i<n; i++){
    	cout << points[i].first << ", " << points[i].second << endl;
    }
}

double compute(vector<pair<int,int>> px, vector<pair<int,int>> py){

	int n = px.size();

	//brute force find the min distance if n < 4
	if(n < 4){
		return brute_compute(px);
	}

	int mid = n/2;

	//divide and conquer
	vector<pair<int,int>> lx;
	vector<pair<int,int>> rx;
	vector<pair<int,int>> ly;
	vector<pair<int,int>> ry;

	copy(begin(px), begin(px) + mid, std::back_inserter(lx));
	copy(begin(px) + mid, end(px), std::back_inserter(rx));
	copy(begin(py), begin(py) + mid, std::back_inserter(ly));
	copy(begin(py) + mid, end(py), std::back_inserter(ry));

	//else find midpoint
	int m = (lx[n].first +  rx[0].first)/2;


	//print(left_set);
	//print(right_set);
	
	double dl = compute(lx,ly);
	double dr = compute(rx,ry);

	//find min distance of left set and right set
	double d = min(dl, dr);

	//find mid_set
	vector<pair<int,int>> mid_set;
    
    for (int i = 0; i < n; i++){
        if (abs(py[i].first - m) < d){
            mid_set.push_back(py[i]);
        }
    }

    return min(d, closest(py, n, d));
}
/*
 * Output the distance between the two closest points.
 */
double Solution::outputClosestDistance() {    

    vector<pair<int,int>> px(points);
	sort(px.begin(), px.end(), compare_x);

	vector<pair<int,int>> py(points);
	sort(py.begin(), py.end(), compare_y);

    return compute(px, py);

}
