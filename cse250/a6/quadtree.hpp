#include <stack>

class QuadTreeNode {
public:
	int value;
	QuadTreeNode* child[4];
};

class TreeIterator {
private:
	
public:
	std::stack<QuadTreeNode*> nodestk; 
	
	TreeIterator(QuadTreeNode* root) {
	
		if(root->child[0] != nullptr){
			TreeIterator(root->child[0]);
		}

		if(root->child[1] != nullptr){
			TreeIterator(root->child[1]);
		}

		if(root->child[2] != nullptr){
			TreeIterator(root->child[2]);
		}

		if(root->child[3] != nullptr){
			TreeIterator(root->child[3]);
		}

		nodestk.push(root);

	}

	TreeIterator& operator++() {
		nodestk.pop();
	}
		
};