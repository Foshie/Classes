#use "arith.ml";;
#use "testUtils.ml";;

prt_str_list (List.sort compare (vars_of (Int 42)));;
prt_str_list (List.sort compare (vars_of (Plus (Int 42, Int 13))));;
prt_str_list (List.sort compare (vars_of (Mult(Int 3, Plus(Int 2, Int 1)))));;
prt_str_list (List.sort compare (vars_of (Minus(Int 2, Negate(Int 4)))));;
prt_str_list (List.sort compare (vars_of (Plus(Var "x", Var "y"))));;
prt_str_list (List.sort compare (vars_of (Mult (Var "foo", Plus(Int 3, Var "baz")))));;
