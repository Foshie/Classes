#use "arith.ml"

type cmd =
    Skip
  | Assign of string * expr
  | Seq of cmd * cmd
  | IfNonZero of expr * cmd * cmd
  | WhileNonZero of expr * cmd
  
let rec exec a c = match c with
	Skip -> a
  | Assign(str,e) -> (str, (eval a e))::a
  | Seq(c1, c2) -> exec (exec a c1) c2
  | IfNonZero(e1, c1, c2) -> 
	if (eval a e1) != 0 then	
		exec a c1
	else
		exec a c2	
  | WhileNonZero(e,c) -> 
	if (eval a e) = 0 then 
		a
	else
		exec (exec a c) (WhileNonZero(e,c))
  