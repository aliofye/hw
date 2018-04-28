(*REFERENCES*)
(*http://www.smlnj.org//doc/smlnj-lib/Manual/ord-set.html#section:0*)
(*http://www.cs.cornell.edu/courses/cs312/2008sp/handouts/sml-nj-library.html*)
(*http://sml-family.org/Basis/string.html*)

val LETTERS_IN_ALPHABET = 26;
(*create Set data structure*)
structure Set = RedBlackSetFn(
	struct
    	(*type of elements stored in Set structure*)
    	type ord_key = char
    	(*char comparator*)
    	val compare = Char.compare
    end
);

(*add the alphabet to set*)
val alphabet = Set.fromList(explode("abcdefghijklmnopqrstuvwxyz"));

fun pangram(inFile : string, outFile : string) =
	let
    	(*open files*)
    	val ins = TextIO.openIn(inFile)
    	val outs = TextIO.openOut(outFile)
    	(*helper function to iterate through each line in the file*)
    	fun helper(data : string option) =
      		case(data) of
          		NONE => (TextIO.closeIn(ins); TextIO.closeOut(outs))
    		|	SOME(line) =>
    				( 
						let
							(*convert line to list of chars*)
							val chars = Set.fromList(explode(line));
							(*set letters to be the intersection of chars and the alphabet*)
							val letters = Set.intersection(chars, alphabet);
							(*check if the intersection is equal to the numbers of the alphabet*)
							val check : bool = Set.numItems letters = LETTERS_IN_ALPHABET;
							(*convert the check from bool to string*)
							(*the concatenate it with a line break*)
							val s : string = Bool.toString(check) ^ "\n";
						
						in
							(*output result to file*)
							TextIO.output(outs, s)
						end;

						(*recursive call of helper function*)
						helper(TextIO.inputLine(ins))
					);
  	in
    	(*call helper function*)
    	helper(TextIO.inputLine(ins))
  	end;

val _ = pangram("./tests/input/input13.txt", "output.txt")