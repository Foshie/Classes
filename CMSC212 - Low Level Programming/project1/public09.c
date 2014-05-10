/*
 * CMSC 212, Spring 2090, Project #1
 * Public test 09 (public09.c)
 *
 * Calls print_program() with a program that was put into memory starting
 * somewhere other than address 0.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1

int main() {
  Word mem[128];
  int ret= 1;

  ret= ret && init_word(&mem[10], INSTR, J,    EMP, EMP, EMP, 2, EMP, EMP);
  ret= ret && init_word(&mem[11], INSTR, JSR,  EMP, EMP, EMP, 3, EMP, EMP);
  ret= ret && init_word(&mem[12], INSTR, SW,   R3,  EMP, EMP, 1, EMP, EMP);
  ret= ret && init_word(&mem[13], INSTR, LW,   R2,  EMP, EMP, 4, EMP, EMP);

  if (ret == 0)
    printf("One or more init_word() calls unexpectedly returned 0.\n");

  else {

    printf("Instructions are:\n");
    ret= print_program(mem, 10, 4);
    if (ret != 1)
      printf("print_program() call didn't return 1 as expected.\n");
    else printf("Instuctions should have been printed.\n");

  }

  return 0;
}
