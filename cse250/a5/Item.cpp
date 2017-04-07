#include "Item.hpp"

#include <stdexcept>

Item::Item(int val) {
    _val = val;
    _type = VAL;
}

Item::Item(char op) {
    switch(op) {
        case '*':
            _type = MUL;
            break;
        case '/':
            _type = DIV;
            break;
        case '+':
            _type = ADD;
            break;
        case '-':
            _type = SUB;
            break;
        default:
            throw std::runtime_error("Invalid operator provided to Item constructor");
    }
}

Item::Item(const Item& other) {
    this->operator=(other);
}

Item& Item::operator=(const Item& other) {
    if (this == &other) {
       return *this;
    }
    _val = other._val;
    _type = other._type;
    return *this;
}

Type Item::getType() {
    return _type;
}

int Item::getVal() {
    return _val;
}
