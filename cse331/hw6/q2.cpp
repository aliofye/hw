#include <vector>
#include <iostream>

int main(int argc, char const *argv[])
{
	int houses[5] = {10,40,90,150,200};
	std::vector<int> towers;
	int size = 5;
	int max = 200;

	int last_coverage = 0;

	for(int i=0; i<size; i++){
		if(last_coverage < houses[i]){
			last_coverage = houses[i] + 100;
			towers.push_back(houses[i]);
		} else if(i+1 < size) {
			int distance_one = houses[i]-towers.back();
			int distance_two = houses[i+1]-houses[i];
			
			if(distance_one > distance_two){
				last_coverage = houses[i]+100;
				towers.push_back(houses[i]);
			}
		}

		if(last_coverage >= max){
			break;
		}
	}

	for(int i=0; i<towers.size(); i++){
		std::cout << towers[i] << std::endl;
	}
	return 0;
}