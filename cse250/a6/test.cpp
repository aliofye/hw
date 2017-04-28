#include <iostream>
#include "A6-jobs.hpp"

int getHammingWeight(int num){
	if(num < 0){
		return 0; //doesn't accept neg numbers
	}

	int w = 0;
	while(num){
		num &= (num - 1);
		w += 1;
	}

	return w;	
}

int main()
{
	/*bool small = false;
	bool large = false;
	int a = 2; // 0010
	int b = 15;// 1111

	// 128 64 32 16 8 4 2 1
	//			    1 0 1 0
	//				0 0 0 0
	//            1 1 1 1 0
	//            1 0 1 0 0


	std::cout << getHammingWeight(b) << std::endl;*/
	int a = 1;
	int b = 10;
	JobQueue jq;
	Job newJob = Job(a, b);
	jq.push(newJob);
	a = 2; b = 1;
	newJob = Job(a, b);
	jq.push(newJob);
	a = 5; b = 3;
	newJob = Job(a, b);
	jq.push(newJob);
	a = 4; b = 3;
	newJob = Job(a, b);
	jq.push(newJob);

	
	try{

		std::cout << jq.top()._pid << ", " << jq.top()._priority << std::endl;

		jq.pop();

		std::cout << jq.top()._pid << ", " << jq.top()._priority << std::endl;

		jq.pop();

		std::cout << jq.top()._pid << ", " << jq.top()._priority << std::endl;

		jq.pop();

		std::cout << jq.top()._pid << ", " << jq.top()._priority << std::endl;


	} catch(std::runtime_error e){
		std::cout << e.what() << std::endl;
	}
	
	
	return 0;
}