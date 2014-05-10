/*
 * CMSC 212, Spring 2010, Project #1
 * Secret test 07 (secret07.c)
 *
 * Tests shift_program()'s return value for values for start that are
 * invalid (too large).
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1
#define SZ 128

int main() {
  Word mem[SZ];
  int ret= 0;

  ret= ret || shift_program(mem, SZ, 1, 10);
  ret= ret || shift_program(mem, SZ + 1, 1, 10);
  ret= ret || shift_program(mem, SZ + 2, 1, 10);

  if (ret != 0)
    printf("An invalid shift_program() call didn't return 0 as expected.\n");
  else printf("All invalid shift_program() calls returned 0 as expected.\n");

  return 0;
}
