type token =
  | INT of (int)
  | STR of (string)
  | ID of (string)
  | FID of (string)
  | CLASS
  | IF
  | THEN
  | ELSE
  | DEF
  | END
  | NEW
  | NIL
  | LT
  | LP
  | RP
  | COMMA
  | SEMI
  | DOT
  | EQ
  | EOF
  | SELF
  | BEGIN
  | INHERITS

val main :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> Ast.prog
