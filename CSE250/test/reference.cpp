#include <iostream>
using std::cout;
using std::endl;


int main(){
	int num = 10;
	int& num_ref = num;
	int* int_ptr;

	cout << num << endl << num_ref << endl;
	cout << &num << endl << &num_ref << endl;

	num_ref = 20;

	cout << num << endl << num_ref << endl;
	cout << &num << endl << &num_ref << endl;

	int_ptr = new int;

	cout << int_ptr << endl;

	return 0;
}