(*REFERENCES*)
(*http://www.smlnj.org//doc/smlnj-lib/Manual/ord-set.html#section:0*)
(*http://www.cs.cornell.edu/courses/cs312/2008sp/handouts/sml-nj-library.html*)
(*http://sml-family.org/Basis/string.html*)

(*init stack*)
val stack = ["5", "add"];
(*helper functions to route to functions from commands*)
fun is_push(command : string) = String.isSubstring "push" command;
fun is_pop(command : string) = String.isSubstring "pop" command;
fun is_add(command : string) = String.isSubstring "add" command;
fun is_sub(command : string) = String.isSubstring "sub" command;
fun is_mul(command : string) = String.isSubstring "mul" command;
fun is_div(command : string) = String.isSubstring "div" command;
fun is_rem(command : string) = String.isSubstring "rem" command;
fun is_neg(command : string) = String.isSubstring "neg" command;
fun is_swap(command : string) = String.isSubstring "swap" command;
fun is_quit(command : string) = String.isSubstring "quit" command;
(*helper functions that deal with each operation*)
fun push_helper(command) = stack;
fun pop_helper() = List.drop(stack,1);
fun math_helper(command) = stack;
fun neg_helper() = stack;
fun swap_helper() = stack;
fun quit_helper() = stack;

(*main program*)
fun interpreter(inFile : string, outFile : string) =
	let
    	(*open files*)
    	val ins = TextIO.openIn(inFile)
    	val outs = TextIO.openOut(outFile)
    	(*helper function to iterate through each command in the file*)
    	fun helper(data : string option) =
      		case(data) of
          		NONE => (TextIO.closeIn(ins); TextIO.closeOut(outs))
    		|	SOME(command) => 
    			( 
					let
						
						val s = "command\n"
						val n = List.length(stack);
						val new_stack = if 		is_push(command) then push_helper(command) 
										else if is_pop(command)  then pop_helper()
										else if is_add(command)  then math_helper(command)
										else if is_sub(command)  then math_helper(command)
										else if is_mul(command)  then math_helper(command)
										else if is_div(command)  then math_helper(command)
										else if is_rem(command)  then math_helper(command)
										else if is_neg(command)  then neg_helper()
										else if is_swap(command) then swap_helper()
										else if is_quit(command) then quit_helper()
										else 	stack;
					in
						(*output result to file*)
						List.drop(stack, n);
						stack @ new_stack; 
						TextIO.output(outs, s)
					end;

					(*recursive call of helper function*)
					helper(TextIO.inputLine(ins))
				);
  	in
    	(*call helper function*)
    	helper(TextIO.inputLine(ins))
  	end;

val _ = interpreter("./input.txt", "output.txt")