/*
 * CMSC 212, Spring 2010, Project #2
 * Public test 03 (public03.c)
 *
 * Tests execute_program() with several binary arithmetic and logical
 * instructions.  Checks the contents of registers afterward.  Note that to
 * avoid using the load instructions in this test (and be able to test only
 * the computation instructions) the test passes in initial "hardcoded"
 * register values that the instructions will operate upon.  The
 * instructions don't end with "halt", so ACTIVE should be returned.
 */

#include <stdio.h>
#include "machine.h"
#include "assembler.h"

#define SZ 128
#define NUM_REGISTERS 8

static int compare_registers(short registers[], short expected_registers[],
                             int start, int size);

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
  Mem mem[SZ];
  short registers[NUM_REGISTERS]= {0, 11, 9, 7, 5, 2, 0, 0};
  short exp_registers[NUM_REGISTERS]= {0, 0, 1, 1, 1, 5};
  int num_instructions;
  Status ret;

  num_instructions= assemble("public03.a", mem);

  if (num_instructions == 0)
    printf("Regretfully the program couldn't be assembled.  Bye.\n");
  else {

    ret= execute_program(mem, registers, 0, num_instructions, 0);

    if (ret != ACTIVE)  /* because there's no halt instruction */
      printf("execute_program() returned unexpected value (%d).\n", ret);
    else
      if ((ret= compare_registers(registers, exp_registers, 1, 5)) != -1) {
        printf("Registers appear incorrect after execute_program() call.\n");
        printf("First incorrect register is %d (%d instead of %d).\n",
               ret, registers[ret], exp_registers[ret]);
      } else printf("Registers are correct after execute_program() call!\n");

  }

  return 0;
}