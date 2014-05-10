#use "arith.ml";;
#use "testUtils.ml";;

prt_bool (no_mult (Int 42));;
prt_bool (no_mult (Plus (Int 42, Int 13)));;
prt_bool (no_mult (Mult(Int 3, Plus(Int 2, Int 1))));;
prt_bool (no_mult (Minus(Int 2, Negate(Int 4))));;
prt_bool (no_mult (Plus(Var "x", Var "y")));;
prt_bool (no_mult (Mult (Var "foo", Plus(Int 3, Var "baz"))));;
