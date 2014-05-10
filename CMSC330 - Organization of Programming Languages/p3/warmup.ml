let rec prod l = match l with
	[] -> 1
	| (x::xs) -> x * prod xs
	
let rec add_tail l e = match l with
	[] -> e::[]
	| (x::xs) -> x :: add_tail xs e
	
let rec fill x n = match n with 
	0 -> []
	| num -> x :: fill x (num-1)
	
let rec rindex l e = match l with
	[] -> -1
	| h::t -> let i = rindex t e in
				if i != -1 then
					i+1
				else( 
					if h =e then
						0
					else
						-1
				)
		
let rec even_elts l = match l with
	[] -> []
	| x::xs::t -> x::even_elts t
	| x::[] -> x::[]
	
let rec sublist_h n m l i = match l with
	[] -> []
	| h::t ->	if i >= m then
					(if i = m then
						h :: []
					else
						[])
				else
					h::sublist_h n m t (i+1)
let rec sublist_i n m l i = match l with
	[] -> []
	| h::t -> 	if i = n then 
					h::sublist_h n m t (i+1)
				else
					sublist_i n m t (i+1)

let sublist n m l = sublist_i n m l 0

let rec length l = match l with
	[] -> 0
	|h::t -> 1 + length t

let rec rotate_h n l = 

	let len = length l in
	if n != 0 && len > 1 then
		let a = sublist 0 (len-2) l in
		let b = sublist (len-1) (len-1) l in
		match b with
			[]->[]
			|h::[] -> rotate_h (n-1) (h::a)
	else 
		l
let rotate n l =
		rotate_h n l
	
let rec unzip_h l left right = match l with
	[] -> (left, right)
	|(a,b)::t -> unzip_h t (add_tail left a) (add_tail right b)
	
let unzip l = unzip_h l [] []

let rec app_int f m n = 
	if m <= n then
		(f m)::app_int f (m+1) n
	else
		[]