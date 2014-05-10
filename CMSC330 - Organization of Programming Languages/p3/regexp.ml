(* Put your solutions to part 2 in this file *)
(* Do *not* change the following data type *)
type regexp =
    REEpsilon
  | REConst of char
  | REStar of regexp
  | REUnion of regexp * regexp
  | REConcat of regexp * regexp
 
let rec red l = match l with
	[] -> []
	|h::t -> 
		if (List.mem h t) then
			red t
		else
			h::(red t)

let rec check e = match e with
	REEpsilon(_)-> true
	|REConst(_) -> false
	|REUnion(a, b) -> if (check a) then true
					  else check b
	|REStar(_) -> true
	|REConcat(a, b) -> if (check a) then check b
					   else false
			
let concat e2 (a, e) =
	(a, REConcat(e, e2))

let star f (a, prime) = 
	(a, REConcat(prime, REStar(f)))
	
let rec trans e = match e with
	REEpsilon(_)-> []
	|REConst(a)-> [(a, REEpsilon)]
	|REUnion(e1, e2)-> 
		let a = trans(e1) in
		let b = trans(e2) in
		red (a @ b)
	|REConcat(e1, e2)->
		let a = List.map (concat e2) (trans e1) in
		if (check e1) then
			red (a @ (trans e2))
		else
			red a
	|REStar(f)->
		red (List.map (star f) (trans f))
		