/*
 * CMSC 212, Spring 2010, Project #1
 * Secret test 11 (secret11.c)
 *
 * Tests shift_program() by shifting a program downward (to a lower memory
 * range) that partly overlaps its original location.
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
  Word mem[SZ]= {{0}};  /* initializes everything to zero */
  Word expected[SZ]= {{0},
                      {0},
                      {0},
                      {0},
                      {0},
                      {0},
                      {INSTR, {{ADD, R1, R2, R3, EMP, EMP}}},
                      {INSTR, {{SUB, R2, R3, R4, EMP, EMP}}},
                      {INSTR, {{MUL, R3, R4, R5, EMP, EMP}}},
                      {INSTR, {{DIV, R5, R4, R3, EMP, EMP}}},
                      {INSTR, {{MOD, R4, R3, R2, EMP, EMP}}},
                      {INSTR, {{AND, R4, R3, R2, EMP, EMP}}},
                      {INSTR, {{OR,  R4, R3, R2, EMP, EMP}}},
                      {INSTR, {{XOR, R4, R3, R2, EMP, EMP}}},
                      {INSTR, {{MOD, R4, R3, R2, EMP, EMP}}},
                      {INSTR, {{AND, R4, R3, R2, EMP, EMP}}},
                      {INSTR, {{OR,  R4, R3, R2, EMP, EMP}}},
                      {INSTR, {{XOR, R4, R3, R2, EMP, EMP}}}};

  /* not bothering to check the return value of these calls */
  init_word(&mem[10], INSTR, ADD,  R1,  R2,  R3,  EMP, EMP, EMP);
  init_word(&mem[11], INSTR, SUB,  R2,  R3,  R4,  EMP, EMP, EMP);
  init_word(&mem[12], INSTR, MUL,  R3,  R4,  R5,  EMP, EMP, EMP);
  init_word(&mem[13], INSTR, DIV,  R5,  R4,  R3,  EMP, EMP, EMP);
  init_word(&mem[14], INSTR, MOD,  R4,  R3,  R2,  EMP, EMP, EMP);
  init_word(&mem[15], INSTR, AND,  R4,  R3,  R2,  EMP, EMP, EMP);
  init_word(&mem[16], INSTR, OR,   R4,  R3,  R2,  EMP, EMP, EMP);
  init_word(&mem[17], INSTR, XOR,  R4,  R3,  R2,  EMP, EMP, EMP);

  /* the array "expected" has the hardcoded values that mem is expected to
     have after the shift; the function compare_memory_arrays compares two
     arrays of memory to ensure they have identical values */
  if (shift_program(mem, 10, 8, 6) != 1 ||
      compare_memory_arrays(mem, expected) == 0)
    printf("shift_program() call returned 0, or memory is incorrect.\n");
  else printf("shift_program() call returned 1, and memory is correct.\n");

  return 0;
}
