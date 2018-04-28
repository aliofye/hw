fun writeFile(filename : string, content : string) =
    let val outs = TextIO.openOut filename
        val _ = TextIO.output (outs, content) handle e => (TextIO.closeOut outs; raise e)
        val _ = TextIO.closeOut outs
    in () 
    end;

val s = [["lo", "behold"], ["hey", "what"]];
fun main (stk) = 
	let
		val lol = "hey";
		val filename = "output.txt";
		val stack = stk@[["haha", "man"]];
	in
		
    	map (fn pair => writeFile(filename, (List.nth(pair, 1)))) stack

	end;
val _ = main(s);
print (String.concatWith "\n" (map (fn l => List.nth(l, 1)) s));
