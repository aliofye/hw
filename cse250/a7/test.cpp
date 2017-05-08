#include "A7.cpp"
#include <iostream>
#include <vector>

int main(){

	std::string text = "aaaabab";
	std::string pat = "aaa";
	std::vector<std::string> seqs;
	seqs.push_back("a");
	seqs.push_back("aa");
	seqs.push_back("ab");
	seqs.push_back("aab");


	int count = countOccurrences(pat, text);
	std::cout << "Number of times pattern appears: " << count << std::endl; 

	std::vector<unsigned int> cvector = countOccurrences(seqs, text);
	for(auto c : cvector){
		std::cout << "Number of times pattern appears: " << c << std::endl; 
	}
	
	return 0;
}