/*
 * CMSC 212, Spring 2050, Project #1
 * Public test 05 (public05.c)
 *
 * Calls init_word() with several instructions and instruction types not
 * tested in the earlier public tests, and print_program() to check the
 * results.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1

int main() {
  Word mem[128];
  int ret= 1;

  ret= ret && init_word(&mem[0],  INSTR, AND,  R1,  R3,  R2,  EMP, EMP, EMP);
  ret= ret && init_word(&mem[1],  INSTR, OR,   R1,  R3,  R2,  EMP, EMP, EMP);
  ret= ret && init_word(&mem[2],  INSTR, XOR,  R1,  R3,  R2,  EMP, EMP, EMP);
  ret= ret && init_word(&mem[3],  INSTR, IO,   R0,  R1,  EMP, EMP, EMP, EMP);
  ret= ret && init_word(&mem[4],  INSTR, MOVE, R7,  R6,  EMP, EMP, EMP, EMP);
  ret= ret && init_word(&mem[5],  INSTR, LI,   R1,  EMP, EMP, EMP, 123, EMP);
  ret= ret && init_word(&mem[6],  INSTR, LO,   R1,  R2,  EMP, 17,  EMP, EMP);
  ret= ret && init_word(&mem[7],  INSTR, BEQ,  R1,  R2,  EMP, 10,  EMP, EMP);
  ret= ret && init_word(&mem[8],  INSTR, BNE,  R2,  R1,  EMP, 2,   EMP, EMP);
  ret= ret && init_word(&mem[9],  INSTR, RTN,  EMP, EMP, EMP, EMP, EMP, EMP);
  ret= ret && init_word(&mem[10], INSTR, HALT, EMP, EMP, EMP, EMP, EMP, EMP);

  if (ret == 0)
    printf("One or more init_word() calls unexpectedly returned 0.\n");

  else {

    printf("Instructions are:\n");
    ret= print_program(mem, 0, 11);
    if (ret != 1)
      printf("print_program() call didn't return 1 as expected.\n");
    else printf("Instuctions should have been printed.\n");

  }

  return 0;
}
