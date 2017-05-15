#include "A7.hpp"
#include <vector>
#include <algorithm>
#include <unordered_map>

//part 1
unsigned int countOccurrences(const std::string& seq, const std::string& text){
	
	std::pair<std::string, unsigned int> pair(seq, 0);

	unsigned int max = seq.length();
	unsigned int limit = text.length();


	if(limit > 0){

		for(int i = 0; i < limit - max + 1; ++i){

			std::string str1 = text.substr(i, max);

			for(int j = 0; j < max; ++j){

				std::string str2 = str1.substr(0, j + 1);

				//count number of occurances
				if(str2 == seq){ pair.second++; }
			}

		}

		for(int i = limit - max + 1; i < limit; ++i){

			std::string str1 = text.substr(i, max);
			
			for(int j = 0; i + j < limit; ++j){

				std::string str2 = str1.substr(0, j + 1);

				//count number of occurances
				if(str2 == seq){ pair.second++; }
			}
		}
	}
	

	unsigned int count = pair.second;
	
    return count;
}

//part 2
std::vector<unsigned int> countOccurrences(const std::string& text){
	
	//initialize a vector to the maximum number of 4 letter combinations (26^4)
	std::vector<unsigned int> count(456976, 0);

	unsigned int limit = text.length();
	
	//check to see if the text is less than 4 letters, meaning no occurances can be found
	if(limit < 4){
		
		return count;

	} else {
		
		for(int i = 0; i < limit - 3; ++i){
		
			std::string str = text.substr(i, i + 4);
					
			//hash the string into an index, i.e. 'aaaa' = 0
			int index = ((str[0] - 'a') * 26 * 26 * 26) + ((str[1] - 'a') * 26 * 26) + ((str[2] - 'a') * 26) + (str[3] - 'a');
			
			count.at(index)++;

		}
	}

	

	return count;

}

//part 3
std::vector<unsigned int> countOccurrences(const std::vector<std::string>& seqs, const std::string& text){
	
	
	unsigned int size = seqs.size();
	unsigned int limit = text.length();
	

	std::unordered_map<std::string, unsigned int> map;
	std::unordered_map<std::string, unsigned int>::iterator it;

	unsigned int max = 0;

	for(auto str : seqs){
		
		//evaluate max size of all seqs
		if(str.size() > max){ max = str.size(); }

		map.insert(std::pair<std::string, unsigned int>(str, 0));
	}

	//check to see if text is not a null string
	if(limit > 0){

		for(int i = 0; i < limit - max + 1; ++i){

			std::string str1 = text.substr(i, max);

			for(int j = 0; j < max; ++j){

				std::string str2 = str1.substr(0, j + 1);

				it = map.find(str2);

				//count number of occurances
				if(it != map.end()){ it->second++; }
			}

		}

		for(int i = limit - max + 1; i < limit; ++i){

			std::string str1 = text.substr(i, max);
			
			for(int j = 0; i+j < limit; ++j){

				std::string str2 = str1.substr(0, j + 1);

				it = map.find(str2);

				//count number of occurances
				if(it != map.end()){ it->second++; }
			}
		}
	}
	

	//take count of occurances in map in store in vector
	std::vector<unsigned int> count(size, 0);


	for(int i = 0; i < count.size(); ++i){

		it = map.find(seqs.at(i));
		count.at(i) = it->second;
	}


	return count;
}

//bonus
std::vector<unsigned int> countOccurrences(const std::vector<std::string>& seqs, const std::string& text, bool bonus){

	unsigned int size = seqs.size();
	
	std::vector<std::string> pair;
	
	//counter to erase first seqs.size() * seqs.size() - 1 digits
	unsigned int c = 0;
	
	//generate sequence pairs from (0, 0) to (0, n-1) ... (1,0) to (1, n-1) ...
	for(int i = 0; i < size; ++i){
		
		for(int j = 0; j < size - 1; j++){

			std::string pat = seqs[i] + seqs[j];

			c++;

			//this for loop will generate redundant pairs so they are removed
			if(c >= (seqs.size() * seqs.size() - 1)){ pair.push_back(pat); }

		}
	}

	//generate sequence pairs from (n-1, 0) to (n-1, n-1)
	for(int i = size - 1; i >= 0; --i){

		for(int j = size - 1; j >= 0; --j){

			std::string pat = seqs[i] + seqs[j];

			pair.push_back(pat);
			
		}
	}

	//push back means everything is stored in reverse order, so reverse back
	std::reverse(pair.begin(), pair.end());


	std::vector<unsigned int> count;

	std::unordered_map<std::string, unsigned int> map;
	std::unordered_map<std::string, unsigned int>::iterator it;
	
	unsigned int max = 0;


	//insert each pair into map and calculate max size of string in pair
	for(auto pat : pair){
		if(pat.size() > max){
			max = pat.size();
		}

		map.insert(std::pair<std::string, unsigned int>(pat, 0));
	}

	unsigned int limit = text.length();

	if(limit > 0){

		//find number of occurances from index 0 to limit - max + 1
		for(int i = 0; i < limit - max + 1; ++i){

			try{

				std::string str1 = text.substr(i, max);

				for(int j = 0; j < max; ++j){

					std::string str2 = str1.substr(0, j + 1);

					it = map.find(str2);

					//count number of occurances
					if(it != map.end()){ it->second++; }
				}

			} catch(std::out_of_range e){
				//e.what();
			}
		}
		
		//find number of occurances from index limit - max + 1 to limit
		for(int i = limit - max + 1; i < limit; ++i){
			
			try{

				std::string str1 = text.substr(i, max);
				
				for(int j = 0; i+j < limit; ++j){

					std::string str2 = str1.substr(0, j + 1);

					it = map.find(str2);

					//count number of occurances
					if(it != map.end()){ it->second++; }
				}
			} catch(std::out_of_range e){}
		}
	}
	
	//iterate through map and push count
	for(auto pat : pair){

		it = map.find(pat);
		count.push_back(it->second);
	}

	return count;
}




