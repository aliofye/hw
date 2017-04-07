#include <iostream>
#include <math.h>

using std::cout;
using std::pow;
using std::endl;

int fn(int n){
	int fn = (-0.01) * pow(n, 3) + 3 * pow (n, 2) - 2 * n;
	return fn;
}


int main(){

	int rhs = -20;

	for (int i = 1; i < 1000; i++)
	{
		int lhs = fn(i);
		if(lhs <= rhs){
			cout << lhs << ", " << i << endl;
			break;
		}
	}

	return 0;
}