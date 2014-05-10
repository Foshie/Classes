/*
 * CMSC 212, Spring 2010, Project #1
 * Secret test 08 (secret08.c)
 *
 * Tests shift_program() passing in negative values for size.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1
#define SZ 128

int main() {
  Word mem[SZ]= {{0}};  /* initializes everything to zero */
  int ret= 0;

  /* not bothering to check the return value of this call */
  init_word(&mem[0], INSTR, DIV, R1, R2, R3, EMP, EMP, EMP);

  ret= ret || shift_program(mem, 0, -1, 10);
  ret= ret || shift_program(mem, 1, -2, 10);
  ret= ret || shift_program(mem, 2, -3, 10);

  /* verify that address 10 has *not* been changed and still has 0s in
     all its fields (that none of the calls did anything); note that ADD
     is the opcode with value 0 and INSTR also has value 0 */
  if (ret != 0 || mem[10].contents != INSTR || mem[10].value.instr.op != ADD ||
      mem[10].value.instr.r1 != 0 || mem[10].value.instr.r2 != 0 ||
      mem[10].value.instr.r3 != 0 || mem[10].value.instr.address != 0 ||
      mem[10].value.instr.imm != 0)
    printf("An invalid shift_program() call unexpectedly had some effect.\n");
  else printf("The invalid shift_program() calls did nothing as expected.\n");

  return 0;
}
