/**
 *  a3-test.cpp:
 *
 *  Author: Andrew Hughes (ahughes6@buffalo.edu)
 *
 *  Passing this is required for grading.
 *  Checks for correct usage of the vector _keys.
 *  Note: _keys must be public for code to compile.
 *
 */

#include "A3.hpp"
#include <iostream>
#include <algorithm>


// Overload << operator to allow printing of a pair.
// This must be a non-member function.
std::ostream& operator<<(std::ostream& os, const Pair& pair) {
   os << '(' << pair.key << ',' << pair.value << ')';
   return os;
}

int main() {
   int numKeys = 2;
   int numValuesPerKey = 5;

   std::cerr << "Creating a pairList with 2 keys." << std::endl;
   PairList pairList(numKeys);

   if(pairList._keys.size() != numKeys) {
      std::cerr << "failed" << std::endl;
      std::cerr << "_keys.size() == " << pairList._keys.size() << " but should be size " << 2 << std::endl;
      return 0;
   }


   // Insert 5 keys into each pair.
   std::cerr << "Inserting 5 pairs into key 1." << std::endl;
   pairList.insert(Pair(1,1));
   pairList.insert(Pair(1,2));
   pairList.insert(Pair(1,0));
   pairList.insert(Pair(1,4));
   pairList.insert(Pair(1,3));

   std::cerr << "Inserting 5 pairs into key 0." << std::endl;
   pairList.insert(Pair(0,0));
   pairList.insert(Pair(0,1));
   pairList.insert(Pair(0,4));
   pairList.insert(Pair(0,3));
   pairList.insert(Pair(0,2));


   if(pairList._keys.size() != numKeys) {
      std::cerr << "failed" << std::endl;
      std::cerr << "Size of _keys vector should not change after insertion/removal/contains." << std::endl;
      return 0;
   }


   // Check that pairs are inserted in _keys.
   PairList::Node* head;
   for(int key = 0; key < numKeys; ++key) {
      head = pairList._keys[key];
      for(int value = 0; value < numValuesPerKey; ++value) {
         if(head == nullptr) {
            std::cerr << "failed" << std::endl;
            std::cerr << "Missing values from the list at key " << key << ". Only found " << value << " out of " << numValuesPerKey << " that were stored." << std::endl;
            break;
         }
         else if(head->value != value) {
            std::cerr << "failed" << std::endl;
            std::cerr << "Values not correctly stored in _keys vector." << std::endl;
            std::cerr << "Confirm your _keys vector stores values in increasing order." << std::endl;
            return 0;
         }
         head = head->next;
      }
   }

   std::cerr << "success" << std::endl;

   std::cerr << "Exiting. An error after this resides within the deconstructor." << std::endl;
   return 0;
}
