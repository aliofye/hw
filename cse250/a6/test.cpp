#include <iostream>
#include "A6-jobs.hpp"

int getHammingWeight(int num){
	if(num < 0){
		return 0; //doesn't accept negative numbers
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

	// 128 64 32 16 8 4 2 1
	//			    1 0 1 0
	//				0 0 0 0
	//            1 1 1 1 0
	//            1 0 1 0 0


	//std::cout << getHammingWeight(b) << std::endl;
	JobQueue jq;
	
	for(int i = 0; i < 100; i++){
		int a = std::rand()%(250-0 + 1) + 0;

		int b = std::rand()%(250-0 + 1) + 0;
		
		Job newJob = Job(a, b);
		jq.push(newJob);
	}
	

	
	try{

		for(int i = 0; i < 100; i++){

			std::cout << jq.top()._pid << ", " << jq.top()._priority << std::endl;
			jq.pop();
			
		}

		

	} catch(std::runtime_error e){
		std::cout << e.what() << std::endl;
	}
	
	
	return 0;
}