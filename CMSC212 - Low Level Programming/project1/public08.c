/*
 * CMSC 212, Spring 2080, Project #1
 * Public test 08 (public08.c)
 *
 * Calls print_program() with invalid parameter values.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1

int main() {
  Word mem[128];
  int ret= 1;

  /* not bothering to check the return value of these calls */
  init_word(&mem[0], INSTR, ADD,  R1,  R2,  R3,  EMP, EMP, EMP);
  init_word(&mem[1], INSTR, SUB,  R2,  R3,  R4,  EMP, EMP, EMP);
  init_word(&mem[2], INSTR, MUL,  R3,  R4,  R5,  EMP, EMP, EMP);
  init_word(&mem[3], INSTR, DIV,  R5,  R4,  R3,  EMP, EMP, EMP);

  /* invalid call to print_program(), which should produce no output */
  ret= print_program(mem, -1, 4000);

  if (ret != 0)
    printf("An invalid print_program() call didn't return 0 as expected.\n");

  else {

    printf("Instructions are:\n");
    ret= print_program(mem, 0, 4);
    if (ret != 1)
      printf("print_program() call didn't return 1 as expected.\n");
    else printf("Instuctions should just have been printed once.\n");

  }

  return 0;
}
