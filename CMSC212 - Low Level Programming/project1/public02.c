/*
 * CMSC 212, Spring 2010, Project #1
 * Public test 02 (public02.c)
 *
 * Calls init_word() with a two-register instruction, and print_program() to
 * check its results.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1

int main() {
  Word mem[128];
  int ret;

  ret= init_word(&mem[0], INSTR, INC,  R4,  R5,  EMP,  EMP, EMP, EMP);

  if (ret != 1)
    printf("init_word() call didn't return 1 as expected.\n");

  else {

    printf("Instruction is:\n");
    ret= print_program(mem, 0, 1);
    if (ret != 1)
      printf("print_program() call didn't return 1 as expected.\n");
    else printf("Instuction should have been printed.\n");

  }

  return 0;
}
