//
// Name:
//

#include "Stack.hpp"


//implement default constructor
Stack::Stack(){
	//cout << "****************default constructor call************" << endl;
	head = nullptr;
}

//implement copy constructor
Stack::Stack(const Stack& other){
	//cout << "****************copy constructor call************" << endl;
	head = nullptr;
	*this = other;
}

//check if stack is empty
bool Stack::isEmpty() const{
	if(head == nullptr){
		return true;
	} else {
		return false;
	}
}

void Stack::deleteStack(DNode* node){
	if(node == nullptr) {
      //cout << "Head is null, nothing deleted" << endl;
      return;
   	}

   	//cout << "Delete node with value: "<<node->value<<endl;
	
	DNode* rest = node->next;

	delete node;

	this->deleteStack(rest);	

}

DNode* Stack::copyStack(DNode* node){
	
	if(node == nullptr){
		return nullptr;
	} 
		
	//recursive step
	DNode* rest = node->next;
	
	//declare copy node
	DNode* copyNode = nullptr;
	copyNode = new DNode();
	copyNode->value = node->value;

	copyNode->next = this->copyStack(rest);

	if(copyNode->next != nullptr){
		copyNode->next->prev = copyNode;
	}

	// Return the head of the copied list.
	return copyNode;
	
}

//implement copy operator
Stack& Stack::operator=(const Stack& other){
	// Protect against copying when called by "a = a"
	if(this != &other) {
	// Clean up memory.
		deleteStack(head);

	// Make a deep copy of each stack.
		head = copyStack(other.head);
	}

	return *this;
}

//implement destructor
Stack::~Stack(){
	//cout << "****************destructor call************" << endl;
	deleteStack(head);
}


//implement push
void Stack::push(const Entry& value){
	
	//init temp node
	DNode* temp = nullptr;
	temp = new DNode();
	
	//set temp to the new values
	temp->value = value;
	temp->next = head;
	
	//set head to temp
	head = temp;
	head->prev = nullptr;

	//doubly link it
	if(head->next != nullptr){
		head->next->prev = head;
	}


	temp = nullptr;
	delete temp;
}

Entry Stack::peek() const{
	if(isEmpty()){
		throw std::runtime_error("Peek called on empty stack.");
	}

	return head->value;
}

Entry Stack::pop(){
	
	if(isEmpty()){
		throw std::runtime_error("Pop called on empty stack.");
	}

	//make copy of value
	Entry value = head->value;
	
	//delete last element
	DNode* temp = head->next;
	delete head;

	head = nullptr;
	head = temp;
	
	if(head != nullptr){
		head->prev = nullptr;
	}

	temp = nullptr;
	delete temp;
	
	

	//return copy
	return value;
}

void Stack::test(){
	DNode* temp = head;
	
	bool stop = false;
	//iterate to the end
	//cout << "iterate front" << endl;

	while(!stop){
		//cout << temp->value << " ";
		if(temp->next != nullptr){
			temp = temp->next;
		}else{
			stop = true;
		}
	}

	//cout << endl;

	//iterate to the front
	//cout << "iterate back" << endl;

	stop = false;

	while(!stop){
		
		//cout << temp->value << " ";
		if(temp->prev != nullptr){
			temp = temp->prev;
		} else {
			stop = true;
		}
	}

	//cout << endl;
}