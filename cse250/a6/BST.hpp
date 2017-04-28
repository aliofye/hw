
#ifndef CSE250_BST_HPP
#define CSE250_BST_HPP

#include <stack>
#include <queue>
#include <iostream>
#include <iomanip>
#include <cmath>

typedef int Entry;
class TNode {
public:
   Entry _value;
   TNode* _left;
   TNode* _right;
   TNode(Entry value) : _value(value), _left(nullptr), _right(nullptr) {
      // We have to initialize _item in the initialization
      // list or it will generate an error (no default constructor for item).
   }
};

int computeDepth(TNode* root) {
   if(root == nullptr) { return -1; }
   int maxDepth = -1;
   std::stack<TNode*> nodes;
   TNode* top = root;
   nodes.push(root);
   while(top->_left != nullptr) {
      nodes.push(top->_left);
      top = top->_left;
   }
   while(!nodes.empty()) {
      if(nodes.size()-1 > maxDepth) { maxDepth = nodes.size() - 1; }
      if(top->_right != nullptr) {
         nodes.push(top->_right);
         while(nodes.top()->_left != nullptr) {
            nodes.push(nodes.top()->_left);
         }
         top = nodes.top();
      }
      else {
         nodes.pop();
         while(!nodes.empty() && (nodes.top()->_right == top || nodes.top()->_right == nullptr)) {
            top = nodes.top();
            nodes.pop();
         }
         if(!nodes.empty()) {
            top = nodes.top();
         }
      }
   }
   return maxDepth;
}

template <class COMP>
class BST {
public:
private:
   TNode* _root;
   COMP _compare;
public:
   BST();
   ~BST();

   bool insert(Entry value);
   bool contains(Entry value);
   bool remove(Entry value);

   void printTree();
};

class NodeDepthPair {
public:
   TNode* _node;
   size_t _depth;
   NodeDepthPair(TNode* node, size_t depth) : _node(node), _depth(depth) {}
};

template<class COMP>
BST<COMP>::BST() : _root(nullptr) { }

template<class COMP>
BST<COMP>::~BST() {
   std::stack<TNode*> nodeStack;
   nodeStack.push(_root);
   while(!nodeStack.empty()) {
      // Push left and right then delete node.
      TNode* temp = nodeStack.top();
      nodeStack.pop();
      if(temp != nullptr) {
         nodeStack.push(temp->_left);
         nodeStack.push(temp->_right);
      }
      delete temp;
   }
}

template<class COMP>
bool BST<COMP>::insert(Entry value) {
   if(_root == nullptr) {
      _root = new TNode(value);
      return true;
   }

   TNode* currentNode = _root;
   while(currentNode != nullptr) {
      if(_compare(value, currentNode->_value)) {
         if(currentNode->_left != nullptr) {
            // value < currentNode->_value, and left value, so go left.
            currentNode = currentNode->_left;
         }
         else {
            // value < currentNode->_value, and no left, so insert.
            currentNode->_left = new TNode(value);
            return true;
         }
      }
      else {
         // value < currentNode->_value is false.
         if(_compare(currentNode->_value, value)) {
            if(currentNode->_right != nullptr) {
               // currentNode->_value < value, and right, so go right.
               currentNode = currentNode->_right;
            }
            else {
               // value < currentNode->_value, and no left, so insert.
               currentNode->_right = new TNode(value);
               return true;
            }
         }
         else {
            // value < currentNode->_value is false and
            // currentNode->_value < value is false, so we
            // can assume equal. So value already exists.
            return false;
         }
      }
   }
   return false;
}

template<class COMP>
bool BST<COMP>::contains(Entry value) {
   if(_root == nullptr) {
      // Tree is empty so it doesn't contain value.
      return false;
   }

   TNode* currentNode = _root;
   while(currentNode != nullptr) {
      if(_compare(value, currentNode->_value)) {
         // value < currentNode->_value, and left value, so go left.
         currentNode = currentNode->_left;
      }
      else {
         // value < currentNode->_value is false.
         if(_compare(currentNode->_value, value)) {
            // currentNode->_value < value, and right, so go right.
            currentNode = currentNode->_right;
         }
         else {
            // value < currentNode->_value is false and
            // currentNode->_value < value is false, so we
            // can assume equal. Then we found value.
            return true;
         }
      }
   }
   return false;
}

template<class COMP>
bool BST<COMP>::remove(Entry value) {
   if(_root == nullptr) {
      // Tree is empty, so value is not removed.
      return false;
   }

   TNode* currentNode = _root;
   TNode* prevNode = _root;
   // Check if we need to remove the root.
   bool smaller = _compare(value, _root->_value);
   bool larger = _compare(_root->_value, value);
   if(!smaller && !larger) {
      if(_root->_right != nullptr) {
         // Replace root with next element in-order if it exists.
         prevNode = currentNode;
         currentNode = _root->_right;
         while(currentNode->_left != nullptr) {
            prevNode = currentNode;
            currentNode = currentNode->_left;
         }
         // Move the right subtree root in place of the next node.
         _root->_value = currentNode->_value;
         if(_root == prevNode) {
            _root->_right = currentNode->_right;
         }
         else {
            prevNode->_left = currentNode->_right;
         }
         delete currentNode;
      }
      else {
         // There is no right subtree, so move left subtree to root.
         currentNode = _root->_left;
         delete _root;
         _root = currentNode;
      }
      return true;
   }


   while(currentNode != nullptr) {
      smaller = _compare(value, currentNode->_value);
      larger = _compare(currentNode->_value, value);
      if(!smaller && !larger) {
         TNode* removeNode = currentNode;
         // value is at current node.
         if(currentNode->_right != nullptr) {
            // Replace current node with next element in-order, if it exists.
            prevNode = currentNode;
            currentNode = currentNode->_right;
            while(currentNode->_left != nullptr) {
               prevNode = currentNode;
               currentNode = currentNode->_left;
            }
            // Move the value for the next element up to the element that was removed.
            removeNode->_value = currentNode->_value;
            // Move the right subtree into the appropriate node.
            if(prevNode->_left == currentNode) {
               prevNode->_left = currentNode->_right;
            }
            else {
               prevNode->_right = currentNode->_right;
            }
            delete currentNode;
         }
         else {
            // There is no right subtree, so move left subtree to currentNode.
            if(currentNode == prevNode->_left) {
               prevNode->_left = currentNode->_left;
            }
            else {
               prevNode->_right = currentNode->_left;
            }
            delete currentNode;
         }
         return true;
      }
      else if(smaller) {
         // value < currentNode->_value, and left value, so go left.
         prevNode = currentNode;
         currentNode = currentNode->_left;
      }
      else {
         // value < currentNode->_value is false.
         // currentNode->_value < value, and right, so go right.
         prevNode = currentNode;
         currentNode = currentNode->_right;
      }
   }
   return false;
}

template<class COMP>
void BST<COMP>::printTree() {
   std::queue<NodeDepthPair> printQueue;
   std::queue<NodeDepthPair> previousNodes;
   size_t treeDepth = computeDepth(_root);

   if(_root == nullptr) {
      return;
   }

   size_t currentDepth = 0;
   printQueue.emplace(_root,currentDepth);
   while(!printQueue.empty()) {
      NodeDepthPair next = printQueue.front();
      printQueue.pop();
      previousNodes.push(next);

      if(next._depth != currentDepth) {
         std::cout << std::endl;
         currentDepth++;
//         elementAtDepth = 0;
//         printedAtDepth = 0;
      }
      std::cout << next._node->_value << " ";

      if(next._node->_left != nullptr) {
         printQueue.emplace(next._node->_left,currentDepth+1);
      }
      if(next._node->_right != nullptr) {
         printQueue.emplace(next._node->_right,currentDepth+1);
      }
   }
   std::cout << std::endl;
}

#endif //CSE250_BST_HPP
