/*
 * CMSC 212, Spring 2010, Project #2
 * Public test 11 (public11.c)
 *
 * Calls execute_program() with a program containing a tiny function.  Also
 * uses an io instruction.  Checks execute_program()'s return value, as well
 * as the contents of registers afterward.
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
  Mem mem[SZ]= {0};
  short registers[NUM_REGISTERS]= {0};
  short exp_registers[NUM_REGISTERS]= {0, 99, 2, 10, 0, 0, 0xfe, 0xc};
  int num_instructions;
  Status ret;

  num_instructions= assemble("public11.a", mem);

  if (num_instructions == 0)
    printf("Regretfully the program couldn't be assembled.  Bye.\n");
  else {

    ret= execute_program(mem, registers, 0, num_instructions, 0);

    if (ret != TERMINATED)
      printf("execute_program() returned unexpected value (%d).\n", ret);
    else

      if ((ret= compare_registers(registers, exp_registers, 0, 8)) != -1) {

        printf("Registers appear incorrect after execute_program() call.\n");
        printf("First incorrect register is %d (%d instead of %d).\n",
               ret, registers[ret], exp_registers[ret]);

      } else printf("Registers are correct after execute_program() call!\n");

  }

  return 0;
}
