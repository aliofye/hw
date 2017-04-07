//
// Original Author: Andrew Hughes (ahughes6@buffalo.edu)
//

#ifndef CSE250_A3_PAIRLIST_HPP
#define CSE250_A3_PAIRLIST_HPP

#include <vector>
#include "Pair.hpp"

class PairList {
public:
   /**
    * Declare classes to allow usage in PairList.
    * Both classes defined later.
    */
   class Node;
   class Iterator;

private:
   /** Member variables
    *
    *  Feel free to add member variables here if you wish.
    *  You should not remove or modify _keys.
    */

   // stores links to every node.
   std::vector<Node*> _keys;

   /**
    * Default Constructor:
    *    Set to private to be disabled.
    *    We only allow for a PairList to be initialized
    *    with a starting number of keys.
    */
   PairList();

   // Helper function to copy a PairList::Node list.
   PairList::Node* copyList(PairList::Node* head) const;

   // Helper function to copy a PairList::Node list to a PairNode list.
   PairNode* copyNodeListToPairNodeList(PairList::Node* head, const int& key) const;

   // Helper function to delete a PairList::Node list.
   void deleteList(PairList::Node* head);

   // Helper function to find a node with a given value.
   PairList::Node* findNode(PairList::Node* head, const int& value) const;

   // Helper function to find the node just before where a node should be inserted.
   // If value was already inserted, this returns the node just prior to the node with value.
   PairList::Node* findNodePriorToInsert(PairList::Node* head, const int& value) const;

   // Helper function to check if a key is out of bounds for the _keys vector.
   bool keyOutOfBounds(const int& key) const;
public:
   /**
    *  PairList Constructors:
    */

   /**
    * Constructor to set the initial size of the number of keys.
    *    The number of keys is fixed during the lifetime of the PairList.
    *
    * @param numKeys - number of keys to allocate for.
    */
   PairList(int numKeys);

   /**
    * Copy constructor:
    *    Create a deep copy of the other PairList.
    * @param other - other PairList to copy from.
    */
   PairList(const PairList& other);

   /**
    * Copy assignment operator:
    *    Create a deep copy of the other PairList.
    * @param other - other PairList to copy from.
    * @return reference to this.
    */
   PairList& operator=(const PairList& other);

   /**
    * Destructor:
    *    Clean up all memory used.
    */
   ~PairList();

   /**
    *  PairList Functionality:
    */

   /**
    * insert:
    *    insert the value stored in pair under the list
    *    at location indexed by key, maintaining the list in
    *    increasing sorted order.
    *
    * @param pair (key,value)
    * @return true: value was inserted into list under key.
    *         false: value was unable to be inserted
    *                ** Key didn't exist.
    *                ** Value already existed in list under key.
    */
   bool insert (const Pair& pair);

   /**
    * contains:
    *    determines whether the (key,value) pair is stored in this list.
    *
    * @param pair (key,value)
    * @return true: value was in the list under key.
    *         false: key didn't exist or value was not in list under key.
    */
   bool contains (const Pair& pair) const;

   /**
    * find:
    *    determines whether the (key,value) pair is stored in this list
    *    and returns an iterator to the pair if found.
    *
    * @param pair (key,value)
    * @return Iterator referencing the pair.
    *         If not found, return end().
    */
   Iterator find (const Pair& pair);

   /**
    * remove:
    *    removes the pair from the representation.
    *
    * @param pair (key,value)
    * @return true: value was in the list under key and was removed.
    *         false: key didn't exist or value was not in list under key.
    */
   bool remove (const Pair& pair);

   /**
    *  associatedList:
    *     return a list of pairs associated with the requested key.
    * @param key
    * @return nullptr: key was invalid or no data stored.
    *         PairNode* pointing to first element in generated list of pairs.
    */
   PairNode* associatedList(const int& key) const;


   /**
    * begin:
    *    return an iterator to the first pair in the data structure.
    * @return iterator to first pair stored.
    */
   Iterator begin();

   /**
    * end:
    *    return an iterator to just after the last pair in the data structure.
    * @return iterator to "beyond the last pair"
    */
   Iterator end();


   /******************************************
    * Helper classes:
    ******************************************/

   /**
    *  Node class:
    *
    *  Used for representing lists.
    *
    *  Feel free to add functionality to Node if you wish,
    *  but you must leave minimally value and next.
    */
   class Node {
   public:
      int value;
      Node* next;
   };

   /**
    *  Iterator class:
    *
    *  Iterate the PairList in order of the smallest pair for each
    *  key, followed by the next smallest pair for each, and so on.
    *
    */
   class Iterator {
      // Field to store pointer to PairList iterator is associated with.
      PairList* _associatedPairList;

      // Field to store if iterator is at end or not.
      bool _atEnd;

      // Field to store current location in each list.
      std::vector<PairList::Node*> _currentLocations;

      // Field to store current key iterator is located at.
      int _currentKey;

   public:

      Iterator(PairList* pairList, bool atEnd);

      /** Prefix incrcement:
       *    Move to the next element stored,
       *    in correct order.
       *
       *    @return Reference to updated iterator.
      */
      Iterator& operator++();

      /** Postfix increment:
       *    Move to the next element stored,
       *    in correct order.
       *
       *    @return Copy of current iterator before increment.
      */
      Iterator operator++(int);

      /** Indirection operator:
       *    Access value in position of iterator.
       *
       *    @return Pair representing data stored in structure.
      */
      Pair operator*() const;

      /** Equality operator:
       *    Check if two iterators are representing the same position
       *    in the same PairList.
       *
       *    @return true: same PairList and same position.
       *            false: different PairList or position.
      */
      bool operator==(const Iterator& rhs) const;

      /** Inequality operator:
       *    Check if two iterators are representing the different
       *    positions or iterate different PairLists.
       *
       *    @return true: different PairList or position.
       *            false: same PairList and same position.
      */
      bool operator!=(const Iterator& rhs) const;
   };
};




#endif //CSE250_A3_PAIRLIST_HPP
