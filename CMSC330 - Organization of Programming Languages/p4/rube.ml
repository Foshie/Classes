open Ast

type value =
    VInt of int
  | VNil
  | VString of string
  | VObject of string * (string * value) list
    (* Invariant:  no field name appears twice in a VObject *)
  | VLoc of int

(*********************************************************************)

let rec output_expr o = function
  | EInt i -> Printf.fprintf o "%d" i
  | ENil -> Printf.fprintf o "nil"
  | ESelf -> Printf.fprintf o "self"
  | EString s -> Printf.fprintf o "\"%s\"" s
  | ELocal x -> output_string o x
  | EField x -> output_string o x
  | EIf (e1, e2, e3) ->
      Printf.fprintf o "if %a then %a else %a end" output_expr e1
	output_expr e2 output_expr e3
  | ESeq (e1, e2) -> Printf.fprintf o "%a; %a" output_expr e1 output_expr e2
  | EWrite (x, e) ->
      Printf.fprintf o "%s = (%a)" x output_expr e
  | EWriteField (x, e) ->
      Printf.fprintf o "%s = (%a)" x output_expr e
  | ENew x ->
      Printf.fprintf o "new %s" x
  | EInvoke (e, m, es) ->
      Printf.fprintf o "%a.%s(%a)" output_expr e m output_exprs es

and output_exprs o = function
    [] -> ()
  | [e] -> output_expr o e
  | e::es -> Printf.fprintf o "%a, %a" output_expr e output_exprs es

and output_strs o = function
    [] -> ()
  | [s] -> output_string o s
  | s::ss -> Printf.fprintf o "%a, %a" output_string s output_strs ss

and output_meth o ((name, args, body):meth) =
  Printf.fprintf o "  def %s(%a)\n    %a\n  end\n" name output_strs args output_expr body

and output_meths o = function
    [] -> ()
  | [m] -> Printf.fprintf o "%a" output_meth m
  | m::ms -> Printf.fprintf o "%a\n%a" output_meth m output_meths ms

and output_cls o ((name, super, meths):cls) =
  Printf.fprintf o "class %s < %s\n  %a\nend\n" name super output_meths meths

and output_clss o = function
    [] -> ()
  | [c] -> Printf.fprintf o "%a" output_cls c
  | c::cs -> Printf.fprintf o "%a\n%a" output_cls c output_clss cs

and print_program ((cs,e):prog) = match cs with
  | [] -> Printf.printf "%a\n" output_expr e
  | _ -> Printf.printf "%a\n%a\n" output_clss cs output_expr e

(*********************************************************************)

let rec print_fields o = function
  | [] -> ()
  | [f,v] -> Printf.fprintf o "%s=%a" f print_value v
  | (f,v)::fs -> Printf.fprintf o "%s=%a, %a" f print_value v print_fields fs

and print_value o = function
  | VInt n -> Printf.fprintf o "%d" n
  | VNil -> Printf.fprintf o "nil"
  | VString s -> Printf.fprintf o "%s" s
  | VObject (c, []) -> Printf.fprintf o "[%s]" c
  | VObject (c, fs) -> Printf.fprintf o "[%s %a]" c print_fields fs
  | VLoc n -> Printf.fprintf o "l%d" n

(* Local variable environment *)
type environment = (string * value) list

(* Heap *)
type heap = (int * value) list

let rec print_env o = function
    [] -> ()
  | [x,v] -> Printf.fprintf o "%s=%a" x print_value v
  | (x,v)::xs -> Printf.fprintf o "%s=%a\n%a" x print_value v print_env xs

let rec print_heap o = function
    [] -> ()
  | [l,v] -> Printf.fprintf o "l%d=%a" l print_value v
  | (l,v)::xs -> Printf.fprintf o "l%d=%a\n%a" l print_value v print_heap xs

(*********************************************************************)

(* PART 1 *)
(*#1*)
let rec check_args args = match args with
	[]->false
	|(h::t) ->	if List.mem h t then
					true
				else
					check_args t
let rec check_dup_mlist mlist = match mlist with 
	[]->false
	|(h::t)-> match h with 
				(_,args,_)-> if check_args args then
								true
							 else
								check_dup_mlist t

let rec check_dup_clist cls = match cls with
	[]-> false
	|(h::t)-> 	if (match h with
						(_,_, mlist)->	check_dup_mlist mlist)then 
					true
				else
					check_dup_clist t
	
let check_dup_params (p:prog):bool = match p with
	(cls, _) -> check_dup_clist cls

(*#2*******)
let rec unused_arg arg body = match body with
	ENil -> false
	| ESelf -> false
	| EInt (_)-> false
	| EString (_)-> false	
	| ELocal x -> 	if x = arg then
						true
					else
						false
	| EField x -> 	false
						
	| EIf (e1, e2, e3) -> (unused_arg arg e1) ||(unused_arg arg e2)||(unused_arg arg e3)
									
	| ESeq (e1, e2) -> (unused_arg arg e1) ||(unused_arg arg e2)
							
	| EWrite (x, e) -> if x = arg then
						 true
						else
							false
						 
	| EWriteField (x, e) -> false
							
	| ENew x -> false	
	| EInvoke (e, m, es) ->	if (unused_arg arg e) then
								true
							else 
								let rec un_inv lst = (match lst with
									[]->false
									|(h::t)-> if unused_arg arg h then
												true
											  else
												un_inv t
									) in un_inv es
							
let rec unused_h cname mname args body = match args with
	[]->[]
	|(h::t) -> if (unused_arg h body) = false then
				(cname, mname, h)::(unused_h cname mname t body)
				else
				unused_h cname mname t body

let rec unused_mlist cname mlist = match mlist with
	[]->[]
	|(h::t)->	match h with
					(m,args,bod) -> (unused_h cname m args bod)@(unused_mlist cname t)
				
let rec unused_clist cls = match cls with
	[]-> []
	|(h::t)->	match h with
					(c,_,meth) -> (unused_mlist c meth)@(unused_clist t)
				
let unused (p:prog):((string * string * string) list) = match p with
	(cls, _) -> unused_clist cls
(*#3*********************)

let rec rename_body x y body = match body with
	ENil -> ENil
	| ESelf -> ESelf
	| EInt (n)-> EInt(n)
	| EString (s)-> EString (s)
	| ELocal (var) -> if (var = x) then (ELocal y) else (ELocal var)
	| EField (var) -> (EField var)
	| EIf (e1, e2, e3) -> EIf((rename_body x y e1),(rename_body x y e2),(rename_body x y e3))
	| ESeq (e1, e2) -> ESeq((rename_body x y e1),(rename_body x y e2))
	| EWrite (var, e) -> if (var = x) then
							EWrite (y, (rename_body x y e))
						else
							EWrite (var, (rename_body x y e))
	| EWriteField (var, e) -> EWriteField (var,(rename_body x y e))
	| ENew var -> (ENew var)
	| EInvoke (e, m, es) ->	if (x = m) then
								EInvoke((rename_body x y e), y, (List.map (rename_body x y) es))
							else
								EInvoke((rename_body x y e), m, (List.map (rename_body x y) es))
			
let rec rename_args args x y = match args with
	[]->[]
	|(h::t) -> if (x = h) then
					y::(rename_args t x y)
			   else
					h::(rename_args t x y)
					
let rec rename_mlist mlist m x y = match mlist with
	[]->[]
	|((name, alist, body)::t)->if (m = name) then
								(name, (rename_args alist x y), (rename_body x y body))::t
						      else
								(name, alist, body)::(rename_mlist t m x y)
let rec rename_c cls c m x y = match cls with
	[]->[]
	|((name, sname, mlist)::t)->if (c = name) then
									(name, sname, (rename_mlist mlist m x y))::t
								else
									(name, sname, mlist)::(rename_c t c m x y)
								
let rename (p:prog) (c:string) (m:string) (x:string) (y:string):prog = match p with
	(cls, expr) -> ((rename_c cls c m x y),expr)
		

(*********************************************************************)

(* PART 2 *)
(*#1*)
let rec dup_clist cls lst= match cls with
	[]-> false
	|(h::t)-> match h with
		(cname,_,_) -> if List.mem cname lst then 
							true
						else
							(dup_clist t (cname::lst))
let check_dup_classes (p:prog):bool =match p with
	(cls, _) -> dup_clist cls []

(*#2*)

let superclass_of (p:prog) (c:string):string = 
	if (c = "Object") then
		"Object"
	else
		(match p with
		(clst, _)-> let rec super_h lst = (match lst with
			[]-> raise Not_found
			|(h::t)-> match h with
				(cname, super,_)-> if (cname = c) then
										super
									else
										super_h t
			) in super_h clst
		)

(*#3*)
let rec map_lst clst= match clst with
	[]->["Object"]
	|(h::t)-> match h with
		(name, _,_)-> name::(map_lst t)
							
let rec part_a clst fulllst= match clst with
	[]-> true
	|((_, super, _)::t)-> if ((List.mem super fulllst) = false) then false
						  else
							part_a t fulllst

let rec check_super p name vis = 
	if ( name = "Object") then
		false
	else (
		if (List.mem name vis) then
			true
		else
			check_super p (superclass_of p name) (name::vis)
		)
let rec part_b clst p = match clst with
	[]-> true
	|((name,super,_)::t)-> if (check_super p super [name]) then
				false
			  else
				part_b t p

let wf_inheritance (p:prog):bool =match p with 
	(cls, _) -> if((part_a cls (map_lst cls)) && (part_b cls p)) then
					true
				else
					false
  
(*#4*)

let lookup (p:prog) (c:string) (m:string):meth = match p with
	(clst, _) -> 
		let rec clas curr lst name = (match curr with
		[]-> raise Not_found
		|((cname,super,meths)::t)-> 
			if (cname = c) then
			(
				
				let rec met mlst = (match mlst with
					[]-> if (super = "Object") then raise Not_found
						else
							clas lst lst super
					|((mname,args,body)::tail)->
						if (mname = m) then
							(mname,args,body)
						else
							met tail
				) in met meths	
			)
			else
				clas t lst name
	) in clas clst clst c
(*********************************************************************)

(* PART 3 *)

exception Eval_error

let a_new a b = (a,b)
let rec map_tuple aList bList = match aList with
	[]-> []
	|(a::t1)->( match bList with
		(b::t2)-> (a,b)::(map_tuple t1 t2))
	
let rec get_val vlist = match vlist with
	[]->[]
	|((_,_,v)::t)-> v::(get_val t)
	
let rec eval_expr (p, expr, a, h)= match expr with
	EInt (n) -> (a, h, VInt(n))
	| ENil-> (a, h, VNil)
	| EString (s)-> (a, h, VString(s))
	| ESelf -> (a, h,(List.assoc "self" a))
	
	| ELocal var -> if (List.mem_assoc var a) then
						(a, h, (List.assoc var a))
					  else
						(raise Eval_error)
	| EField (var) -> (match (List.assoc "self" a) with
		VLoc l -> (match (List.assoc l h) with
			VObject(_, id)-> if (List.mem_assoc var id) then
									(a, h, (List.assoc var id))
								else
									(a, h, VNil)))
	| EIf (e1, e2, e3) -> (match (eval_expr(p, e1, a, h)) with
		(a1, h1, v)-> if (v = VNil) then
						eval_expr(p, e3, a1, h1)
					  else
						eval_expr(p, e2, a1, h1))
	| ESeq (e1, e2) -> (match eval_expr(p, e1, a, h) with
		(a1, h1, v)-> eval_expr(p, e2, a1, h1))
	| EWrite (var, e) -> (match eval_expr(p, e, a, h) with
		(a1, h1, v) -> if var = "self" then
							raise Eval_error
					   else
							((var, v)::a1, h1, v))
	| EWriteField (var, e) -> (match eval_expr(p, e, a, h) with
		(a1, h1, v)-> (match (List.assoc "self" a) with
			VLoc l -> (match (List.assoc l h1) with
				VObject(s,flist)-> (a1, ((l,VObject(s,((var, v)::flist)))::h1), v))))
	| ENew var -> (if (List.mem var (map_lst (match p with (clst,_)-> clst))) then
				(	let rec fresh_check loc = 
						if (List.mem_assoc loc h) then
							fresh_check (loc+1)
						else
							(a,((loc, VObject(var, []))::h), VLoc loc)
					in fresh_check 0
				)
				  else
					raise Eval_error)
	| EInvoke (e, m, es) ->	(
		if (m = "send") then(
			match es with 
			(head::t)-> (
				match eval_expr(p, head, a, h) with
					(a1, h1, VString str)-> eval_expr(p, EInvoke(e, str, t), a1, h1)
			)
						
		)else(
		  match eval_expr(p, e, a, h) with
			(aZ, hZ, VNil)->(
								if (m = "to_s") then
									(aZ, hZ, VString "nil")
								else
									raise Eval_error
							)
			|(a1, h1, VInt n1)->(
									if (m = "+" || m= "-" || m = "*" || m = "/") then (
										match es with (head::t)-> (
											match (eval_expr(p, head, a1, h1)) with
												(a2, h2, VInt n2)-> (
													if (m = "+") then
														(a2, h2, VInt (n1+n2))
													else if (m = "-") then
														(a2, h2, VInt(n1-n2))
													else if (m = "*") then
														(a2, h2, VInt(n1*n2))
													else 
														(a2, h2, VInt(n1/n2))
												)
											)
									)else if (m="equal?") then(
										match es with (head::t)-> (
											match (eval_expr(p, head, a1, h1)) with
												(a2, h2, VInt n2)-> (
													if (n1 = n2) then
														(a2, h2, VInt 1)
													else
														(a2, h2, VNil)
												)
										)
									)else if (m = "to_s") then
										(a1, h1, VString (Pervasives.string_of_int n1))
									else
										raise Eval_error
								)
			|(aZ, hZ, VString str)-> (
				if (m = "print") then(
					print_s str;
					(aZ, hZ, VNil)
				)
				else
					raise Eval_error
			)
			|(aZ, hZ, VLoc l)-> (
				if (m = "class_of") then(
					match (List.assoc l hZ) with 
						VObject(ids, _)-> (aZ, hZ, VString ids)
				)
				else(
				  match (List.assoc l hZ) with 
					VObject(ids, _)-> (
						let rec eval_list an hn elist= (
						  match elist with
							[]->[]
							|(h::t)-> (match (eval_expr(p, h, an, hn)) with
								(aNew, hNew, v)-> (aNew, hNew, v)::(eval_list aNew hNew t))
						) in let vals = (eval_list aZ hZ es) in (
							  match (lookup p ids m) with
								(_,args, ex)-> if ((List.length vals) = (List.length args)) then
													(match List.rev(vals) with
														((aN,hN,_)::t)->        			
															match (eval_expr(
																		p, 
																		ex,
																		("self",VLoc l)::(map_tuple args (get_val vals)), 
																		hN
																		))	 with
																(_,hDPrime, newV)-> (aN, hDPrime, newV)
														)
												else
													raise Eval_error
							)
					)
				  
				)
			)
		)
	)
let eval_prog (p:prog):value = (match p with
	(_, expr) -> (match eval_expr (p, expr, [("self", VLoc 0)],[(0, VObject("Object", []))]) with
		(_,_, v)-> v))
