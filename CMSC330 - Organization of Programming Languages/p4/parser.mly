%{
  open Ast
%}

%token <int> INT
%token <string> STR ID FID
%token CLASS IF THEN ELSE DEF END NEW NIL
%token LT LP RP COMMA SEMI DOT EQ EOF SELF BEGIN INHERITS
%start main
%type <Ast.expr> expr exprs
%type <Ast.expr list> params
%type <string list> ids
%type <Ast.meth> meth
%type <Ast.meth list> meths
%type <Ast.cls> cls
%type <Ast.cls list> clss
%type <Ast.prog> main
%right SEMI
%right EQ
%nonassoc DOT
%%
main:
 clss exprs EOF { ($1, $2) }
;
clss:
  { [] }
| cls clss { $1::$2 }
cls:
  CLASS ID INHERITS ID BEGIN meths END { ($2, $4, $6) }
meths:
  { [] }
| meth meths { $1::$2 }
;
meth:
  DEF ID LP ids RP exprs END { ($2, $4, $6) }
;
ids:
  { [] }
| ID  { [$1] }
| ID COMMA ids { $1::$3 }
;
exprs:
  expr { $1 }
| expr SEMI exprs { ESeq($1, $3) }
;
expr:
| INT { EInt $1 }
| NIL { ENil }
| SELF { ESelf }
| STR { EString $1 }
| ID { ELocal $1 }
| FID { EField $1 }
| IF expr THEN expr ELSE expr END { EIf($2, $4, $6) }
| ID EQ expr { EWrite($1, $3) }
| FID EQ expr { EWriteField($1, $3) }
| expr DOT ID LP params RP { EInvoke($1, $3, $5) }
| NEW ID { ENew $2 }
| LP exprs RP { $2 }
;
params:
  { [] }
| expr { [$1] }
| expr COMMA params { $1::$3 }
