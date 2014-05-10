/*
 * CMSC 212, Spring 2060, Project #1
 * Public test 06 (public06.c)
 *
 * Calls init_word() with various values for parameters not used by
 * instructions, and print_program() to check the results.
 */

#include <stdio.h>
#include "machine.h"

int main() {
  Word mem[128];
  int ret= 1;

  ret= ret && init_word(&mem[0], INSTR, ADD,  R1,  R2,  R3,  -2,  2,   3);
  ret= ret && init_word(&mem[1], INSTR, NOT,  R3,  R2,  4,   5,   6,   -7);
  ret= ret && init_word(&mem[2], INSTR, JSR,  8,   -9,  10,  40,  -12, -13);
  ret= ret && init_word(&mem[3], INSTR, SW,   R3,  123, 456, 51,  987, 654);
  ret= ret && init_word(&mem[4], INSTR, LI,   R4,  222, 333, 444, 5,   666);
  ret= ret && init_word(&mem[5], INSTR, LO,   R1,  R5,  888, 200, 0,   11);
  ret= ret && init_word(&mem[6], INSTR, BEQ,  R1,  R2,  22,  10,  33,  44);

  if (ret == 0)
    printf("One or more init_word() calls unexpectedly returned 0.\n");

  else {

    printf("Instructions are:\n");
    ret= print_program(mem, 0, 7);
    if (ret != 1)
      printf("print_program() call didn't return 1 as expected.\n");
    else printf("Instuctions should have been printed.\n");

  }

  return 0;
}
