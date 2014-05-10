/*
 * CMSC 212, Spring 2070, Project #1
 * Public test 07 (public07.c)
 *
 * Calls init_word() and print_program() with a program containing some words
 * containing data values.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1

int main() {
  Word mem[128];
  int ret= 1;

  ret= ret && init_word(&mem[0], INSTR, ADD,  R1,  R2,  R3,  EMP, EMP, EMP);
  ret= ret && init_word(&mem[1], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 175);
  ret= ret && init_word(&mem[2], INSTR, MUL,  R3,  R4,  R5,  EMP, EMP, EMP);
  ret= ret && init_word(&mem[3], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 751);
  ret= ret && init_word(&mem[4], INSTR, MOD,  R4,  R3,  R2,  EMP, EMP, EMP);
  ret= ret && init_word(&mem[5], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 571);
  ret= ret && init_word(&mem[6], INSTR, NEG,  R2,  R1,  EMP, EMP, EMP, EMP);
  ret= ret && init_word(&mem[7], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 715);
  ret= ret && init_word(&mem[8], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 517);
  ret= ret && init_word(&mem[9], DATA,  EMP,  EMP, EMP, EMP, EMP, EMP, 157);

  if (ret == 0)
    printf("One or more init_word() calls unexpectedly returned 0.\n");

  else {

    printf("Instructions are:\n");
    ret= print_program(mem, 0, 10);
    if (ret != 1)
      printf("print_program() call didn't return 1 as expected.\n");
    else printf("Instuctions should have been printed.\n");

  }

  return 0;
}
