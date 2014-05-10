#use "arith.ml";;
#use "testUtils.ml";;
#use "arithUtils.ml";;

prt_expr (subst (Plus(Var "v", Int 3)) [("foo", Int 4)]);;
prt_expr (subst (Mult(Var "foo", Plus(Int 3, Var "baz"))) [("foo", Int 4)]);;
prt_expr (subst (Plus(Var "v", Int 3)) [("v", Negate (Var "v"))]);;
prt_expr (subst (Mult(Var "foo", Plus(Int 3, Var "baz"))) [("v", Negate (Var "v"))]);;
