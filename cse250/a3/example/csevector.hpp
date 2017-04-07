#ifndef CSE_VECTOR
#define CSE_VECTOR
// Include guard: stops multiple definitions of CSEVector from being
// loaded in a project.
#include <algorithm>
#include <iostream>


template <typename T>
class CSEVector {
   // default scope is private

   // Number of elements stored in vector.
   int _size;

   // Storage for vector will be in an array.
   int _capacity;
   T* _storageArray;

   // Resize size of storage for vector.
   void reserve(int newSize);


public:
   // everything following is public, unless
   // additional access modifier used.

   // Default constructor.
   CSEVector();

   // Default destructor.
   ~CSEVector();

   // Copy constructor.
   CSEVector(const CSEVector<T>&other);

   // Move constructor. (new to C++11)
   CSEVector(CSEVector<T>&& other);

   // Copy assignment.
   CSEVector<T>& operator=(const CSEVector<T>&other);

   // Move assignment. (new to C++11)
   CSEVector<T>& operator=(CSEVector<T>&& other);

   // Get reference to element at index.
   T& at(int index);

   // Get reference to element at index using [] op
   T& operator[](const int& index);

   // Get the number of elements stored.
   int size() const;

   // Return if the vector is storing values.
   bool empty() const;

   // Resize size of storage for vector.
   void resize(const int& newSize);

   // Insert copy of value at index.
   void insert(const int& index,const T& value);

   // Insert copy of value at end of vector.
   void push_back(const T& value);

   // Erase element at index.
   void erase(int index);


}; // class CSEVector

template <typename T>
CSEVector<T>::CSEVector() : _size(0), _capacity(0), _storageArray(nullptr) {
   std::cout << "Default CSEVector constructor called." << std::endl;
}

template <typename T>
CSEVector<T>::~CSEVector() {
   std::cout << "Destructor called." << std::endl;
   delete[] _storageArray;
}

template <typename T>
CSEVector<T>::CSEVector(const CSEVector<T>&other) : _size(0), _capacity(0), _storageArray(nullptr) {
   std::cout << "Copy constructor called." << std::endl;
   // This constructor is used to copy the state of the
   // other object into this instance of the object.

   // Eliminate redundant code by calling copy assignment operator.
   *this = other;

//   // Allocate new space.
//   _storageArray = new T[other._capacity];
//
//   // Set appropriate size of stored values.
//   _size = other._capacity;
//
//   // Copy memory over.
//   std::copy(other._storageArray,other._storageArray+other._size,_storageArray);
//   _size = other._size;
}

template <typename T>
CSEVector<T>::CSEVector(CSEVector<T>&& other) : _size(0), _capacity(0), _storageArray(nullptr) {
   std::cout << "CSEVector move constructor called." << std::endl;
   // This constructor is used to move the state of the
   // other object into this instance of the object.
   // other object should be left in a valid state.

   // Eliminate redundant code by calling move assignment operator.
   *this = std::move(other);

//   // Move state of other into this.
//   _storageArray = other._storageArray;
//   _capacity = other._capacity;
//   _size = other._size;
//
//   // Reset other.
//   other._storageArray = nullptr;
//   other._capacity = 0;
//   other._size = 0;
}

template <typename T>
CSEVector<T>& CSEVector<T>::operator=(const CSEVector<T>& other) {
   std::cout << "Copy assignment operator called." << std::endl;
   // This operator is used to copy the state of the
   // other object into this instance of the object.
   if(this != &other) {
      if(_capacity != other._capacity) {
         // We need to reallocate storage size.
         delete[] _storageArray;
         // In case memory allocation fails,
         // we update state of this object first.
         _size = 0;
         _capacity = 0;
         _storageArray = nullptr;

         // Allocate new space.
         _storageArray = new T[other._capacity];

         // Set appropriate size of stored values.
         _capacity = other._capacity;
      }

      // Copy memory over.
      std::copy(other._storageArray,other._storageArray+other._size,_storageArray);
      _size = other._size;

   }

   return *this;
}

template <typename T>
CSEVector<T>& CSEVector<T>::operator=(CSEVector<T>&& other) {
   std::cout << "Move assignment operator called." << std::endl;
   // This operator is used to move the state of the
   // other object into this instance of the object.
   // other object should be left in a valid state.
   if(this != &other) {
      // Deallocate our current memory.
      delete[] _storageArray;

      // Move state of other into this.
      _storageArray = other._storageArray;
      _capacity = other._capacity;
      _size = other._size;

      // Reset other.
      other._storageArray = nullptr;
      other._capacity = 0;
      other._size = 0;
   }

   return *this;
}

// Get reference to element at index.
template <typename T>
T& CSEVector<T>::at(int index) {
   if(index >= _capacity || index < 0) {
      throw;
   }
   return _storageArray[index];
}

// Get reference to element at index.
template <typename T>
T& CSEVector<T>::operator[](const int& index) {
   return this->at(index);
}

// Get the size of the vector.
template <typename T>
int CSEVector<T>::size() const {
   return _size;
}

// Return if the vector is storing values.
template <typename T>
bool CSEVector<T>::empty() const {
   return _size == 0;
}

// Resize storage.
template <typename T>
void CSEVector<T>::reserve(int newSize) {
   if(_capacity >= newSize) {
      return;
   }
   T* temp = new T[newSize];
   std::copy(_storageArray,_storageArray+_size, temp);
   std::swap(_storageArray,temp);
   delete[] temp;
   _capacity = newSize;
}

// Resize vector.
template <typename T>
void CSEVector<T>::resize(const int& newSize) {
   if(_capacity >= newSize) {
      _size = newSize > 0 ? newSize : 0;
   }
   else {
      this->reserve(newSize);
      _size = newSize;
   }
}

// Insert copy of value at index.
template <typename T>
void CSEVector<T>::insert(const int& index,const T& value) {
   if(index < 0 || index > _size) {
      throw;
   }

   // if we have maxed the size, double the capacity
   if(_size >= _capacity) {
      this->reserve(std::max(1,_capacity*2));
   }

   // shift elements right to make room for value.
   for(int i = _size - 1; i >= index; --i) {
      _storageArray[i+1] = _storageArray[i];
   }

   _storageArray[index] = value;
   _size++;
}

// Insert value at end of storage.
template <typename T>
void CSEVector<T>::push_back(const T& value) {
   this->insert(0,value);
   // if we have maxed the size, double the capacity
//   if(_size >= _capacity) {
//      this->reserve(std::max(1,_capacity*2));
//   }
//
//   // Copy value into last entry.
//   _storageArray[_size] = value;
//   _size++;
}

// Erase element at index.
template <typename T>
void CSEVector<T>::erase(int index) {
   if(index < 0 || index >= _size) {
      throw;
   }

   // shift elements left to cover gap.
   for(int i = index+1; i < _size; ++i) {
      _storageArray[i-1] = _storageArray[i];
   }

   _size--;
}



#endif