#include <iostream>

using std::cout;
using std::string;

int main(int argc, char* argv[]){
	bool b = true;
	char c = 'C';
	int i = 123456;
	float f = 14.1f;
	double d = 14.5;

	string course = "CSE";
	cout << "This is" << course << b << c << i << f << d;
	return 0;
}
