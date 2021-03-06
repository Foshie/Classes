#use "regexp.ml";;
#use "testUtils.ml";;
#use "regexpUtils.ml";;

prt_trans (trans (REConst 'o'));;
prt_trans (trans (REStar (REConst 'l')));;
prt_trans (trans (REConcat (REStar (REConst 'l'), REConst 'o')));;
prt_trans (trans (REConcat (REStar (REConst 'o'), REConst 'l')));;
prt_trans (trans (REConcat (REConst 'o', REConcat (REStar (REConst 'l'), REConst 'o'))));;
prt_trans (trans (REConcat (REConst 'l', REConcat (REStar (REConst 'o'), REConst 'o'))));;
prt_trans (trans (REUnion (REStar (REConst 'o'), REStar (REConst 'l'))));;
prt_trans (trans (REUnion (REConcat (REConst 'o', REStar (REConst 'l')), REConcat (REConst 'l', REStar (REConst 'o')))));;
prt_trans (trans (REUnion (REConcat (REStar (REConst 'l'), REConcat (REConst 'o', REStar (REConst 'l'))), REStar (REConst 'l'))));;
prt_trans (trans (REUnion (REConcat (REStar (REConst 'o'), REConst 'l'), REConcat (REConst 'o', REConst 'l'))));;
prt_trans (trans (REUnion (REConcat (REConst 'o', REConcat (REConst 'o', REConst 'o')), REConcat (REConst 'l', REConcat (REConst 'l', REConst 'l')))));;
prt_trans (trans (REUnion (REConcat (REConst 'o', REConcat (REConst 'l', REConcat (REConst 'o', REConst 'l'))), REConcat (REConst 'l', REConcat (REConst 'o', REConcat (REConst 'l', REConst 'o'))))));;
prt_trans (trans (REUnion (REConcat (REConst 'l', REConcat (REConst 'o', REConst 'o')), REUnion (REConcat (REConst 'o', REConcat (REConst 'l', REConst 'o')), REConcat (REConst 'o', REConcat (REConst 'o', REConst 'l'))))));;
prt_trans (trans (REUnion (REConcat (REConst 'l', REConcat (REConst 'l', REConst 'o')), REUnion (REConcat (REConst 'l', REConcat (REConst 'o', REConst 'l')), REConcat (REConst 'o', REConcat (REConst 'l', REConst 'l'))))));;
prt_trans (trans (REUnion (REConcat (REConst 'l', REConcat (REConst 'l', REConcat (REConst 'o', REConst 'o'))), REUnion (REConcat (REConst 'o', REConcat (REConst 'o', REConcat (REConst 'l', REConst 'l'))), REUnion (REConcat (REConst 'o', REConcat (REConst 'l', REConcat (REConst 'l', REConst 'o'))), REConcat (REConst 'l', REConcat (REConst 'o', REConcat (REConst 'o', REConst 'l'))))))));;
prt_trans (trans (REUnion (REConst 'o', REUnion (REConst 'l', REUnion (REConcat (REConst 'o', REConst 'o'), REConcat (REConst 'l', REConst 'l'))))));;
prt_trans (trans (REUnion (REConcat (REConst 'o', REConcat (REConst 'o', REConst 'o')), REUnion (REConcat (REConst 'l', REConcat (REConst 'l', REConst 'l')), REUnion (REConcat (REConst 'o', REConcat (REConst 'o', REConcat (REConst 'o', REConcat (REConst 'o', REConst 'o')))), REConcat (REConst 'l', REConcat (REConst 'l', REConcat (REConst 'l', REConcat (REConst 'l', REConst 'l')))))))));;
prt_trans (trans (REUnion (REConst 'l', REUnion (REConcat (REConst 'l', REConst 'l'), REUnion (REConcat (REConst 'l', REConcat (REConst 'l', REConst 'l')), REConcat (REConst 'l', REConcat (REConst 'l', REConcat (REConst 'l', REConst 'l'))))))));;
