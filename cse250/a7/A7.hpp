#ifndef CSE250_A7_HPP
#define CSE250_A7_HPP

#include <vector>
#include <string>

/**
 * countOccurrences
 *
 * @param seq: sequence of characters you want to find all matches of.
 * @param text: body of text to find matches in. All characters are a-z.
 *
 * @return: return the count of the number of times seq occurs in text.
 */
unsigned int countOccurrences(const std::string& seq, const std::string& text);


/**
 * countOccurrences
 *
 * @param text: body of text to find matches in. All characters are a-z.
 *
 * @return: return the occurrence count of each 4 character string
 * (including those that are not present).
 */
std::vector<unsigned int> countOccurrences(const std::string& text);


/**
 * countOccurrences
 * @param seqs: vector holding sequences of characters to be matched.
 * @param text: body of text to find matches in. All characters are a-z
 *
 * @return: return a vector containing occurrence counts of each sequence
 *                 (counts should occur in the order sequences are given).
 */
std::vector<unsigned int> countOccurrences(const std::vector<std::string>& seqs, const std::string& text);

/**
 * countOccurrences (bonus)
 *
 * @param seqs: vector holding sequences of characters to be matched.
 * @param text: body of text to find matches in. All characters are a-z
 *
 * @return: return a vector containing occurrence counts for
 *          each pair of sequences
 *          (counts should occur in the order sequences are given).
*/
std::vector<unsigned int> countOccurrences(const std::vector<std::string>& seqs, const std::string& text, bool bonus);

#endif //CSE250_A7_HPP
