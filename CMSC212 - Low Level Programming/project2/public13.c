/*
 * CMSC 212, Spring 2010, Project #2
 * Public test 13 (public13.c)
 *
 * Calls execute_program() with a program that's loaded into the middle of
 * memory (not starting at address 0), containing instructions that have
 * addresses.  Checks the contents of registers afterward.
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
  short exp_registers[NUM_REGISTERS]= {0, 17, 17, 0, 0, 20, 0xfe, 0x10};
  int num_instructions;
  Status ret;

  num_instructions= assemble("public13.a", &mem[20]);

  if (num_instructions == 0)
    printf("Regretfully the program couldn't be assembled.  Bye.\n");
  else {

    ret= execute_program(mem, registers, 40, 7, 0);

    if (ret != TERMINATED)
      printf("execute_program() returned unexpected value (%d).\n", ret);
    else

      if ((ret= compare_registers(registers, exp_registers, 0, 8)) != -1) {

        printf("Registers appear incorrect after execute_program() call.\n");
        printf("First incorrect register is %d (%d instead of %d).\n",
               ret, registers[ret], exp_registers[ret]);

      } else
        if (mem[29] != 17) {
          printf("The memory location at address 58 appears incorrect ");
          printf("0x%04x instead of 0x%04x).\n", mem[29], 17);
        } else {
          printf("Registers and memory are correct after execute_program() ");
          printf("call!\n");
        }

  }

  return 0;
}
