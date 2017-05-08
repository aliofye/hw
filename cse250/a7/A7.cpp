#include "A7.hpp"
#include <vector>
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

// Put your function definitions here.
unsigned int countOccurrences(const std::string& seq, const std::string& text){
	
	unsigned int count = 0;
	
	int M = seq.length();
    int N = text.length();
    //const char* pat = seq.c_str();
 
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

std::vector<unsigned int> countOccurrences(const std::vector<std::string>& seqs, const std::string& text){
	std::vector<unsigned int> count;

	for (auto pat : seqs) {
    	int c = countOccurrences(pat, text);
    	count.push_back(c);
	}

	return count;
}

