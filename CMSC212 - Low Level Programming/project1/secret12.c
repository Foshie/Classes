/*
 * CMSC 212, Spring 2010, Project #1
 * Secret test 12 (secret12.c)
 *
 * Tests shift_program() by shifting a program several times- the calls
 * shift some instructions and overwrite some original instructions- and
 * printing the results.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1
#define SZ 128

int main() {
  Word mem[SZ]= {{0}};  /* initializes everything to zero */

  /* not bothering to check the return value of these calls */
  init_word(&mem[0], INSTR, ADD,  R1,  R2,  R3,  EMP, EMP, EMP);
  init_word(&mem[1], INSTR, SUB,  R2,  R3,  R4,  EMP, EMP, EMP);
  init_word(&mem[2], INSTR, MUL,  R3,  R4,  R5,  EMP, EMP, EMP);
  init_word(&mem[3], INSTR, DIV,  R5,  R4,  R3,  EMP, EMP, EMP);
  init_word(&mem[4], INSTR, MOD,  R4,  R3,  R2,  EMP, EMP, EMP);
  init_word(&mem[5], INSTR, AND,  R4,  R3,  R2,  EMP, EMP, EMP);
  init_word(&mem[6], INSTR, OR,   R4,  R3,  R2,  EMP, EMP, EMP);
  init_word(&mem[7], INSTR, XOR,  R4,  R3,  R2,  EMP, EMP, EMP);

  /* not bothering to check the return value of these calls */
  shift_program(mem, 0, 8, 8);
  shift_program(mem, 0, 3, 5);
  shift_program(mem, 10, 4, 3);
  shift_program(mem, 12, 1, 2);

  print_program(mem, 0, 16);

  return 0;
}
