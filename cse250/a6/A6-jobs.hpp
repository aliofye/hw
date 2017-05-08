#include <iostream>
#include <queue>
#include <vector>

class Job {

public:
	int _pid;
	int _priority;

	Job(const int _pid, const int _priority){
		
		this->_pid = _pid;
		this->_priority = _priority;

	}
};

class Compare {

public:
 bool operator() (const Job& currentJob, const Job& newJob){
 	
 	if(currentJob._priority == newJob._priority){
 		
 		return currentJob._pid > newJob._pid;

 	} else {
 		
 		return currentJob._priority > newJob._priority;
 	
 	}
 }	
};


class JobQueue {

private:

	std::priority_queue<Job, std::vector<Job>, Compare> queue;

public:
	void push(Job newJob){
		queue.push(newJob);
	}

	Job top(){
		if(!queue.empty()){
			return queue.top();
		} else {
			throw std::runtime_error("I ain't gon say it no more");
		}
	}

	void pop(){
		if(!queue.empty()){
			queue.pop();
		} else {
			throw std::runtime_error("put some respec on my name");
		}
	}

};
