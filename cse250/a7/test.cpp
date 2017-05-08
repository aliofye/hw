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



	//test part 1
	std::cout << "START PART ONE"<< std::endl; 
	int count = countOccurrences(pat, text);
	std::cout << "Number of times pattern appears: " << count << std::endl;
	std::cout << "END PART ONE"<< std::endl; 

	//test part 2
	
	
	//test part 3
	std::cout << "START PART THREE"<< std::endl;
	std::vector<unsigned int> cvector = countOccurrences(seqs, text);
	for(auto c : cvector){
		std::cout << "Number of times pattern appears: " << c << std::endl; 
	}
	std::cout << "END PART THREE"<< std::endl;
	
	//test bonus
	std::cout << "START BONUS"<< std::endl;
	std::string text2 = "tooo";
	std::vector<std::string> seqs2;
	seqs2.push_back("to");
	seqs2.push_back("o");

	std::vector<unsigned int> cvector2 = countOccurrences(seqs2, text2, true);
	for(auto c : cvector2){
		std::cout << "Number of times pattern appears: " << c << std::endl; 
	}
	std::cout << "END BONUS"<< std::endl;
	
	return 0;
}