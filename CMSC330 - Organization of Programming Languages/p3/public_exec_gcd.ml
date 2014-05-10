#use "cmd.ml";;
#use "testUtils.ml";;

let rec sequence cmds = match cmds with
    [] -> Skip
  | [c] -> c
  | c::cs -> Seq (c, sequence cs)
;;
let gcd m n = List.assoc "n" (exec [("m",m);("n",n)] (sequence [
  WhileNonZero (
    Var "m",
    IfNonZero (
      Minus (Var "m", Var "n"),
      (* m <> n; see if m < n *)
      sequence [
	Assign ("t1", Mult (Minus (Var "m", Var "n"), Minus (Var "m", Var "n")));
	Assign ("t2", Var "m");
	Assign ("less", Int 0);
        (* If m <= n then t2 will be equal to n within at most t1 ++ *)
	WhileNonZero (
	  Var "t1",
	  sequence [
	    Assign ("t1", Minus (Var "t1", Int 1));
	    Assign ("t2", Plus (Var "t2", Int 1));
	    IfNonZero (
	      Minus (Var "t2", Var "n"),
	      Skip,
	      Assign ("less", Int 1)
	    );
	  ]
	);
	(* If m > n then swap m and n; otherwise n -= m*)
	IfNonZero (
	  Var "less",
	  Assign ("n", Minus (Var "n", Var "m")),
	  sequence [
	    Assign ("m", Plus (Var "m", Var "n"));
	    Assign ("n", Minus (Var "m", Var "n"));
	    Assign ("m", Minus (Var "m", Var "n"))
	  ]
	);
      ],
      (* m = n *)
      Assign ("m", Int 0)
    )
  )
]))
;;

for m = 0 to 20 do
  prt_int_list (List.map (gcd m) [0;1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19;20])
done;;

