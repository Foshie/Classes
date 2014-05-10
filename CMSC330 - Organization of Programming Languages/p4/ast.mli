type expr =
    EInt of int
  | ENil
  | ESelf
  | EString of string
  | ELocal of string    (* Read a local variable *)
  | EField of string    (* Read a field *)
  | EIf of expr * expr * expr
  | ESeq of expr * expr
  | EWrite of string * expr  (* Write a local variable *)
  | EWriteField of string * expr  (* Write a field *)
  | ENew of string
  | EInvoke of expr * string * (expr list)

(*  meth name * arg name list * method body *)
type meth = string * string list * expr

(* class name * superclass name * methods *)
type cls = string * string * meth list

(* classes * top-level expression *)
type prog = cls list * expr
