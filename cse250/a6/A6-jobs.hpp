#include <iostream>
#include <stack>

class Job {

public:
	int _pid;
	int _priority;

	Job(int& _pid, int& _priority){
		
		this->_pid = _pid;
		this->_priority = _priority;

	}
};

class JobQueue {
private:
	std::stack<Job> stack;
	std::stack<Job> tmpstk;

public:
	void push(Job newJob){
		if(stack.size() == 0){

			stack.push(newJob);
			
		} else {
			Job currentJob = stack.top();

			if(currentJob._priority > newJob._priority){
				
				stack.push(newJob);

			} else if(currentJob._priority == newJob._priority){

				if(currentJob._pid > newJob._pid){
					stack.push(newJob);
				} else {
					Job elevatedJob = stack.top();
					stack.pop();
					stack.push(newJob);
					stack.push(elevatedJob);
				}

			} else {

				while(currentJob._priority < newJob._priority && !stack.empty()){
					currentJob = stack.top();
					stack.pop();
					tmpstk.push(currentJob);
					currentJob = stack.top();
				}

				stack.push(newJob);

				while(!tmpstk.empty()){
					stack.push(tmpstk.top());
					tmpstk.pop();
				}
			}
			
		}
	
	}

	Job top(){
		if(stack.size() > 0){
			return stack.top();
		} else {
			throw std::runtime_error("I ain't gon say it no more");
		}
	}

	void pop(){
		if(stack.size() > 0){
			stack.pop();
		} else {
			throw std::runtime_error("put some respec on my name");
		}
	}

};
