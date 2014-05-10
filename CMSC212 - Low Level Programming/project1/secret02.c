/*
 * CMSC 212, Spring 2010, Project #1
 * Secret test 02 (secret02.c)
 *
 * Calls init_word() with a NULL pointer for word_ptr, and an invalid value
 * for type, both of which should cause it to have no effect.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1

int main() {
  Word word= {INSTR, {{INC, 1, 2, 3, 4, 5}}};
  int ret= 0;

  ret= init_word(NULL, INSTR, ADD, R6, R5, R4, EMP, EMP, EMP) ||
       init_word(&word, 9, ADD, R5, R4, R3, EMP, EMP, EMP);

  /* since the init_word() calls should have had no effect, word should
     still have its initial values, and both calls should have returned 0 */
  if (ret != 0 || word.contents != INSTR || word.value.instr.op != INC ||
      word.value.instr.r1 != 1 || word.value.instr.r2 != 2 ||
      word.value.instr.r3 != 3 || word.value.instr.address != 4 ||
      word.value.instr.imm != 5)
    printf("An invalid init_word() call unexpectedly had some effect.\n");
  else printf("The invalid init_word() calls did nothing as expected.\n");

  return 0;
}
