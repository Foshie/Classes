/*
 * CMSC 212, Spring 2010, Project #1
 * Secret test 09 (secret09.c)
 *
 * Tests shift_program() passing in 0 for size, which is valid but should
 * not shift anything.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1
#define SZ 128

int main() {
  Word mem[SZ]= {{0}};  /* initializes everything to zero */
  int ret;

  /* not bothering to check the return value of these calls */
  init_word(&mem[0], INSTR, ADD,  R1,  R2,  R3,  EMP, EMP, EMP);
  init_word(&mem[1], INSTR, SUB,  R2,  R3,  R4,  EMP, EMP, EMP);
  init_word(&mem[2], INSTR, MUL,  R3,  R4,  R5,  EMP, EMP, EMP);

  ret= shift_program(mem, 0, 0, 10);

  /* verify that address 10 has *not* been changed and still has 0s in
     all its fields (that none of the calls did anything); note that ADD
     is the opcode with value 0 and INSTR also has value 0 */
  if (ret != 1 || mem[10].contents != INSTR || mem[10].value.instr.op != ADD ||
      mem[10].value.instr.r1 != 0 || mem[10].value.instr.r2 != 0 ||
      mem[10].value.instr.r3 != 0 || mem[10].value.instr.address != 0 ||
      mem[10].value.instr.imm != 0)
    printf("Shifting by 0 words returned 0, or changed memory.\n");
  else printf("Shifting by 0 words returned 1 and didn't change memory.\n");

  return 0;
}
