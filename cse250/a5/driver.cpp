#include "A5.hpp"
#include "Item.hpp"

#include <vector>
#include <iostream>

void validate(int expected, int actual) {
    if (expected != actual) {
        std::cerr << "Incorrect evaluation. Expected value = " << expected << ", Actual value = " << actual << std::endl;
    }
    else {
        std::cout << "Evaluated expression stack correctly." << std::endl;
    }
}

void deleteExprTree(ITNode* tree) {
    if(tree != nullptr) {
        deleteExprTree(tree->_left);
        deleteExprTree(tree->_right);
        delete tree;
    }
}

int main() {
    /* Change the expression and expected values here to test your code */
    // This is the result of the expression (3 + 4) * (2 - 5) * (2 - 5)
    std::vector<Item> expr = {{3},{4},{'+'},{2},{5},{'-'},{'*'}};
    int expected = -21;
    bool expectException = false;
    
    // exprTree will hold a tree with the expression (3 + 4) * (2 - 5)
    ITNode* exprTree = new ITNode(Item('*'));
    exprTree->_left = new ITNode(Item('+'));
    exprTree->_right = new ITNode(Item('-'));
    ITNode* current = exprTree->_left;
    current->_left = new ITNode(Item(3));
    current->_right = new ITNode(Item(4));
    current = exprTree->_right;
    current->_left = new ITNode(Item(2));
    current->_right = new ITNode(Item(5));
    //////////////////////////////////////////////////////////////////////
    
    ItemStack s;
    
    // Notice that we push the RPN to the stack in reverse order.
    // This gives us the _leftmost item in the RPN formula on top.
    for (auto it = expr.rbegin(); it != expr.rend(); ++it) {
        s.push(*it);
    }

    try {
        // Evaluate expression in stack.
        eval(s);
        
        // After eval, top of stack should be result.
        int actual = s.top().getVal();
        

        if (expectException) {
            std::cerr << "Expected exception but did not throw one" << std::endl;
        }
        else {
            validate(expected, actual);
        }

    }
    catch (const std::runtime_error& e) {
        if (!expectException) {
            std::cerr << "Caught unexpected exception" << std::endl;
        } else {
            std::cout << "Threw exception correctly." << std::endl;
        }
    }

    try {
        // Convert expression in tree to a stack.
        s = generateStack(exprTree);

        // Evaluate expression in stack.
        eval(s);


        // After eval, top of stack should be result.
        int actual = s.top().getVal();


        if (expectException) {
            std::cerr << "Expected exception but did not throw one" << std::endl;
        }
        else {
            validate(expected, actual);
        }

    }
    catch (const std::runtime_error& e) {
        if (!expectException) {
            std::cerr << "Caught unexpected exception" << std::endl;
        }else {
            std::cout << "Threw exception correctly." << std::endl;
        }
    }
    


    // Clean up tree memory.
    deleteExprTree(exprTree);
    //////////////////////////////////////////////////////////////////////

    return 0;
}
