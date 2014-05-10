/*
 * CMSC 212, Spring 2130, Project #1
 * Public test 13 (public13.c)
 *
 * Calls shift_program() to shift a program containing instructions and data,
 * shifting downward to a lower memory region.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1

int main() {
  Word mem[128];
  int ret;

  /* not bothering to check the return value of these calls */
  init_word(&mem[100], INSTR, ADD,  R1,  R2,  R3,  EMP, EMP, EMP);
  init_word(&mem[101], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 175);
  init_word(&mem[102], INSTR, MUL,  R3,  R4,  R5,  EMP, EMP, EMP);
  init_word(&mem[103], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 751);
  init_word(&mem[104], INSTR, MOD,  R4,  R3,  R2,  EMP, EMP, EMP);
  init_word(&mem[105], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 571);
  init_word(&mem[106], INSTR, NEG,  R2,  R1,  EMP, EMP, EMP, EMP);
  init_word(&mem[107], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 715);
  init_word(&mem[108], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 517);
  init_word(&mem[109], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 157);

  /* put specific values in the locations that the program will be
     shifted to, so we can tell later whether they've been changed */
  init_word(&mem[0], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 111);
  init_word(&mem[1], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 222);
  init_word(&mem[2], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 333);
  init_word(&mem[3], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 444);
  init_word(&mem[4], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 555);
  init_word(&mem[5], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 666);
  init_word(&mem[6], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 777);
  init_word(&mem[7], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 888);
  init_word(&mem[8], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 999);
  init_word(&mem[9], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, -11);

  ret= shift_program(mem, 100, 10, 0);

  printf("Program is:\n");
  ret= ret && print_program(mem, 0, 10);
  if (ret != 1)
    printf("Either shift_program() or print_program() didn't return 1.\n");
  else printf("Shifted program should have been printed.\n");

  return 0;
}
