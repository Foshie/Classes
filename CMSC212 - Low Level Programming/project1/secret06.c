/*
 * CMSC 212, Spring 2010, Project #1
 * Secret test 06 (secret06.c)
 *
 * Tests shift_program()'s return value for values for new_start_loc that
 * are invalid (too large).
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1
#define SZ 128

int main() {
  Word mem[SZ];
  int ret= 0;

  /* not bothering to check the return value of these calls */
  init_word(&mem[0], INSTR, ADD,  R1,  R2,  R3,  EMP, EMP, EMP);
  init_word(&mem[1], INSTR, SUB,  R2,  R3,  R4,  EMP, EMP, EMP);
  init_word(&mem[2], INSTR, MUL,  R3,  R4,  R5,  EMP, EMP, EMP);
  init_word(&mem[3], INSTR, DIV,  R5,  R4,  R3,  EMP, EMP, EMP);
  init_word(&mem[4], INSTR, MOD,  R4,  R3,  R2,  EMP, EMP, EMP);

  ret= ret || shift_program(mem, 0, 5, SZ);
  ret= ret || shift_program(mem, 0, 5, SZ + 1);
  ret= ret || shift_program(mem, 0, 5, SZ + 2);

  if (ret != 0)
    printf("An invalid shift_program() call didn't return 0 as expected.\n");
  else printf("All invalid shift_program() calls returned 0 as expected.\n");

  return 0;
}
