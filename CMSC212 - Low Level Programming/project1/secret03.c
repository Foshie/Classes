/*
 * CMSC 212, Spring 2030, Project #1
 * Secret test 03 (secret03.c)
 *
 * Tests print_program() with values for start that are invalid (too large).
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1
#define SZ 128

int main() {
  Word mem[SZ];
  int ret;

  ret= init_word(&mem[127], INSTR, LI, R0, EMP, EMP, EMP, 17, EMP);

  /* first ensure that the valid value 127 for start does work */
  ret= ret && print_program(mem, 127, 1);
  if (ret != 1)
    printf("init_word() or print_program() didn't return 1 as expected.\n");
  else printf("init_word() or print_program() didn't return 1 as expected.\n");

  /* now try the invalid values 128 and 129 for start */
  ret= 0;
  ret= ret || print_program(mem, 128, 1);
  ret= ret || print_program(mem, 129, 1);
  if (ret != 0)
    printf("One invalid print_program() call didn't return 0 as expected.\n");
  else printf("Both invalid print_program() calls returned 0 as expected.\n");

  return 0;
}
