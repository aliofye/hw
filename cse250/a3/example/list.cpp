#include "list.hpp"
#include <iostream>

using std::cout;
using std::endl;


List::List(){
   head = nullptr;
   head = new Node; 
   head->value = 0;
   head->next = nullptr; 
}
bool List::insert(const int& value){

   Node* temp = nullptr;
   temp = new Node();
   temp->value = value;
   temp->next = head;
   head = temp;

   cout << head->value << "->" << head->next->value;
}

bool List::contains (const int& value) const{
   bool isFound = false;
   
   //to avoid changing head
   Node* temp = nullptr;
   temp = new Node();
   temp = head;


   while(temp->next != nullptr){
      if(temp->value == value){

         isFound = true;
         break;

      } else {

         isFound = false;
         temp = temp->next;
      }
   }

   return isFound;
}

bool List::remove (const int& value){
   
   bool isRemoved = false;
   //store head temporarily
   Node* temp = nullptr;
   temp = new Node();
   temp = head;

   while(head->next != nullptr){
      if(head->value == value){
         
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

   return isRemoved;
}


List::~List(){
   if(head->next == nullptr){

      head = nullptr;
      delete head;

   } else {

      while(head->next != nullptr){

         head = head->next;
         
         if(head->next = nullptr){

            head = nullptr;
            delete head;

         }
      }
   }
}


int main()
{
   List list;

   if(list.insert(10)){
      cout << "all good!" << endl;
   } else {
      cout << "big problems ahead!" << endl;
   }

   if(list.insert(15)){
      cout << "all good!" << endl;
   } else {
      cout << "big problems ahead!" << endl;
   }

   if(list.insert(20)){
      cout << "all good!" << endl;
   } else {
      cout << "big problems ahead!" << endl;
   }

   if(list.insert(25)){
      cout << "all good!" << endl;
   } else {
      cout << "big problems ahead!" << endl;
   }

   if(list.contains(10)){
      cout << "found!" << endl;
   } else {
      cout << "not found!" << endl;
   }

   if(list.remove(10)){
      cout << "removed!" << endl;
   } else {
      cout << "not removed!" << endl;
   }


   if(list.contains(10)){
      cout << "found!" << endl;
   } else {
      cout << "not found!" << endl;
   }



   
   return 0;
}