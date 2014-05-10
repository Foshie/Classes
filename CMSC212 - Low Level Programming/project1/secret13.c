/*
 * CMSC 212, Spring 2010, Project #1
 * Secret test 13 (secret13.c)
 *
 * Tests shift_program() by shifting a program containing data as well as
 * instructions.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1
#define SZ 128

static int compare_words(Word word1, Word word2);

int compare_words(Word word1, Word word2) {
  int same= 1;

  if (word1.contents != word2.contents ||
      (word1.contents == DATA &&
       word1.value.data != word2.value.data) ||
      (word1.contents == INSTR &&
       (word1.value.instr.op != word2.value.instr.op ||
        word1.value.instr.r1 != word2.value.instr.r1 ||
        word1.value.instr.r2 != word2.value.instr.r2 ||
        word1.value.instr.r3 != word2.value.instr.r3 ||
        word1.value.instr.address != word2.value.instr.address ||
        word1.value.instr.imm != word2.value.instr.imm)))
      same= 0;

  return same;
}

int main() {
  Word mem[SZ]= {{0}};  /* initializes everything to zero */
  int i, correct= 1;

  /* not bothering to check the return value of these calls */
  init_word(&mem[0], INSTR, BEQ,  R1,  R2,  EMP, 50,  EMP, EMP);
  init_word(&mem[1], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 111);
  init_word(&mem[2], INSTR, JSR,  EMP, EMP, EMP, EMP, EMP, EMP);
  init_word(&mem[3], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 222);
  init_word(&mem[4], INSTR, LI,   EMP, EMP, EMP, EMP, 42,  EMP);
  init_word(&mem[5], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 333);
  init_word(&mem[6], INSTR, SW,   R7,  EMP, EMP, 124, EMP, EMP);
  init_word(&mem[7], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 444);

  /* not bothering to check the return value of this call */
  shift_program(mem, 0, 8, 20);

  /* call compare_words() to check that the first eight locations of mem
     have identical contents to locations 20..27 */
  for (i= 0; i < 8 && correct == 1; i++)
    correct= correct && compare_words(mem[i], mem[20 + i]);

  if (correct == 1)
    printf("Shifting a program with instructions and data worked right.\n");
  else printf("Shifting a program with instructions and data didn't work.\n");

  return 0;
}
