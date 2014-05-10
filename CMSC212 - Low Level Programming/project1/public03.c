/*
 * CMSC 212, Spring 2030, Project #1
 * Public test 03 (public03.c)
 *
 * Calls init_word() with several register-only instructions, and
 * print_program() to check the results.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1

int main() {
  Word mem[128];
  int ret= 1;

  ret= ret && init_word(&mem[0], INSTR, ADD,  R1,  R2,  R3,  EMP, EMP, EMP);
  ret= ret && init_word(&mem[1], INSTR, SUB,  R2,  R3,  R4,  EMP, EMP, EMP);
  ret= ret && init_word(&mem[2], INSTR, MUL,  R3,  R4,  R5,  EMP, EMP, EMP);
  ret= ret && init_word(&mem[3], INSTR, DIV,  R5,  R4,  R3,  EMP, EMP, EMP);
  ret= ret && init_word(&mem[4], INSTR, MOD,  R4,  R3,  R2,  EMP, EMP, EMP);
  ret= ret && init_word(&mem[5], INSTR, NOT,  R3,  R2,  EMP, EMP, EMP, EMP);
  ret= ret && init_word(&mem[6], INSTR, NEG,  R2,  R1,  EMP, EMP, EMP, EMP);
  ret= ret && init_word(&mem[7], INSTR, INC,  R1,  R0,  EMP, EMP, EMP, EMP);

  if (ret == 0)
    printf("One or more init_word() calls unexpectedly returned 0.\n");

  else {

    printf("Instructions are:\n");
    ret= print_program(mem, 0, 8);
    if (ret != 1)
      printf("print_program() call didn't return 1 as expected.\n");
    else printf("Instuctions should have been printed.\n");

  }

  return 0;
}
