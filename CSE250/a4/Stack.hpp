//
// Name:
//

#ifndef CSE250_STACK_HPP
#define CSE250_STACK_HPP

#include <stdexcept>

// This typedef line allows us to easily change the values stored in the Stack.
// Changing int to char, for example, would change the values stored to char.
// You should not use int within your stack,
// but rather Entry for your method inputs.
typedef int Entry;

class DNode {
public:
   // Do not change these variables.
   // Value stored in node.
   Entry value;
   // Pointer to next node.
   DNode* next;
   // Pointer to previous node.
   DNode* prev;

   // Feel free to add functionality to the DNode.

}; // DNode class

class Stack {
   // Make sure you use Entry as your parameters to your push.
public:	

	Stack();

	Stack(const Stack& other);

	Stack& operator=(const Stack& other);


	~Stack();

	void push(const Entry& value);

	Entry peek() const;

	Entry pop();

	bool isEmpty() const;

	void deleteStack(DNode* node);

	DNode* copyStack(DNode* node);

	void test();

private:
	DNode* head;

}; // Stack class


#endif //CSE250_STACK_HPP
