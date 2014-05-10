/*
 * CMSC 212, Spring 2030, Project #1
 * Secret test 05 (secret05.c)
 *
 * Tests print_program() passing in 0 for size, which is valid but should
 * print nothing.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1
#define SZ 128

int main() {
  Word mem[SZ];
  int ret= 1;

  /* not bothering to check the return value of these calls */
  init_word(&mem[0], INSTR, ADD,  R1,  R2,  R3,  EMP, EMP, EMP);
  init_word(&mem[1], INSTR, SUB,  R2,  R3,  R4,  EMP, EMP, EMP);
  init_word(&mem[2], INSTR, MUL,  R3,  R4,  R5,  EMP, EMP, EMP);

  ret= ret && print_program(mem, 0, 0);
  ret= ret && print_program(mem, 1, 0);
  if (ret != 1)
    printf("A print_program() call didn't return 1 as expected.\n");
  else printf("Both print_program() calls returned 1 as expected.\n");

  return 0;
}
