#include "A5.hpp"
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

void validate(ItemStack& valStack){
    
    if(valStack.empty()){
        throw std::runtime_error("Malformed expression.");
    } else if(valStack.size() == 1 && valStack.top().getType() != VAL){
        throw std::runtime_error("Malformed expression.");
    } else if(valStack.size() == 2){
        throw std::runtime_error("Malformed expression.");
    }

    int val = 0;
    int op = 0;

    while(!valStack.empty()){
        Item token = valStack.top();
        valStack.pop();

        if(token.getType() == VAL){
            val++;
        } else {
            op++;
        }
    }

    if(op != (val - 1)){
        throw std::runtime_error("Malformed expression.");
    }
}
void eval(ItemStack& exprStack) {
   
    ItemStack evalStack;
    evalStack = exprStack;

    const int MIN_ARGS = 2;
    const int DIVIDE_BY_ZERO = 0;
    const int MAX_RESULT = 1;
    
    validate(evalStack);

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
    			
    			Item two = evalStack.top();
    			evalStack.pop();

                int rhs = one.getVal();
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
   
    ItemStack exprStack;

    std::stack<ITNode*> iter;

    iter.push(root);

    while(!iter.empty()){
        
        ITNode* pos = iter.top();
        iter.pop();
        
        //visit node
        exprStack.push(pos->_item);

        if(pos->_left != nullptr){
            iter.push(pos->_left);
        }

        if(pos->_right != nullptr){
            iter.push(pos->_right);
        }
    }

    return exprStack;
}


ITNode* generateExprTree (std::string expr){
    
    ITNode* root;
    ItemStack stack;
    
    //count paranthesis and push chars to stack
    int oPar = 0;
    int cPar = 0;
    
    for(int i = 0; i < expr.length(); i++){
       
        int arr[35];

        if(expr[i] == '('){
            oPar++;
        } else if(expr[i] == ')'){
            cPar++;
        } else if(expr[i] == ' '){
            //skip
        } else{

            int num = expr[i] - '0';

            int count = 0;
            
            if(num < 0 || num > 9){// if num is not an int
                
                Item token = num;
                stack.push(token);

            } else {// if num is an int
                
                arr[count] = num;
                count++;

                num = expr[i + 1] - '0';

                while(num >= 0 || num <= 9){
                    arr[count] = num;
                    count++;
                }

                //get int from arr and push to stack

                num =
            }
            
        }

    }

    //check for mismatched paranthesis
    if(oPar != cPar){
        throw std::runtime_error("Mismatched paranthesis.");
    }

    int val = 0;
    int op = 0;

    while(!stack.empty()){
        Item token = stack.top();
        stack.pop();

        if(token.getType() == VAL){
            val++;
        } else {
            op++;
        }
    }

    if(op != (val - 1)){
        throw std::runtime_error("Malformed expression.");
    }


    
    return root;
}
