/*
 * CMSC 212, Spring 2100, Project #1
 * Public test 10 (public10.c)
 *
 * Calls shift_program() to shift just one instruction, and print_program to
 * check the results.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1

int main() {
  Word mem[128];
  int ret;

  /* not bothering to check the return value of these calls */
  init_word(&mem[0], INSTR, ADD,  R1,  R2,  R3,  EMP, EMP, EMP);
  init_word(&mem[1], INSTR, SUB,  R2,  R3,  R4,  EMP, EMP, EMP);

  /* shift first instruction up by 1, so it should replace the original
     second instruction that is above */
  ret= shift_program(mem, 0, 1, 1);

  printf("Instruction is:\n");
  ret= ret && print_program(mem, 1, 1);
  if (ret != 1)
    printf("Either shift_program() or print_program() didn't return 1.\n");
  else printf("Shifted instuction should have been printed.\n");

  return 0;
}
