//
// Author: Andrew Hughes (ahughes6@buffalo.edu)
//

#include "BST.hpp"
#include "A6-comp.hpp"
#include <cmath>

class CompareLT {
public:
   bool operator() (const int& lhs, const int& rhs) {
      return lhs < rhs;
   }
};

class CompareGT {
public:
   bool operator() (const int& lhs, const int& rhs) {
      return lhs > rhs;
   }
};

class CompareStrange {
public:
   bool operator() (const int& lhs, const int& rhs) {
      return lhs % 10 < rhs % 10 || (!(lhs % 10 < rhs % 10) && (rhs % 100 < lhs % 100));
   }
};


int main() {
   BST<CompareLT> bstLT;
   BST<CompareGT> bstGT;
   BST<CompareStrange> bstStrange;
   BST<CompareBits> bstBits;

   /*int levels = 4;
   for(int i = 0; i < levels; ++i) {
      for(int j = pow(2,levels-i-1); j < pow(2,levels); j+=pow(2,levels-i-1)) {
         bstLT.insert(j);
         bstGT.insert(j);
         bstStrange.insert(j);
      }
   }*/

   /*//start
   bstGT.insert(10);
   bstGT.insert(0);
   bstGT.insert(30);
   bstGT.insert(20);
   bstGT.insert(50);
   bstGT.insert(5);
   bstGT.insert(3);

   std::cout << "Tree using GT:" << std::endl;
   bstGT.printTree();

   bstGT.remove(10);

   std::cout << "Tree using GT:" << std::endl;
   bstGT.printTree();

   bstGT.remove(30);

   std::cout << "Tree using GT:" << std::endl;
   bstGT.printTree();
   *///end

   /*//begin
   bstLT.insert(7);
   bstLT.insert(3);
   bstLT.insert(2);
   bstLT.insert(4);
   bstLT.insert(1);
   bstLT.insert(5);
   bstLT.insert(9);
   bstLT.insert(8);
   bstLT.insert(10);   




   std::cout << "Tree using LT:" << std::endl;
   bstLT.printTree();

   bstLT.remove(1);

   std::cout << "Tree using LT:" << std::endl;
   bstLT.printTree();

   *///end

   bstBits.insert(10);
   bstBits.insert(0);
   bstBits.insert(30);
   bstBits.insert(20);
   bstBits.insert(50);
   bstBits.insert(5);
   bstBits.insert(3);

   std::cout << "Tree using bits:" << std::endl;
   bstBits.printTree();



   /*std::cout << "Tree using Strange:" << std::endl;
   bstStrange.printTree();*/
}