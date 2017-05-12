#include "A7.hpp"
#include <vector>
#include <algorithm>
#include <map>
#include <set>
//computes longest prefix suffix to preprocess the string 
//for better time complexity using the Knuth Morris Pratt 
//pattern searching algorithm

void computeLPS(const std::string& pat, const int M, int *lps)
{
    // length of the previous longest prefix suffix
    int len = 0;
 
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0)
            {
                len = lps[len-1];
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

//part 1
// Put your function definitions here.
unsigned int countOccurrences(const std::string& seq, const std::string& text){
	
	unsigned int count = 0;
	
	int M = seq.length();
    int N = text.length();
 
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];
 
    // Preprocess the pattern (calculate lps[] array)
    computeLPS(seq, M, lps);
 
    int i = 0;  // index for text[]
    int j  = 0;  // index for seq[]
    while (i < N)
    {
        if (seq[j] == text[i])
        {
            j++;
            i++;
        }
 
        if (j == M)
        {
        	count++; //increment counter of found patterns
            j = lps[j-1];
        }
 
        // mismatch after j matches
        else if (i < N && seq[j] != text[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }

    return count;
}

//part 2
std::vector<unsigned int> countOccurrences(const std::string& text){
	
	std::map<std::string, unsigned int> map;
	std::vector<unsigned int> count;
	
	bool print = true;

	if(text.length() < 4){
		print = false;
	}

	if(print){
		for(char a='a'; a<='z'; ++a) {
		    for(char b='a'; b<='z'; ++b) {
		        for(char c='a'; c<='z'; ++c) {
		            for(char d='a'; d<='z'; ++d){
		            	
		            	std::string word;
		            	word += a;
		            	word += b;
		            	word += c;
		            	word += d;

		            	//do the good shit here
		            	map.insert(std::pair<std::string, unsigned int>(word, 0));
		            }
		        }
		    }
		}

		for (auto const& p : map)
		{
	    	int c = countOccurrences(p.first, text);
	    				
	    	if(c > 0){
	  			map[p.first] = c;
	    	}

	    	count.push_back(p.second);
		}

	} else {
		for(int i = 0; i < 456976; i++){
			count.push_back(0);
		}
	}

	

	return count;

}

//part 3
std::vector<unsigned int> countOccurrences(const std::vector<std::string>& seqs, const std::string& text){
	std::vector<unsigned int> count;

	for (auto pat : seqs) {
    	int c = countOccurrences(pat, text);
    	count.push_back(c);
	}

	return count;
}

//bonus
std::vector<unsigned int> countOccurrences(const std::vector<std::string>& seqs, const std::string& text, bool bonus){

	std::vector<unsigned int> count;
	
	std::vector<std::string> copy = seqs;
	std::vector<std::string>::iterator start = copy.begin();
	std::vector<std::string>::iterator end = copy.end();

	sort(start, end); //sort iterator for next_permutation use

	do{
		std::string pat;
		for(auto str : copy){
			pat += str;
		}
		
		int c = countOccurrences(pat, text);
    	count.push_back(c);

	} while(std::next_permutation(start, end));
	
	return count;
}


