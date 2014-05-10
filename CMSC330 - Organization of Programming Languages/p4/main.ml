open Ast

let parse_file name =
  let chan = open_in name in
  let lexbuf = Lexing.from_channel chan in
  let (p:prog) = Parser.main Lexer.token lexbuf in
    close_in chan;
    p

let do_unparse () =
  let p = parse_file Sys.argv.(2) in
    Rube.print_program p

let do_check_dup_params () =
  let p = parse_file Sys.argv.(2) in
  let r = Rube.check_dup_params p in
    Printf.printf "%b\n" r

let rec print_unused o = function
    [] -> ()
  | [c,m,x] -> Printf.fprintf o "(%s, %s, %s)" c m x
  | (c,m,x)::tl -> Printf.fprintf o "(%s, %s, %s); %a" c m x print_unused tl

let do_unused () =
  let p = parse_file Sys.argv.(2) in
  let r = Rube.unused p in
    Printf.printf "[%a]" print_unused r

let do_rename () =
  let p = parse_file Sys.argv.(2) in
  let c = Sys.argv.(3) in
  let m = Sys.argv.(4) in
  let x = Sys.argv.(5) in
  let y = Sys.argv.(6) in
  let p' = Rube.rename p c m x y in
    Rube.print_program p'

let do_check_dup_classes () =
  let p = parse_file Sys.argv.(2) in
  let r = Rube.check_dup_classes p in
    Printf.printf "%b\n" r

let do_superclass_of () =
  let p = parse_file Sys.argv.(2) in
  let c = Sys.argv.(3) in
  let r = Rube.superclass_of p c in
    Printf.printf "%s\n" r

let do_wf_inheritance () =
  let p = parse_file Sys.argv.(2) in
  let r = Rube.wf_inheritance p in
    Printf.printf "%b\n" r

let do_lookup () =
  let p = parse_file Sys.argv.(2) in
  let c = Sys.argv.(3) in
  let m = Sys.argv.(4) in
  let r = Rube.lookup p c m in
    Printf.printf "%a" Rube.output_meth r

let do_eval_prog () =
  let p = parse_file Sys.argv.(2) in
  let r = Rube.eval_prog p in
    Printf.printf "%a" Rube.print_value r

let commands = [
  "unparse", do_unparse;
  "check_dup_params", do_check_dup_params;
  "unused", do_unused;
  "rename", do_rename;
  "check_dup_classes", do_check_dup_classes;
  "superclass_of", do_superclass_of;
  "wf_inheritance", do_wf_inheritance;
  "lookup", do_lookup;
  "eval_prog", do_eval_prog;
]

;;

(List.assoc (Sys.argv.(1)) commands) ()
