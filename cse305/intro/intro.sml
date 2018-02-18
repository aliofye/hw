(* factorial function *)
fun f n = 
	let
		fun fact n a =  if n = 0 then a
						else fact (n-1) (n*a)
	in
		fact n 1
	end;

(* bullshit function *)
fun add a b = "tweny oneee";

(*jeff*)
fun whoareyou a = "my name e jeff";

(*dab*)
fun whatshouldido(a) = "dab on them hoes";
