#include <stack>
#include <iostream>

class QuadTreeNode {
public:
	int value;
	QuadTreeNode* child[4];
};

class TreeIterator {
private:
	
public:
	std::stack<QuadTreeNode*> nodestk;

	void iterate(QuadTreeNode* root){

		if(root->child[0] != nullptr){
			iterate(root->child[0]);
		}

		if(root->child[1] != nullptr){
			iterate(root->child[1]);
		}

		if(root->child[2] != nullptr){
			iterate(root->child[2]);
		}

		if(root->child[3] != nullptr){
			iterate(root->child[3]);
		}

		nodestk.push(root);
	} 
	
	TreeIterator(QuadTreeNode* root) {
	
		iterate(root);
	}

	TreeIterator& operator++() {
		QuadTreeNode* node = nodestk.top();
		nodestk.pop();
	}
		
};