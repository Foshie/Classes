/*
 * CMSC 212, Spring 2030, Project #1
 * Secret test 04 (secret04.c)
 *
 * Tests print_program() with values for size that are invalid (too small).
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

  ret= ret || print_program(mem, -1, 3);
  ret= ret || print_program(mem, -2, 3);
  if (ret != 0)
    printf("An invalid print_program() call didn't return 0 as expected.\n");
  else printf("Both invalid print_program() calls returned 0 as expected.\n");

  return 0;
}
