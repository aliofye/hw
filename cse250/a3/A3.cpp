//
// Original Author: Andrew Hughes (ahughes6@buffalo.edu)
//
// All of your function definitions should be in here.
// **** Note: ****
// **** You should remove the include of iostream ****
// **** before submission (or you will not be graded). ****

#include "A3.hpp"
#include <iostream>
using std::cout;
using std::endl;


PairList::PairList(int numKeys) {
   _keys.resize(numKeys);

   for (int i = 0; i < _keys.size(); ++i)
   {
      _keys.at(i) = nullptr;
      _keys.at(i) = new Node();
      _keys.at(i)->value = 0; 
      _keys.at(i)->next = nullptr;
   }
}

PairList::PairList(const PairList &other){
   *this = other; //use copy operator
}

PairList& PairList::operator=(const PairList &other) {
   
   if(this != &other){
      if(_keys.size() != other._keys.size()){
         _keys.resize(other._keys.size());
      }

      for(int i = 0; i < other._keys.size(); ++i){
         _keys.at(i) = nullptr;
         _keys.at(i) = new Node();
         _keys.at(i)->value = other._keys.at(i)->value; //deep copy
         _keys.at(i)->next = other._keys.at(i)->next;

      }
   }

   return (*this);
}

PairList::~PairList() {
   for(int i = 0; i < _keys.size(); ++i){
      _keys.at(i) = nullptr;
      delete _keys.at(i);
   }
}


bool PairList::insert(const Pair &pair) {
   
   Node* head = nullptr;
   head = _keys.at(pair.key);

   Node* temp = nullptr;
   temp = new Node();

   if(contains(pair) != true){
      
      temp->value = pair.value;
      temp->next = head;
      head = temp;
   

      //sort
      mergeSort(&head);

      return true;

   } else{ //if duplicate
      
      cout << "duplicate" << endl;
      return false;

   }
}

bool PairList::contains(const Pair &pair) const {
   bool isFound = false;
   
   
   if(_keys.at(pair.key) != nullptr){//if node under key exists

      Node* temp = nullptr;
      temp = new Node();
      temp = _keys.at(pair.key);

      while(temp->next != nullptr){
         if(temp->value == pair.value){

            isFound = true;
            cout << "found!" << endl;
            break;

         } else {

            cout << temp->value << "=? " << pair.value << endl;
            cout << "no found!" << endl;
            isFound = false;
            temp = temp->next;

         }
      }

   } else {//if node under key doesn't exist

      isFound = false;
      
   }
   
   return isFound;
}

PairList::Iterator PairList::find(const Pair &pair) {
   return end();
}

bool PairList::remove(const Pair &pair) {
   
   bool isRemoved = false;
   
   Node* head = nullptr;
   head = new Node();
   head = _keys.at(pair.key);

   if(head != nullptr){
   
      //store head temporarily
      Node* temp = nullptr;
      temp = new Node();
      temp = head;

      while(head->next != nullptr){
         if(head->value == pair.value){
            
            temp->next = head->next;
            //remove head
            head = nullptr;
            delete head;
            head = temp;
            isRemoved = true;
            break;

         } else {
            temp = head;
            head = head->next;
            isRemoved = false;
         }
      }
   } else {
      isRemoved = false;
   }

   return isRemoved;
}

PairNode* PairList::associatedList(const int &key) const {
  
   if(_keys.at(key) != nullptr){//if node exists at key

      Node* temp = nullptr;
      temp = new Node();
      temp = _keys.at(key)->next;

      PairNode* pairHead = nullptr;
      pairHead = new PairNode(key, temp->value);

      PairNode* pairTemp = nullptr;
      pairTemp = pairHead;

      while(temp->next != nullptr){
         pairTemp->next = new PairNode(key, temp->next->value);
         pairTemp = pairTemp->next;
         temp = temp->next;
      }

      return pairHead;

   } else {
      return nullptr;
   }
}

PairList::Iterator PairList::begin() {
   return PairList::Iterator();
}

PairList::Iterator PairList::end() {
   return PairList::Iterator();
}

PairList::Iterator& PairList::Iterator::operator++() {
   return *this;
}

PairList::Iterator PairList::Iterator::operator++(int) {
   return PairList::Iterator();
}

Pair PairList::Iterator::operator*() {
   return Pair(-1,-1);
}

bool PairList::Iterator::operator==(const PairList::Iterator &rhs) const {
   return false;
}

bool PairList::Iterator::operator!=(const PairList::Iterator &rhs) const {
   return false;
}
