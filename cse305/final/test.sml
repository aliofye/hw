(*fun myfun f b = f 5 (b 3);
fun myfun f b = f 5 b 3;*)
(*fun mystery1 D = foldl (fn((a,b), c) =>
 if a < b
 then (a+b)::c
 else b::c) [] D;
fun mystery2 D =
 case D
 of (y,z)::xs =>
 if y < z
 then [y+z]@(mystery2 xs)
 else [y]@(mystery2 xs)
 | [] => []

 val res = mystery1([(1,2),(2,3)])*)

(*fun foldl (f:'a*'b*'a ->'b)(acc: 'b)(c : 'a )
(l:'a list):'b =
 case l of
 [] => acc
 | x::xs => foldl f (f(x,acc,c)) c xs
fun foo1 c l = foldl
(fn (x,a,c) => if (x > c) then x::a else a)
[] c l
fun foo2 c l =
 case l
 of x::xs =>
 if (x > c)
 then [x]::(foo2 c xs)
 else foo2 c xs
 | [] => [l]*)

 



(*fun mystery3(g, n) =

  if n = 1

  then g 1

  else g n + mystery3(g, n-1)



val res = mystery3(f, 5)*)
(*fun foldl (f:'a*'b->'b)(acc: 'b)(l:'a list):'b =

  case l of

    [] => acc

  | x::xs => foldl f (f(x,acc)) xs

fun mystery1 l = foldl (fn(x, a) =>

  if (x mod 2) = 0

  then x::a

  else a) [] l

fun mystery2 l =

  case l

    of x::xs =>

        if (x mod 2) = 0

        then x::(mystery2 xs)

        else mystery2 xs

     | [] => []

val a = mystery2 [1,2,3]*)
(*fun foo(x) = (print("foo");x)

fun bar(x) = (print("bar");x)

fun baz(x) = (print("baz");x)

val _ = foo baz bar 1;*)
(*let 
	val x = 1

    val y = 2

    fun f y = (print(Int.toString(x+y)); y)

    val x = 3

    val y = 4

    fun g y = print(Int.toString(x+y))

in 
	let 
		val x = 5

   	in 
   		g (f 3)

   	end

end*)
(*fun mystery1 D = foldl (fn((a,b), c) =>
 if a < b
 then (a+b)::c
 else b::c) [] D;*)
(*fun foo(x) = (print("foo\n");x)
fun bar(x) = (print("bar\n");x)
fun baz(x) = (print("baz\n");x)*)

(*val _ = foo (baz bar) *)
(*val _ = foo bar baz 1*)
(*val _ = (foo bar)(baz 1)*)

(*datatype VALUE = 
	Name of string 
	| Integer of int

fun interpret (x,stack,binders) = 
	case x of 
		Name (s)  => (x::stack, s::binders)
		|Integer (i) => (x::stack, binders);

fun interpret2 x stack binders = 
	case x of 
		Name (s)  => (x::stack, s::binders)
		|Integer (i) => (x::stack, binders);