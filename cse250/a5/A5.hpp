#ifndef _A5_HPP_
#define _A5_HPP_

#include "Item.hpp"
#include "ITNode.hpp"
#include <stack>
#include <string>
#include <stdexcept>


// Defines the type "ItemStack" to be an STL stack
// holding Items.
typedef std::stack<Item> ItemStack;

/**
 * eval
 *
 * @param stack: stack holding an expression to evaluate.
 *               Upon completion of evaluating a valid stack,
 *               stack should only contain one element, the result
 *               of evaluating the stack.
 *
 * @throw runtime_error: if stack is holding an invalid expression, throw
 *                       a runtime error.
 */
void eval(ItemStack& exprStack);

/**
 * generateStack
 *
 * @param root: root of tree holding expression.
 *
 * @return ItemStack: containing the expression represented
 *                    by the tree in RPN (reverse Polish notation)
 *                    with first value on top
 *                    (if reading RPN from left to right)
 */
ItemStack generateStack(ITNode* root);



#endif // _A5_HPP_
