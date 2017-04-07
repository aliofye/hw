#ifndef _ITNODE_HPP_
#define _ITNODE_HPP_

#include "Item.hpp"

class ITNode {

public:
    Item _item;
    
    ITNode* _left;
    ITNode* _right;

    // Constructor for item tree node copies in the item to _item
    // and initializes left and right child to nullptr.
    ITNode(Item item) : _item(item), _left(nullptr), _right(nullptr) {
        // We have to initialize _item in the initialization
        // list or it will generate an error (no default constructor for item).
    }
    
private:
    // Default constructor disabled.
    ITNode();

};

#endif // _ITEM_HPP_
