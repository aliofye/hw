#include <iostream>

using std::cout;
using std::endl;

int main(){

	
   //**VALUE TEST**//
   int a = 15;
   int const b = 12;

   int& c = a;
   const int* int_ptrA = &a; //invalid without const

   cout << c << endl;

   c = b;

   cout << c << endl;


   //**POINTER TEST**//

   int x = 10;
	int y = 35; //        v   address-of operator (&)
	const int* int_ptrX = &x;
	int* const int_ptrY = &y;
	int* int_ptrZ = &x;

   // Change values pointed to 
   //*int_ptrX = 52; //invalid
   *int_ptrY = 48; 
   *int_ptrZ = 90;

   // Change what the pointer is pointing to
   int_ptrX = int_ptrY;
   //int_ptrY = int_ptrZ; //invalid

   *int_ptrY = 22;

   // Print values 
   cout << *int_ptrX << endl; //22
   cout << *int_ptrY << endl; //22
   cout << *int_ptrZ << endl; //90
   cout << x << endl;

   return 0;
}