/*
 * CMSC 212, Spring 2150, Project #1
 * Public test 15 (public15.c)
 *
 * Calls shift_program with invalid parameter values, which should have no
 * effect.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1
#define SZ 128

int compare_memory_arrays(Word arr1[], Word arr2[]);

int compare_memory_arrays(Word arr1[], Word arr2[]) {
  int i, same= 1;

  for (i= 0; i < SZ && same == 1; i++)
    if (arr1[i].contents != arr2[i].contents ||
        (arr1[i].contents == DATA &&
         arr1[i].value.data != arr2[i].value.data) ||
        (arr1[i].contents == INSTR &&
         (arr1[i].value.instr.op != arr2[i].value.instr.op ||
          arr1[i].value.instr.r1 != arr2[i].value.instr.r1 ||
          arr1[i].value.instr.r2 != arr2[i].value.instr.r2 ||
          arr1[i].value.instr.r3 != arr2[i].value.instr.r3 ||
          arr1[i].value.instr.address != arr2[i].value.instr.address ||
          arr1[i].value.instr.imm != arr2[i].value.instr.imm)))
      same= 0;

  return same;
}

int main() {
  Word mem[SZ]= {{0}}, copy[SZ];
  int i, ret;

  /* not bothering to check the return value of these calls */
  init_word(&mem[0], INSTR, ADD,  R1,  R2,  R3,  EMP, EMP, EMP);
  init_word(&mem[1], INSTR, SUB,  R2,  R3,  R4,  EMP, EMP, EMP);
  init_word(&mem[2], INSTR, MUL,  R3,  R4,  R5,  EMP, EMP, EMP);
  init_word(&mem[3], INSTR, DIV,  R5,  R4,  R3,  EMP, EMP, EMP);
  init_word(&mem[4], INSTR, MOD,  R4,  R3,  R2,  EMP, EMP, EMP);
  init_word(&mem[5], INSTR, NOT,  R3,  R2,  EMP, EMP, EMP, EMP);
  init_word(&mem[6], INSTR, NEG,  R2,  R1,  EMP, EMP, EMP, EMP);
  init_word(&mem[7], INSTR, INC,  R1,  R0,  EMP, EMP, EMP, EMP);

  /* make a copy of the memory contents in a second arraay so we can verify
     that the incorrect call to shift_program() below doesn't change
     anything in memory */
  for (i= 0; i < SZ; i++)
    copy[i]= mem[i];

  shift_program(mem, -200, 210, -10);

  /* now verify the arrays mem and copy still have the same contents */
  ret= compare_memory_arrays(mem, copy);
  if (ret != 1) {

    printf("Incorrect call to shift_program() changed something in memory.\n");
    printf("(First changed location was %d.)\n", ret);

  } else {

    printf("An incorrect call to shift_program() had no effect on memory ");
    printf("as expected.\n");

  }

  return 0;
}
