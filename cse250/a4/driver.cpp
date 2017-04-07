//
// Provides some examples on how to throw and catch errors.
//

#include "Stack.hpp"
#include <iostream>


int main() {
   
   //test default constructor
   Stack stack;

   Entry value = 0;
   
   for (int i = 1; i < 6; ++i)
   {
      value = i;
      stack.push(value);
   }

   //stack.test();
   
   //test copy constructor
   Stack nstack;

   for (int i = 1; i < 11; ++i)
   {
     value = i;
     nstack.push(value);
   }

   //nstack.test();

   
   // Example of how to try and catch some code.
   // You may use this to test if you throw exceptions correctly.
   try {
      
      stack.pop();
      stack.test(); //4321

      nstack = stack; 
      nstack.test(); //4321

      stack.pop(); 
      stack.test(); //321

      value = 5;
      nstack.push(value);
      nstack.test(); //54321

      value = 7;
      stack.push(value); 
      stack.test(); //7321

      stack = nstack;
      stack.test(); //54321

      value = 9;
      stack.push(value);
      nstack = stack;
      nstack.test(); //954321

      while(stack.isEmpty() != true){
         stack.pop();
         nstack.pop();
      }

      //invoke copy constructor
      
      
   }
   catch (const std::runtime_error& e) {
      std::cout << "Exception caught." << std::endl;
      std::cout << e.what() << std::endl;
   }

   std::cout << "Code continues to run." << std::endl;

   Stack s1;
   Stack s2;
   for (int i = 0; i < 5; i++) {
      s1.push(i);
   }

   for (int i = 0; i < 10; i++) {
      s2.push(i);
   }
   s2 = s1;


   while (!s1.isEmpty()) {
      std::cout << s1.pop() << " ";
   }
   std::cout << std::endl;
   while (!s2.isEmpty()) {
      std::cout << s2.pop() << " ";
   }
   std::cout << std::endl;

   for (int i = 0; i < 5; i++) {
      s1.push(i);
   }


   if (true) {
      Stack s3;
      for (int i = 0; i < 10; i++) {
         s3.push(i);
      }
      s1 = s3;
   }

   while (!s1.isEmpty()) {
      std::cout << s1.pop() << " ";
   }
   std::cout << std::endl;

   for (int i = 0; i < 5; i++) {
      s1.push(i);
   }

   s1.test();

   Stack s4 = s1;
   Stack s5;
   for (int i = 0; i < 5; i++) {
      s4.push(i);
   }
   while (!s4.isEmpty()) {
      std::cout << s4.pop() << " ";
   }
   std::cout << std::endl;

   for (int i = 0; i < 5; i++) {
      s4.push(i);
   }

   s5 = s4;
   for (int i = 0; i < 5; i++) {
      if (s4.pop() != s5.pop()) {
         std::cout << "bad" << std::endl;
      }
   }

   //std::cout << std::endl;
   //int q;
   //std::cin >> q;

   
   return 0;
}