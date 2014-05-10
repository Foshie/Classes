type expr =
    Int of int
  | Negate of expr
  | Plus of expr * expr
  | Minus of expr * expr
  | Mult of expr * expr
  | Var of string

type assignment = (string * int) list

let rec red l = match l with
	[] -> []
	|h::t -> 
		if (List.mem h t) then
			red t
		else
			h::(red t)

let rec no_mult e = match e with
	Mult(_,_) -> false
	|Int(_) -> true
	|Negate(e) -> no_mult e
	|Plus(a,b) -> if (no_mult a) then no_mult b else false
	|Minus(a,b) -> if (no_mult a) then no_mult b else false
	|Var(_) -> true
	
let rec vars_of e = match e with
	Int(_) -> []
	| Negate(e) -> red (vars_of e)
	| Plus(e1,e2) -> red ((vars_of e1) @ (vars_of e2))
	| Minus(e1,e2) -> red ((vars_of e1)@(vars_of e2))
	| Mult(e1,e2) -> red ((vars_of e1)@(vars_of e2))
	| Var(str)-> str::[]
	
let rec eval l e = match e with
	Int(a) -> a
	| Var(str)-> List.assoc str l
	| Negate(a) -> -1 * (eval l a)
	| Plus(e1,e2) -> (eval l e1) + (eval l e2)
	| Minus(e1,e2) -> (eval l e1) - (eval l e2)
	| Mult(e1,e2) -> (eval l e1) * (eval l e2)

let rec subst_h str s = match s with
	[] -> Var str
	|(a,b)::t -> 
		if a = str then
			b
		else
			subst_h str t

let rec subst e s = match e with
	Int(a) -> Int a
	| Negate(a) -> Negate(subst a s)
	| Plus(e1,e2) -> Plus((subst e1 s), (subst e2 s))
	| Minus(e1,e2) -> Minus((subst e1 s), (subst e2 s))
	| Mult(e1,e2) -> Mult((subst e1 s), (subst e2 s))
	| Var(str)-> subst_h str s 

	