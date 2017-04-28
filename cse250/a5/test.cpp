#include <iostream>

int main(){
	
	char c = 'a';

	int i = c - '0';

	int arr[35];

	for(int i = 0; i < 36; i++){
		arr[i] = 696969;
	}

	arr[0] = 1;

	for (int i = 0; i < 36; ++i)
	{
		std::cout <<  arr[i] << std::endl;
	}

	std::cout <<  i << std::endl;
	return 0;
}