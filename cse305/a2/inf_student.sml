datatype 'a inflist = NIL
                    | CONS of 'a * (unit -> 'a inflist);

exception Empty;
exception Subscript;

fun HD (CONS(a,b)) = a
  | HD NIL = raise Empty; 

fun TL (CONS(a,b)) = b()
  | TL NIL = raise Empty;

fun NUL NIL = true
  | NUL _ = false;

fun NTH 0 L = HD L
  | NTH n L = NTH (n-1) (TL L);

fun TAKE (xs, 0) = []
  | TAKE (NIL, n) = raise Subscript
  | TAKE (CONS(x, xf), n) = x::TAKE(xf(), n-1);

fun FROMN n = CONS(n, fn () => FROMN (n+1));

fun FILL n = CONS(n, fn () => FILL n);

fun FIB n m = CONS(n, fn () => FIB m (n+m));

fun FILTER f l =
  if NUL l
  then NIL
  else if f (HD l)
       then CONS(HD l, fn() => (FILTER f (TL l)))
       else FILTER f (TL l);

fun SIFT NIL = NIL
  | SIFT l =
     let val a = HD l
     in CONS(a, fn () => SIFT(FILTER (fn x => x mod a <> 0) (TL l)))
     end;

	 
(**********************
 *
 * FUNCTION AND INFLIST STUBS -- YOU MUST IMPLEMENT THESE
 * 
 * printList and printPairList must write to the file named by f.
 * Anything printed to the terminal will not be graded.
 *
 **********************)
 
fun even (x : int) : bool = x mod 2 = 0;
fun odd  (x : int) : bool = x mod 2 <> 0;
val fibs  = FIB 0 1;
val natural = FROMN 0;
val evens = FILTER even natural;
val odds  = FILTER odd natural;
val allZeros = FILL 0;
val allOnes  = FILL 1;
val primes   = SIFT (FROMN 2);

fun printGenList (f : ('a -> 'b)) nil : unit = ()
	| printGenList (f : ('a -> 'b)) (l : ('a list)) : unit = (f (hd l); printGenList f (tl l));

fun printList (f : string, l : int list) : unit = (
	let
    	val outs = TextIO.openOut(f);
	in
		printGenList (fn(i) => TextIO.output(outs, Int.toString(i)^" ")) l;
		TextIO.closeOut(outs)
	end);

fun printPairList (f : string, l : (int * int) list) : unit = (
	let
		val outs = TextIO.openOut(f);
	in
		printGenList (fn(i,j) => TextIO.output(outs, "("^Int.toString(i)^", "^Int.toString(j)^") ")) l;
		TextIO.closeOut(outs)
	end);

fun rev_zip (_, NIL) = NIL
	| rev_zip (NIL, _) = NIL
	| rev_zip (infL1 : 'a inflist, infL2 : 'b inflist) : ('b * 'a) inflist = CONS((HD infL2, HD infL1), fn () => (rev_zip (TL infL1, TL infL2)));

(*val result = TAKE(rev_zip (evens, odds), 10);*)
(*val result = printList("output.txt", [1,2,3,4]);*)
(*val result = printPairList("output.txt", [(1,1),(2,2),(3,3),(4,4)]);*)
(*val result = NTH 4 primes;*)

