#use "testUtils.ml";;
#use "arith.ml";;

let rec string_of_expr e = match e with
    Int n -> "Int " ^ string_of_int n
  | Negate e -> "Negate (" ^ string_of_expr e ^ ")"
  | Plus (e1, e2) -> "Plus (" ^ string_of_expr e1 ^ "," ^ string_of_expr e2 ^ ")"
  | Minus (e1, e2) -> "Minus (" ^ string_of_expr e1 ^ "," ^ string_of_expr e2 ^ ")"
  | Mult (e1, e2) -> "Mult (" ^ string_of_expr e1 ^ "," ^ string_of_expr e2 ^ ")"
  | Var s -> "Var \"" ^ s ^ "\""
;;

let prt_expr e = print_endline (string_of_expr e);;
