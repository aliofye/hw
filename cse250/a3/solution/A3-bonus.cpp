//
// Original Author: Andrew Hughes (ahughes6@buffalo.edu)
//
// All of your function definitions should be in here.
// **** Note: ****
// **** You should remove the include of iostream ****
// **** before submission (or you will not be graded). ****

#include "A3-bonus.hpp"


PairList::Node* PairList::copyList(PairList::Node* head) const {
   // Base case: list is empty, so return empty list.
   if(head == nullptr) {
      return nullptr;
   }

   // Recursive case: list is not empty.
   Node* rest = head->next;

   // Copy the head into a new node.
   Node* copyHead = new Node();
   copyHead->value = head->value;
   copyHead->prev = nullptr;

   // Link this new node to the copy of the remainder of the list.
   copyHead->next = this->copyList(rest);

   if(copyHead->next != nullptr) {
      // Setup backward link.
      copyHead->next->prev = copyHead;
   }

   // Return the head of the copied list.
   return copyHead;
}

PairNode* PairList::copyNodeListToPairNodeList(PairList::Node* head, const int& key) const {
   // Base case: list is empty, so return empty list.
   if(head == nullptr) {
      return nullptr;
   }

   // Recursive case: list is not empty.
   PairList::Node* rest = head->next;

   // Copy the head into a new pair node.
   PairNode* copyHead = new PairNode(key, head->value);

   // Link this new node to the copy of the remainder of the list.
   copyHead->next = this->copyNodeListToPairNodeList(rest,key);

   // Return the head of the copied list.
   return copyHead;
}

void PairList::deleteList(PairList::Node* head) {
   // Base case: list is empty, there is nothing to delete.
   if(head == nullptr) {
      return;
   }

   // Recursive case: list is not empty.
   PairList::Node* rest = head->next;

   // Delete the head of the list.
   delete head;

   // Delete the rest of list.
   this->deleteList(rest);
}

PairList::Node* PairList::findNode(PairList::Node* head, const int& value) const {
   // Base case: list is empty, there is nothing to delete.
   if(head == nullptr) {
      return nullptr;
   }

   // Recursive case: list is not empty.
   if(head->value == value) {
      // Value found at head of list. Return head.
      return head;
   }
   else {
      // Value not found at head of list, so search remainder of list.
      PairList::Node* rest = head->next;
      return this->findNode(rest,value);
   }
}

PairList::Node* PairList::findNodePriorToInsert(PairList::Node* head, const int& value) const {
   // Base case: empty list
   if(head == nullptr) {
      // If there is an empty list, then the node before insertion is nullptr.
      return nullptr;
   }

   // Base case: one node in list.
   if(head->next == nullptr) {
      if(value <= head->value) {
         // If value is smaller than list head value, or the same,
         // then there is no Node prior to where value should be inserted.
         return nullptr;
      }
      else {
         // If the value was not smaller or equal,
         // then the value should go after head.
         return head;
      }
   }

   // Recursive case: there are 2 or more nodes in list.
   Node* rest = head->next;
   if(value <= rest->value) {
      // Value should come before next node, which means
      // head is the first node previously.
      return head;
   }
   else {
      // Value should go somewhere in the remainder
      // of the list.
      return this->findNodePriorToInsert(rest,value);
   }
}

bool PairList::keyOutOfBounds(const int &key) const {
   // Bounds check the key.
   if(key < 0 || key >= this->_keys.size()) {
      // If key is out of bounds, return true.
      return true;
   }
   else {
      // key is within valid bounds, return false.
      return false;
   }
}

PairList::PairList(int numKeys) : _keys(std::vector<PairList::Node*>(numKeys,nullptr)),
                                  _listLengths(std::vector<int>(numKeys,0)) {
   // Initialized _keys to size numKeys, each entry holding nullptr.
   // Initialized _listLengths to size numKeys, each entry 0.
   // Done in initialization list.
}

PairList::PairList(const PairList &other){
   // Delegate copy constructor to copy assignment operator.
   *this = other;
}

PairList& PairList::operator=(const PairList &other) {
   // Protect against copying when called by "a = a"
   if(this != &other) {
      // Clean up memory.
      for(int i = 0; i < _keys.size(); ++i) {
         deleteList(_keys[i]);
      }

      // Copy pointers from other.
      _keys = other._keys;

      // Make a deep copy of each list.
      for(int i = 0; i < _keys.size(); ++i) {
         _keys[i] = copyList(_keys[i]);
      }
   }
   return (*this);
}

PairList::~PairList() {
   // Clean up memory.
   for(int i = 0; i < _keys.size(); ++i) {
      this->deleteList(_keys[i]);
   }
}

bool PairList::insert(const Pair &pair) {
   // Check if pair was already inserted.
   if(this->contains(pair)) {
      // If the pair is already present, return false.
      return false;
   }

   // Bounds check the key.
   if(this->keyOutOfBounds(pair.key)) {
      // If key is out of bounds, return false.
      return false;
   }

   // We know pair is valid and wasn't previously inserted.
   // Create a new Node that will be inserted.
   Node* newNode = new Node;
   newNode->value = pair.value;
   newNode->prev = nullptr;

   // Head of list to insert at.
   Node* head = this->_keys[pair.key];

   // Check if value should be inserted at head.
   if(head == nullptr || pair.value < head->value) {
      // List is empty or value at head is large than value to insert.
      // Put new node before head.
      newNode->next = head;

      // Make new node the new head of list at key.
      this->_keys[pair.key] = newNode;
   }
   else {
      // Get node just before point to insert value.
      Node* priorNode = this->findNodePriorToInsert(head,pair.value);

      // newNode should go between priorNode and priorNode->next.
      newNode->next = priorNode->next;
      if(newNode->next != nullptr) {
         newNode->next->prev = newNode;
      }
      priorNode->next = newNode;
      newNode->prev = priorNode;
   }

   // Node was inserted at this point.
   return true;
}

bool PairList::contains(const Pair &pair) const {
   // Bounds check the key.
   if(this->keyOutOfBounds(pair.key)) {
      // If key is out of bounds, return false.
      return false;
   }
   else {
      // If findNode returns a Node* that is not nullptr,
      // then that means the value was found under the
      // appropriate key, so the pair was stored previously.
      return this->findNode(_keys[pair.key],pair.value) != nullptr;
   }
}

PairList::Iterator PairList::find(const Pair &pair) {
   if(this->contains(pair)) {
      // If the pair is stored in this PairList,
      // start from begin() and increment until it is found.
      PairList::Iterator item = this->begin();
      while(item != end()) {
         if(*item == pair) {
            // If our iterator points to the pair, return the iterator.
            return item;
         }
         // If we didn't return, increment iterator.
         ++item;
      }
   }
   // Return end() if we didn't contain the pair.
   return end();
}

bool PairList::remove(const Pair &pair) {
   // Check if pair was already inserted.
   if(!this->contains(pair)) {
      // If the pair is not present, return false.
      return false;
   }
   else {
      // Pair was previously inserted, find node before it.
      Node* head = this->_keys[pair.key];
      Node* priorNode = this->findNodePriorToInsert(head,pair.value);
      if(priorNode == nullptr) {
         // Value was at head of list.
         // Move head of list to next node.
         this->_keys[pair.key] = head->next;
         if(head->next != nullptr) {
            head->next->prev = nullptr;
         }

         // Delete head so we don't create a memory leak.
         delete head;
      }
      else {
         // Value was elsewhere in the list.
         Node* nodeToDelete = priorNode->next;

         // Move pointer for prior node to bypass node to delete.
         priorNode->next = nodeToDelete->next;
         if(nodeToDelete->next != nullptr) {
            nodeToDelete->next->prev = priorNode;
         }

         // Delete node so we don't create a memory leak.
         delete nodeToDelete;
      }
      // We have deleted the value corresponding to pair, so return true.
      return true;
   }
}

PairNode* PairList::associatedList(const int &key) const {
   if(this->keyOutOfBounds(key)) {
      // Return nullptr if key is out of bounds.
      return nullptr;
   }
   else {
      // Return copy of list under _keys[key] as list of pairs.
      Node* head = this->_keys[key];
      return this->copyNodeListToPairNodeList(head,key);
   }
}

PairList::Iterator PairList::begin() {
   return PairList::Iterator(this,false);
}

PairList::Iterator PairList::end() {
   return PairList::Iterator(this,true);
}

PairList::Iterator PairList::r_begin() {
   return PairList::Iterator(this,false,-1);
}

PairList::Iterator PairList::r_end() {
   return PairList::Iterator(this,true,-1);
}

PairList::Iterator::Iterator(PairList *pairList, bool atEnd, int level) :
                                                               _associatedPairList(pairList),
                                                               _atEnd(atEnd),
                                                               _currentKey(-1),
                                                               _currentLevel(level) {
   if(!this->_atEnd) {

      if(level == 0) {
         // We are starting with a call from begin() and need to find
         // the first place in our _keys vector where a list is stored.
         for(int i = 0; i < this->_associatedPairList->_keys.size(); ++i) {
            // Find first key with a value to start from.
            if(this->_associatedPairList->_keys[i] != nullptr) {
               _currentKey = i;
               break;
            }
         }

         if(_currentKey == -1) {
            // If we didn't change the value of _currentKey from -1,
            // _currentLocations has no values so set state of
            // iterator to the end.
            _atEnd = true;
         }
      }
      else {
         // We are starting from a call to r_begin() and need to find the
         // largest list with the largest key to start from.
         for(int i = 0; i < this->_associatedPairList->_keys.size(); ++i) {
            // Find first key with a value to start from.
            int level = -1;
            PairList::Node* currentNode = this->_associatedPairList->_keys[i];
            while(currentNode != nullptr) {
               currentNode = currentNode->next;
               level++;
            }
            if(level > 0 && level >= _currentLevel) {
               _currentKey = i;
               _currentLevel = level;
            }
         }

         if(_currentKey == -1) {
            // If we didn't change the value of _currentKey from -1,
            // _currentLocations has no values so set state of
            // iterator to the end.
            _atEnd = true;
            _currentLevel = -1;
         }
      }
   }
}

PairList::Iterator& PairList::Iterator::operator++() {
   // Use this flag to know when we changed current key.
   bool changedKey = false;
   // Find the next entry that still has an entry at the current level.
   for(int i = _currentKey+1; i < this->_associatedPairList->_keys.size(); ++i) {
      PairList::Node* currentNode = this->_associatedPairList->_keys[i];
      // Check if list under _keys[i] has an element at _current level.
      // Otherwise, skip it.
      for(int j = 0; j < _currentLevel; ++j) {
         if(currentNode == nullptr) {
            break;
         }
         currentNode = currentNode->next;
      }

      if(currentNode != nullptr) {
         _currentKey = i;
         changedKey = true;
         break;
      }
   }

   if(!changedKey) {
      // If we didn't find a key to move to,
      // start from beginning again to find one at next level.
      this->_currentLevel++;
      for(int i = 0; i <= this->_currentKey; ++i) {
         PairList::Node* currentNode = this->_associatedPairList->_keys[i];
         // Check if list under _keys[i] has an element at _current level.
         // Otherwise, skip it.
         for(int j = 0; j < _currentLevel; ++j) {
            if(currentNode == nullptr) {
               break;
            }
            currentNode = currentNode->next;
         }

         if(currentNode != nullptr) {
            _currentKey = i;
            changedKey = true;
            break;
         }
      }
   }

   if(!changedKey) {
      // If we still haven't changed the key, we are at the end.
      this->_atEnd = true;
      this->_currentLevel = 0;
   }

   return *this;
}


PairList::Iterator PairList::Iterator::operator++(int) {
   // Create a copy of the current state of the iterator.
   PairList::Iterator iteratorCopy = *this;

   // Increment the iterator.
   ++(*this);

   // Return copy of original state.
   return iteratorCopy;
}

PairList::Iterator& PairList::Iterator::operator--() {
   // Use this flag to know when we changed current key.
   bool changedKey = false;
   // Find the next entry that has an entry at the current level.
   for(int i = _currentKey-1; i >= 0; --i) {
      PairList::Node* currentNode = this->_associatedPairList->_keys[i];
      // Check if list under _keys[i] has an element at _current level.
      // Otherwise, skip it.
      for(int j = 0; j < _currentLevel; ++j) {
         if(currentNode == nullptr) {
            break;
         }
         currentNode = currentNode->next;
      }

      if(currentNode != nullptr) {
         _currentKey = i;
         changedKey = true;
         break;
      }
   }

   if(!changedKey) {
      // If we didn't find a key to move to,
      // start from beginning again to find one at next level.
      this->_currentLevel--;
      if(this->_currentLevel >= 0) {
         for (int i = this->_associatedPairList->_keys.size() - 1; i >= this->_currentKey; --i) {
            PairList::Node *currentNode = this->_associatedPairList->_keys[i];
            // Check if list under _keys[i] has an element at _current level.
            // Otherwise, skip it.
            for (int j = 0; j < _currentLevel; ++j) {
               if (currentNode == nullptr) {
                  break;
               }
               currentNode = currentNode->next;
            }

            if (currentNode != nullptr) {
               _currentKey = i;
               changedKey = true;
               break;
            }
         }
      }
   }

   if(!changedKey) {
      // If we still haven't changed the key, we are at the front end.
      this->_atEnd = true;
      this->_currentLevel = -1;
   }

   return *this;
}


PairList::Iterator PairList::Iterator::operator--(int) {
   // Create a copy of the current state of the iterator.
   PairList::Iterator iteratorCopy = *this;

   // Decrement the iterator.
   --(*this);

   // Return copy of original state.
   return iteratorCopy;
}

Pair PairList::Iterator::operator*() const {
   if(_atEnd) {
      return Pair(-1,-1);
   }
   // We always ensure that _keys[_currentKey] has a list at least length _currentLevel,
   // or we wouldn't be set at this entry.
   PairList::Node* currentNode = this->_associatedPairList->_keys[_currentKey];
   for(int i = 0; i < _currentLevel; ++i) {
      currentNode = currentNode->next;
   }
   return Pair(_currentKey,currentNode->value);
}

bool PairList::Iterator::operator==(const PairList::Iterator &rhs) const {
   // Two iterators must be associated with the same PairList or they
   // cannot be the same.
   // Then, they are the same if they are both at the end or both
   // are positioned at the same pair.
   // Both at the end requires that both are set to the same current level
   // since -1 is the _currentLevel for r_end() and 0 is the current level
   // for end().
   bool isEmpty = false;
   if(this->_atEnd && rhs._atEnd) {
      // Check if associated PairList is empty.
      isEmpty = true;
      for(int i = 0; i < this->_associatedPairList->_keys.size(); ++i) {
         if(this->_associatedPairList->_keys[i] != nullptr) {
            isEmpty = false;
            break;
         }
      }
   }

   return (this->_associatedPairList == rhs._associatedPairList)
         && ((this->_atEnd && rhs._atEnd && (this->_currentLevel == rhs._currentLevel || isEmpty))
           || (!this->_atEnd && !rhs._atEnd && this->operator*() == *rhs));
}

bool PairList::Iterator::operator!=(const PairList::Iterator &rhs) const {
   // Two iterators are not equal if they are not equal.
   return !(*this == rhs);
}