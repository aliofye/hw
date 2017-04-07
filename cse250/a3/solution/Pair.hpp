/**
 * Author: Andrew Hughes (ahughes6@buffalo.edu)
 *
 * Contains the Pair and PairNode classes.
 *
 * Do not modify this file.
 * It will be overwritten upon submission.
 */

#ifndef CSE250_A3_PAIR_HPP
#define CSE250_A3_PAIR_HPP

#include <ostream>
/**
 * Pair class:
 * Used as interpretation of data stored in PairList.
 *
 */
class Pair {
   // Not default constructable.
   Pair();
public:
   int key;
   int value;

   Pair(int initKey, int initValue) : key(initKey), value(initValue) { }

   bool operator==(const Pair& rhs) const { return (key == rhs.key && value == rhs.value);}
   bool operator!=(const Pair& rhs) const { return !(key == rhs.key && value == rhs.value);}
};

/**
*  PairNode class:
*
*  Used for representing lists of Pairs.
*/
class PairNode {
   PairNode();

public:
   Pair value;
   PairNode* next;

   PairNode(int key = 0, int value = 0) : value(Pair(key,value)), next(nullptr) { }
};

#endif //CSE250_A3_PAIR_HPP
