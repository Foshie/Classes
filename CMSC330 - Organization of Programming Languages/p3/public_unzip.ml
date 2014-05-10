#use "testUtils.ml";;
#use "hide.ml";;
#use "warmup.ml";;

let (fst, snd) = unzip [] in prt_int_list fst; prt_int_list snd;;
let (fst, snd) = unzip [(0, 1)] in prt_int_list fst; prt_int_list snd;;
let (fst, snd) = unzip [(0, 2);(1, 3)] in prt_int_list fst; prt_int_list snd;;
let (fst, snd) = unzip [(0, 3);(1, 4);(2, 5)] in prt_int_list fst; prt_int_list snd;;
let (fst, snd) = unzip [(0, 4);(1, 5);(2, 6);(3, 7)] in prt_int_list fst; prt_int_list snd;;
let (fst, snd) = unzip [(0, 5);(1, 6);(2, 7);(3, 8);(4, 9)] in prt_int_list fst; prt_int_list snd;;
let (fst, snd) = unzip [(0, 6);(1, 7);(2, 8);(3, 9);(4, 10);(5, 11)] in prt_int_list fst; prt_int_list snd;;
let (fst, snd) = unzip [(0, 7);(1, 8);(2, 9);(3, 10);(4, 11);(5, 12);(6, 13)] in prt_int_list fst; prt_int_list snd;;
let (fst, snd) = unzip [(0, 8);(1, 9);(2, 10);(3, 11);(4, 12);(5, 13);(6, 14);(7, 15)] in prt_int_list fst; prt_int_list snd;;
let (fst, snd) = unzip [(0, 9);(1, 10);(2, 11);(3, 12);(4, 13);(5, 14);(6, 15);(7, 16);(8, 17)] in prt_int_list fst; prt_int_list snd;;
