#include <iostream>
using std::cout;
using std:: endl;



class Node{
public: 	
	int value;
	Node* next;
};


int altdif(Node* list){
	int total = 0;
	bool sign = false;

	if(list == nullptr){
		return 0;
	} else if(list->next == nullptr){
		return list->value;
	} else {
		while(list->next != nullptr){
			if(!sign){
				total -= list->value;
			} else {
				total += list->value;
			}

			list = list->next;
			sign = !sign;
		}

		if (sign) {
   			 return -total;
  		} else {
    		return total;
  		}
	}
}

int main()
{
	
	Node* head = nullptr;

	cout << altdif(head) << endl;

	head = new Node();
	head->value = 10;
	head->next = nullptr;

	cout << altdif(head) << endl;

	head->value = 6;
	Node* two = head;
	two->next = new Node();
	two = two->next;
	two->value = 4;
	two->next = new Node();
	two->next->value = 1;

	cout << altdif(head) << endl;





	return 0;
}