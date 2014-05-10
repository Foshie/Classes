{
 open Parser
 exception Eof
}
rule token = parse
  [' ' '\t' '\n']	{ token lexbuf }
| "class" { CLASS }
| "if" { IF }
| "then" { THEN }
| "else" { ELSE }
| "end" { END }
| "def" { DEF }
| "nil" { NIL }
| "self" { SELF }
| "begin" { BEGIN }
| "new" { NEW }
| '<' { INHERITS }
| '(' { LP }
| ')' { RP }
| ',' { COMMA }
| ';' { SEMI }
| '.' { DOT }
| '=' { EQ }
| '"' [^'"']* '"' as lxm { STR(String.sub lxm 1 ((String.length lxm) - 2)) }
| ['0'-'9']+ as lxm { INT(int_of_string lxm) }
| ['A'-'Z''a'-'z''+''-''*''/''_''!''?']+ as lxm { ID(lxm) }
| '@'['A'-'Z''a'-'z''+''-''*''/''_''!''?']+ as lxm { FID(lxm) }
| eof { EOF }
| _ as lxm { Printf.printf "Illegal character %c" lxm; failwith "Bad input" }

