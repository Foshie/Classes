/*
 * CMSC 212, Spring 2030, Project #1
 * Secret test 01 (secret01.c)
 *
 * Calls init_word() with some instructions that use immediates or memory
 * addresses, and print_program() to check the results.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1
#define SZ 128

int main() {
  Word mem[SZ];
  int ret= 1;

  ret= ret && init_word(&mem[0], INSTR, LI,  R2, EMP, EMP, EMP, 17,  EMP);
  ret= ret && init_word(&mem[1], INSTR, LO,  R3, R4,  EMP, 27,  EMP, EMP);
  ret= ret && init_word(&mem[2], INSTR, BEQ, R4, R5,  EMP, 37,  EMP, EMP);
  ret= ret && init_word(&mem[3], INSTR, BNE, R5, R6,  EMP, 47,  EMP, EMP);

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
