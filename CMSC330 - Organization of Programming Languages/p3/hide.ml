(* Hide standard Array.*, List.*, Pervasives.(@)  *)

exception DontUseThis;;

module type ARRAY =
sig
  val length : 'a array -> int
  val get : 'a array -> int -> 'a
  val set : 'a array -> int -> 'a -> unit
  val make : int -> 'a -> 'a array
  val create : int -> 'a -> 'a array
  val init : int -> (int -> 'a) -> 'a array
  val make_matrix : int -> int -> 'a -> 'a array array
  val create_matrix : int -> int -> 'a -> 'a array array
  val append : 'a array -> 'a array -> 'a array
  val concat : 'a array list -> 'a array
  val sub : 'a array -> int -> int -> 'a array
  val copy : 'a array -> 'a array
  val fill : 'a array -> int -> int -> 'a -> unit
  val blit : 'a array -> int -> 'a array -> int -> int -> unit
  val to_list : 'a array -> 'a list
  val of_list : 'a list -> 'a array
  val iter : ('a -> unit) -> 'a array -> unit
  val map : ('a -> 'b) -> 'a array -> 'b array
  val iteri : (int -> 'a -> unit) -> 'a array -> unit
  val mapi : (int -> 'a -> 'b) -> 'a array -> 'b array
  val fold_left : ('a -> 'b -> 'a) -> 'a -> 'b array -> 'a
  val fold_right : ('b -> 'a -> 'a) -> 'b array -> 'a -> 'a
  val sort : ('a -> 'a -> int) -> 'a array -> unit
  val stable_sort : ('a -> 'a -> int) -> 'a array -> unit
  val fast_sort : ('a -> 'a -> int) -> 'a array -> unit
  val unsafe_get : 'a array -> int -> 'a
  val unsafe_set : 'a array -> int -> 'a -> unit
end

module Array : ARRAY =
struct
  let length _ = raise DontUseThis;;
  let get _ = raise DontUseThis;;
  let set _ = raise DontUseThis;;
  let make _ = raise DontUseThis;;
  let create _ = raise DontUseThis;;
  let init _ = raise DontUseThis;;
  let make_matrix _ = raise DontUseThis;;
  let create_matrix _ = raise DontUseThis;;
  let append _ = raise DontUseThis;;
  let concat _ = raise DontUseThis;;
  let sub _ = raise DontUseThis;;
  let copy _ = raise DontUseThis;;
  let fill _ = raise DontUseThis;;
  let blit _ = raise DontUseThis;;
  let to_list _ = raise DontUseThis;;
  let of_list _ = raise DontUseThis;;
  let iter _ = raise DontUseThis;;
  let map _ = raise DontUseThis;;
  let iteri _ = raise DontUseThis;;
  let mapi _ = raise DontUseThis;;
  let fold_left _ = raise DontUseThis;;
  let fold_right _ = raise DontUseThis;;
  let sort _ = raise DontUseThis;;
  let stable_sort _ = raise DontUseThis;;
  let fast_sort _ = raise DontUseThis;;
  let unsafe_get _ = raise DontUseThis;;
  let unsafe_set _ = raise DontUseThis;;
end

module type LIST =
sig
  val length : 'a list -> int
  val hd : 'a list -> 'a
  val tl : 'a list -> 'a list
  val nth : 'a list -> int -> 'a
  val rev : 'a list -> 'a list
  val append : 'a list -> 'a list -> 'a list
  val rev_append : 'a list -> 'a list -> 'a list
  val concat : 'a list list -> 'a list
  val flatten : 'a list list -> 'a list
  val iter : ('a -> unit) -> 'a list -> unit
  val map : ('a -> 'b) -> 'a list -> 'b list
  val rev_map : ('a -> 'b) -> 'a list -> 'b list
  val fold_left : ('a -> 'b -> 'a) -> 'a -> 'b list -> 'a
  val fold_right : ('a -> 'b -> 'b) -> 'a list -> 'b -> 'b
  val iter2 : ('a -> 'b -> unit) -> 'a list -> 'b list -> unit
  val map2 : ('a -> 'b -> 'c) -> 'a list -> 'b list -> 'c list
  val rev_map2 : ('a -> 'b -> 'c) -> 'a list -> 'b list -> 'c list
  val fold_left2 : ('a -> 'b -> 'c -> 'a) -> 'a -> 'b list -> 'c list -> 'a
  val fold_right2 : ('a -> 'b -> 'c -> 'c) -> 'a list -> 'b list -> 'c -> 'c
  val for_all : ('a -> bool) -> 'a list -> bool
  val exists : ('a -> bool) -> 'a list -> bool
  val for_all2 : ('a -> 'b -> bool) -> 'a list -> 'b list -> bool
  val exists2 : ('a -> 'b -> bool) -> 'a list -> 'b list -> bool
  val mem : 'a -> 'a list -> bool
  val memq : 'a -> 'a list -> bool
  val find : ('a -> bool) -> 'a list -> 'a
  val filter : ('a -> bool) -> 'a list -> 'a list
  val find_all : ('a -> bool) -> 'a list -> 'a list
  val partition : ('a -> bool) -> 'a list -> 'a list * 'a list
  val assoc : 'a -> ('a * 'b) list -> 'b
  val assq : 'a -> ('a * 'b) list -> 'b
  val mem_assoc : 'a -> ('a * 'b) list -> bool
  val mem_assq : 'a -> ('a * 'b) list -> bool
  val remove_assoc : 'a -> ('a * 'b) list -> ('a * 'b) list
  val remove_assq : 'a -> ('a * 'b) list -> ('a * 'b) list
  val split : ('a * 'b) list -> 'a list * 'b list
  val combine : 'a list -> 'b list -> ('a * 'b) list
  val sort : ('a -> 'a -> int) -> 'a list -> 'a list
  val stable_sort : ('a -> 'a -> int) -> 'a list -> 'a list
  val fast_sort : ('a -> 'a -> int) -> 'a list -> 'a list
  val merge : ('a -> 'a -> int) -> 'a list -> 'a list -> 'a list
end


module List : LIST =
struct
  let length _ = raise DontUseThis;;
  let hd _ = raise DontUseThis;;
  let tl _ = raise DontUseThis;;
  let nth _ = raise DontUseThis;;
  let rev _ = raise DontUseThis;;
  let append _ = raise DontUseThis;;
  let rev_append _ = raise DontUseThis;;
  let concat _ = raise DontUseThis;;
  let flatten _ = raise DontUseThis;;
  let iter _ = raise DontUseThis;;
  let map _ = raise DontUseThis;;
  let rev_map _ = raise DontUseThis;;
  let fold_left _ = raise DontUseThis;;
  let fold_right _ = raise DontUseThis;;
  let iter2 _ = raise DontUseThis;;
  let map2 _ = raise DontUseThis;;
  let rev_map2 _ = raise DontUseThis;;
  let fold_left2 _ = raise DontUseThis;;
  let fold_right2 _ = raise DontUseThis;;
  let for_all _ = raise DontUseThis;;
  let exists _ = raise DontUseThis;;
  let for_all2 _ = raise DontUseThis;;
  let exists2 _ = raise DontUseThis;;
  let mem _ = raise DontUseThis;;
  let memq _ = raise DontUseThis;;
  let find _ = raise DontUseThis;;
  let filter _ = raise DontUseThis;;
  let find_all _ = raise DontUseThis;;
  let partition _ = raise DontUseThis;;
  let assoc _ = raise DontUseThis;;
  let assq _ = raise DontUseThis;;
  let mem_assoc _ = raise DontUseThis;;
  let mem_assq _ = raise DontUseThis;;
  let remove_assoc _ = raise DontUseThis;;
  let remove_assq _ = raise DontUseThis;;
  let split _ = raise DontUseThis;;
  let combine _ = raise DontUseThis;;
  let sort _ = raise DontUseThis;;
  let stable_sort _ = raise DontUseThis;;
  let fast_sort _ = raise DontUseThis;;
  let merge _ = raise DontUseThis;;
end

let (@) _ = raise DontUseThis;;
