//
// Original Author: Andrew Hughes (ahughes6@buffalo.edu)
//

#include "A3.hpp"
#include "Pair.hpp"
#include <iostream>

// Overload << operator to allow printing of a pair.
// This must be a non-member function.
std::ostream& operator<<(std::ostream& os, const Pair& pair) {
   os << '(' << pair.key << ',' << pair.value << ')';
   return os;
}

void deleteList(PairNode* head) {
   if(head == nullptr) {
      return;
   }
   deleteList(head->next);
   delete head;
}

int main() {
   int numKeys = 2;
   int numValuesPerKey = 6;
   PairList pairList(numKeys);


   // Insert some pairs into pairList
   pairList.insert(Pair(0,11));
   pairList.insert(Pair(0,10));
   pairList.insert(Pair(0,11));
   pairList.insert(Pair(0,7));
   pairList.insert(Pair(0,8));
   pairList.insert(Pair(0,2));


   pairList.insert(Pair(1,8));
   pairList.insert(Pair(1,2));
   pairList.insert(Pair(1,3));
   pairList.insert(Pair(1,8));
   pairList.insert(Pair(1,5));
   pairList.insert(Pair(1,6));


   // Check that pairs are found.
   int valuesFound;
   PairNode* head;
   PairNode* temp;
   for(int key = 0; key < numKeys; ++key) {
      valuesFound = 0;
      std::cout << "There should be " << numValuesPerKey << " associated with key " << key << std::endl;
      head = pairList.associatedList(key);
      temp = head;

      // Print out list returned and compute length of list returned.
      for(valuesFound = 0; valuesFound < numValuesPerKey-1; ++valuesFound) {
         if(temp == nullptr) {
            break;
         }
         std::cout << temp->value << ", ";
         temp = temp->next;
      }
      if(temp != nullptr) {
         valuesFound++;
         std::cout << temp->value << std::endl;
      }

      // Clean up memory used.
      deleteList(head);


      std::cout << "Found " << valuesFound << " values associated with key " << key << std::endl;
   }

   // Call copy constructor.
   std::cout << "Creating a new pair list that is a copy of the first." << std::endl;
   PairList pairListCopy = pairList;

   std::cout << "Creating a new pair list, inserting one element, then copying in original list." << std::endl;
   PairList pairListOtherCopy(10);
   pairListOtherCopy.insert(Pair(5,3));
   std::cout << *(pairListOtherCopy.begin()) << std::endl;
   pairListOtherCopy = pairList;

   PairList::Iterator iterBegin = pairList.begin();
   PairList::Iterator iterEnd = pairList.end();

}
