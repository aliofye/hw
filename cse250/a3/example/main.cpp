#include "csevector.hpp"
#include <iostream>

CSEVector<int> foo() {
   return CSEVector<int>();
}

int main() {
   std::cout << "Create CSEVector: " << std::endl;

   // These both call the default constructor.
   CSEVector<int> array1;
   array1.insert(0,5);

   if (true) {
      std::cout << "Create array2 in a temp scope: " << std::endl;
      // CSEVector<int> array2(); // this declares a function that returns a CSEVector<int>.
      CSEVector<int> array2;
   } // array2 scope exited.

   std::cout << "Create a CSEVector that is a copy of array: " << std::endl;
   // This calls the copy constructor.
   CSEVector<int> array3 = array1;


   // Moves array to array4.
   std::cout << "Move array into array4: " << std::endl;
   CSEVector<int> array4 = std::move(array1);

   array4.push_back(20);
   array4.push_back(50);
   array4.insert(0,100);

   std::cout << "\nContents of array1:\n";
   for(int i = 0; i < array1.size(); ++i) {
      std::cout << array1[i] << " ";
   }
   std::cout << "\nContents of array3:\n";
   for(int i = 0; i < array3.size(); ++i) {
      std::cout << array3[i] << " ";
   }
   std::cout << "\nContents of array4:\n";
   for(int i = 0; i < array4.size(); ++i) {
      std::cout << array4[i] << " ";
   }
   std::cout << std::endl;
   std::cout << std::endl;

   return 0;
}