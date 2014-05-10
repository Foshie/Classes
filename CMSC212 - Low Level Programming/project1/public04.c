/*
 * CMSC 212, Spring 2040, Project #1
 * Public test 04 (public04.c)
 *
 * Calls init_word() with several instructions that have memory address
 * operands, and print_program() to check the results.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1

int main() {
  Word mem[128];
  int ret= 1;

  ret= ret && init_word(&mem[0], INSTR, J,    EMP, EMP, EMP, 2, EMP, EMP);
  ret= ret && init_word(&mem[1], INSTR, JSR,  EMP, EMP, EMP, 3, EMP, EMP);
  ret= ret && init_word(&mem[2], INSTR, SW,   R3,  EMP, EMP, 1, EMP, EMP);
  ret= ret && init_word(&mem[3], INSTR, LW,   R2,  EMP, EMP, 4, EMP, EMP);

  if (ret == 0)
    printf("One or more init_word() calls unexpectedly returned 0.\n");

  else {

    printf("Instructions are:\n");
    ret= print_program(mem, 0, 4);
    if (ret != 1)
      printf("print_program() call didn't return 1 as expected.\n");
    else printf("Instuctions should have been printed.\n");

  }

  return 0;
}
