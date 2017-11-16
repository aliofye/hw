#include <iostream>
using namespace std;

/*int pow(int a, int n){
		
	if(n == 0){
		return 1;
	}

	int r = a;

	for(int i=1; i<n; i++){
		r *= a;
	}

	return r;
}*/

int pow(int a, unsigned int n)
{
    if(n == 0){
    	return 1;
    }
        
    int r = pow(a, n/2);
    
    if (n%2 == 0)
        return r*r;
    else
        return a*r*r;
}

int main(int argc, char const *argv[])
{
	cout << pow(3,0) << endl;
	cout << pow(3,1) << endl;
	cout << pow(3,2) << endl;
	cout << pow(3,3) << endl;
	return 0;
}