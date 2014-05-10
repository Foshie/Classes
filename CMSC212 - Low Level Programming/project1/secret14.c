/*
 * CMSC 212, Spring 2010, Project #1
 * Secret test 14 (secret14.c)
 *
 * Tests shift_program() by shifting a program that occupies all of memory
 * by exactly 0 words.
 */

#include <stdio.h>
#include "machine.h"

#define EMP -1
#define SZ 128

static int compare_memory_arrays(Word arr1[], Word arr2[]);

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
  Word mem[SZ], copy[SZ];
  int i;

  /* not bothering to check the return value of these calls */
  init_word(&mem[0], INSTR, BEQ,  R1,  R2,  EMP, 50,  EMP, EMP);
  init_word(&mem[1], INSTR, XOR,  R4,  R3,  R2,  EMP, EMP, EMP);

  for (i= 2; i < 126; i++)
    init_word(&mem[i], DATA, EMP, EMP, EMP, EMP, EMP, EMP, i);

  init_word(&mem[126], INSTR, BNE,  R1,  R2,  EMP, 50,  EMP, EMP);
  init_word(&mem[127], INSTR, AND,  R4,  R3,  R2,  EMP, EMP, EMP);

  /* make a copy of the memory contents in a second array so we can verify
     that the incorrect call to shift_program() below doesn't change
     anything in memory */
  for (i= 0; i < SZ; i++)
    copy[i]= mem[i];

  shift_program(mem, 0, 128, 0);

  /* now verify the arrays mem and copy still have the same contents */
  if (compare_memory_arrays(mem, copy) == 1)
    printf("Shifting a 128-word program by 0 locations worked fine.\n");
  else printf("Shifting a 128-word program by 0 locations didn't work.\n");

  return 0;
}
