#ifndef _ITEM_HPP_
#define _ITEM_HPP_

typedef enum {
    MUL, DIV, ADD, SUB, VAL
} Type;

class Item {

public:

    Item(int val);
    Item(char op);
    Item(const Item& other);
    Item& operator=(const Item& other);

    Type getType();
    int getVal();

private:

    Type _type;
    int  _val;
};

#endif // _ITEM_HPP_
