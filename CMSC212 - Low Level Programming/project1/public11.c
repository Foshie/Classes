/*
 * CMSC 212, Spring 2110, Project #1
 * Public test 11 (public11.c)
 *
 * Calls shift_program() to shift a program containing multiple instructions,
 * and print_program to check the results.
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
  init_word(&mem[10], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 111);
  init_word(&mem[11], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 222);
  init_word(&mem[12], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 333);
  init_word(&mem[13], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 444);
  init_word(&mem[14], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 555);
  init_word(&mem[15], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 666);
  init_word(&mem[16], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 777);
  init_word(&mem[17], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 888);

  ret= shift_program(mem, 0, 8, 10);

  printf("Program is:\n");
  ret= ret && print_program(mem, 10, 8);
  if (ret != 1)
    printf("Either shift_program() or print_program() didn't return 1.\n");
  else printf("Shifted program should have been printed.\n");

  return 0;
}
