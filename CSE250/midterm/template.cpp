#include <iostream>
using std::cout;
using std::endl;


template <typename T>
void Max(T& one, T& two){
	if (one < two){
		cout << one << " is less than " << two << endl;
	} else {
		cout << one << " is greater than " << two << endl;
	}
}

template <class T>
class Number{

public:
	T x = 10;
	T y = 30;

};

int main()
{
	
	Number<int> a;

	Max(a.x, a.y);
	
	Number<double> b;

	Max(b.x, b.y);

	Number<float> c;

	Max(c.x, c.y);


	

	return 0;
}