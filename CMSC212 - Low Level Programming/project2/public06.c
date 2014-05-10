/*
 * CMSC 212, Spring 2010, Project #2
 * Public test 06 (public06.c)
 *
 * Tests execute_program() with lw, lo, and sw instructions.  Also verifies
 * that R0 contains 0.  Checks the contents of registers and memory
 * afterward.
 */

#include <stdio.h>
#include "machine.h"
#include "assembler.h"

#define SZ 128
#define NUM_REGISTERS 8

static int compare_memory(Mem memory[], Mem expected_memory[], int start,
                          int size);
static int compare_registers(short registers[], short expected_registers[],
                             int start, int size);

/* returns -1 if the size elements of memory and expected_memory are
 * identical, or the index of the first elements that differ
 */
static int compare_memory(Mem memory[], Mem expected_memory[], int start,
                          int size) {
  int ans= -1, i;

  for (i= start; i < start + size && ans == -1; i++)
    if (memory[i] != expected_memory[i])
      ans= i;

  return ans;
}

/* returns -1 if the size elements of registers and expected_registers are
 * identical, or the index of the first elements that differ
 */
static int compare_registers(short registers[], short expected_registers[],
                             int start, int size) {
  int ans= -1, i;

  for (i= start; i < start + size && ans == -1; i++)
    if (registers[i] != expected_registers[i])
      ans= i;

  return ans;
}

int main() {
  Mem mem[SZ]= {0};
  Mem exp_memory[SZ]= {0x91d4, 0x92fa, 0x811a, 0x8218, 0x6300, 0x9c78,
                       0x5330, 0x5330, 0x9d78, 0x8918, 0x8a1a, 0xb000,
                       0x00fa, 0x00d4};
  short registers[NUM_REGISTERS];  /* deliberately not initialized */
  short exp_registers[NUM_REGISTERS]= {0, 250, 212, 2, 250, 212};
  int num_instructions;
  Status ret;

  num_instructions= assemble("public06.a", mem);

  if (num_instructions == 0)
    printf("Regretfully the program couldn't be assembled.  Bye.\n");
  else {

    ret= execute_program(mem, registers, 0, 12, 0);

    if (ret != TERMINATED)
      printf("execute_program() returned unexpected value (%d).\n", ret);
    else

      if ((ret= compare_registers(registers, exp_registers, 0, 6)) != -1) {

        printf("Registers appear incorrect after execute_program() call.\n");
        printf("First incorrect register is %d (%d instead of %d).\n",
               ret, registers[ret], exp_registers[ret]);

      } else

        if ((ret= compare_memory(mem, exp_memory, 0, SZ)) != -1) {

          printf("Memory appears incorrect after execute_program() call.\n");
          printf("First incorrect address is %02x (%04x instead of %04x).\n",
               ret * 2, mem[ret], exp_memory[ret]);

        } else {

          printf("Registers and memory are correct after execute_program() ");
          printf("call!\n");

        }

  }

  return 0;
}
