#include "A5.hpp"
#include <iostream>

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
void eval(ItemStack& exprStack) {
   
    std::stack<Item> evalStack;

    const int MIN_ARGS = 2;
    const int DIVIDE_BY_ZERO = 0;
    const int MAX_RESULT = 1;

    //while there are input tokens left

    while(!exprStack.empty()){
    	//read the next token
    	Item token = exprStack.top();
    	exprStack.pop();

    	//if token is value
    	if(token.getType() == VAL){
    		
    		//push value on the stack
    		evalStack.push(token);

    	} else {
    		if(evalStack.size() < MIN_ARGS){

    			//if there are less than 2 operands
    			throw std::runtime_error("Malformed expression.");
    		} else {
    			
    			Item one = evalStack.top();
    			evalStack.pop();
    			int rhs = one.getVal();
    			
    			Item two = evalStack.top();
    			evalStack.pop();
    			int lhs = two.getVal();

    			switch(token.getType()){
    				case MUL:
    				{
    					Item result = lhs * rhs;
    					evalStack.push(result);
    					break;
    				}
    				case DIV:
    				{
    					if(rhs == DIVIDE_BY_ZERO){
    						//can't divide by zero bruh
    						throw std::runtime_error("DIV by 0 error.");
    						break;
    					}
    					
    					Item result = lhs / rhs;
    					evalStack.push(result);
    					break;
    				}
    				case ADD:
    				{
    					Item result = lhs + rhs;
    					evalStack.push(result);
    					break;
    				}
    				case SUB:
    				{
    					Item result = lhs - rhs;
    					evalStack.push(result);
    					break;
    				}
    				default:
    				{
    					//if there is an invalid operator
    					throw std::runtime_error("Malformed expression.");

    				}
    			}
    		}
    	}
    }
    
    //if there is more than one value after evaluating the expression
    if(evalStack.size() != MAX_RESULT){
    	throw std::runtime_error("Malformed expression.");
    }
    	
    exprStack = evalStack;
}

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
ItemStack generateStack(ITNode* root) {
   // Your code goes here.
   ItemStack exprStack;


   return exprStack;
}
