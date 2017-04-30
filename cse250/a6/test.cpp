#include <iostream>
#include "A6-jobs.hpp"
#include "quadtree.hpp"

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
	/*JobQueue jq;
	
	for(int i = 0; i < 100; i++){
		int a = std::rand()%(250-0 + 1) + 0;

		int b = std::rand()%(250-0 + 1) + 0;
		
		Job newJob = Job(a, b);
		jq.push(newJob);
	}
	

	
	try{

		for(int i = 0; i < 101; i++){

			std::cout << jq.top()._pid << ", " << jq.top()._priority << std::endl;
			jq.pop();

		}

		

	} catch(std::runtime_error e){
		std::cout << e.what() << std::endl;
	}*/

	QuadTreeNode* root = new QuadTreeNode();
	root->value = 0;
	QuadTreeNode* one = new QuadTreeNode();
	one->value = 1;

	QuadTreeNode* a = new QuadTreeNode();
	a->value = 1;
	QuadTreeNode* b = new QuadTreeNode();
	b->value = 2;
	QuadTreeNode* c = new QuadTreeNode();
	c->value = 3;
	QuadTreeNode* d = new QuadTreeNode();
	d->value = 4;

	one->child[0] = a;
	one->child[1] = b;
	one->child[2] = c;
	one->child[3] = d;

	QuadTreeNode* two = new QuadTreeNode();
	two->value = 2;
	QuadTreeNode* three = new QuadTreeNode();
	three->value = 3;
	QuadTreeNode* four = new QuadTreeNode();
	four->value = 4;
	
	root->child[0] = one;
	root->child[1] = two;
	root->child[2] = three;
	root->child[3] = four;

	TreeIterator iter = TreeIterator(root);

	while(!iter.nodestk.empty()){
		std::cout << iter.nodestk.top()->value << std::endl;
		++iter;
	}
	
	
	return 0;
}