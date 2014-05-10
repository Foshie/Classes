#use "regexp.ml";;
#use "testUtils.ml";;

let prec r = match r with
    REEpsilon -> 3
  | REConst _ -> 3
  | REStar _ -> 2
  | REConcat _ -> 1
  | REUnion _ -> 0
;;

let rec string_of_regexp r =
  let p = prec r in
  let add_paren rr =
    let pp = prec rr in
    if pp >= p then string_of_regexp rr else "(" ^ string_of_regexp rr ^ ")"
  in match r with
      REEpsilon -> "()"
    | REConst c -> String.make 1 c
    | REUnion (r1, r2) -> add_paren r1 ^ "|" ^ add_paren r2
    | REConcat (r1, r2) -> add_paren r1 ^ add_paren r2
    | REStar r1 -> add_paren r1 ^ "*"
;;

let string_of_trans l =
  let compare_trans (c1,r1) (c2, r2) =
    let cmp = compare c1 c2 in
      if cmp = 0 then compare (string_of_regexp r1) (string_of_regexp r2) else cmp
  in
  let rec helper ll = match ll with
      [] -> ""
    | (c,r)::[] -> "(" ^ (String.make 1 c) ^ "," ^ string_of_regexp r ^ ")"
    | (c,r)::xs -> "(" ^ (String.make 1 c) ^ "," ^ string_of_regexp r ^ ")," ^ helper xs
  in "[" ^ helper (List.sort compare_trans l) ^ "]"
  (*in "[" ^ helper l ^ "]"*)
;;

let prt_regexp r = print_endline (string_of_regexp r);;

let rec prt_trans l = print_endline (string_of_trans l);;

let prt_bool b = print_endline (string_of_bool b);;

