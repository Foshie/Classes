/*
 * CMSC 212, Spring 2140, Project #1
 * Public test 14 (public14.c)
 *
 * Calls shift_program() to shift a program, and afterwards prints the
 * original memory region where it was, as well as the region where it was
 * shifted to.
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
  init_word(&mem[2], INSTR, MUL,  R3,  R4,  R5,  EMP, EMP, EMP);
  init_word(&mem[3], INSTR, DIV,  R5,  R4,  R3,  EMP, EMP, EMP);
  init_word(&mem[4], INSTR, MOD,  R4,  R3,  R2,  EMP, EMP, EMP);
  init_word(&mem[5], INSTR, NOT,  R3,  R2,  EMP, EMP, EMP, EMP);
  init_word(&mem[6], INSTR, NEG,  R2,  R1,  EMP, EMP, EMP, EMP);
  init_word(&mem[7], INSTR, INC,  R1,  R0,  EMP, EMP, EMP, EMP);

  /* put specific values in the locations that the program will be
     shifted to, so we can tell later whether they've been changed */
  init_word(&mem[100], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 111);
  init_word(&mem[101], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 222);
  init_word(&mem[102], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 333);
  init_word(&mem[103], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 444);
  init_word(&mem[104], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 555);
  init_word(&mem[105], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 666);
  init_word(&mem[106], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 777);
  init_word(&mem[107], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 888);

  ret= shift_program(mem, 0, 8, 100);

  printf("Contents of original memory region are:\n");
  ret= ret && print_program(mem, 0, 8);
  printf("Original program should have been printed.\n\n");
  printf("Contents of new memory region are:\n");
  ret= ret && print_program(mem, 100, 8);
  if (ret != 1)
    printf("At least one function call didn't return 1 as expected.\n");
  else printf("Shifted program should have been printed.\n");

  return 0;
}
