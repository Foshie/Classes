/*
 * CMSC 212, Spring 2010, Project #2
 * Public test 02 (public02.c)
 *
 * Tests the modified shift_program() by shifting a program upward (to a
 * higher memory range) that partly overlaps its original location.  Checks
 * the contents of memory afterward.
 */

#include <stdio.h>
#include "machine.h"

#define SZ 128

static int compare_memory(Mem memory[], Mem expected_memory[], int start,
                          int size);

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

int main() {
  int ret;
  Mem mem[SZ]= {0x0,     /* 0x00: unused */
                0x0,     /* 0x02: unused */
                0x0123,  /* 0x04: add   R1 R2 R3 */
                0x0a34,  /* 0x06: sub   R2 R3 R4 */
                0x1345,  /* 0x08: mul   R3 R4 R5 */
                0x1d43,  /* 0x0a: div   R5 R4 R3 */
                0x2432,  /* 0x0c: mod   R4 R3 R2 */
                0x2d32,  /* 0x0e: and   R5 R3 R2 */
                0x3325,  /* 0x10: or    R3 R2 R5 */
                0x3932,  /* 0x12: xor   R1 R3 R2 */
                0x4320,  /* 0x14: not   R3 R2    */
                0x4a10,  /* 0x16: neg   R2 R1    */
                0x5100,  /* 0x18: inc   R1 R0    */
                0x5810,  /* 0x1a: io    R0 R1    */
                0x6760,  /* 0x1c: move  R7 R6    */
                0x6802,  /* 0x1e: j     2        */
                0x7004,  /* 0x20: jsr   4        */
                0x7800,  /* 0x22: rtn            */
                0x8301,  /* 0x24: sw    R3 1     */
                0x8a04,  /* 0x26: lw    R2 4     */
                0x917b,  /* 0x28: li    R1 123   */
                0x9951,  /* 0x2a: lo    R1 R2 17 */
                0xa14a,  /* 0x2c: beq   R1 R2 10 */
                0xaa22,  /* 0x2e: bne   R2 R1 2  */
                0xb000   /* 0x30: halt           */
  };
  Mem exp_memory[SZ]= {0x0,     /* 0x00: unused */
                       0x0,     /* 0x02: unused */
                       0x0123,  /* 0x04: add   R1 R2 R3 */
                       0x0a34,  /* 0x06: sub   R2 R3 R4 */
                       0x1345,  /* 0x08: mul   R3 R4 R5 */
                       0x1d43,  /* 0x0a: div   R5 R4 R3 */
                       0x2432,  /* 0x0c: mod   R4 R3 R2 */
                       0x2d32,  /* 0x0e: and   R5 R3 R2 */
                       0x3325,  /* 0x10: or    R3 R2 R5 */
                       0x3932,  /* 0x12: xor   R1 R3 R2 */
                       0x4320,  /* 0x14: not   R3 R2    */
                       0x4a10,  /* 0x16: neg   R2 R1    */
                       0x5100,  /* 0x18: inc   R1 R0    */
                       0x5810,  /* 0x1a: io    R0 R1    */
                       0x0123,  /* 0x1c: add   R1 R2 R3 */
                       0x0a34,  /* 0x1e: sub   R2 R3 R4 */
                       0x1345,  /* 0x20: mul   R3 R4 R5 */
                       0x1d43,  /* 0x22: div   R5 R4 R3 */
                       0x2432,  /* 0x24: mod   R4 R3 R2 */
                       0x2d32,  /* 0x26: and   R5 R3 R2 */
                       0x3325,  /* 0x28: or    R3 R2 R5 */
                       0x3932,  /* 0x2a: xor   R1 R3 R2 */
                       0x4320,  /* 0x2c: not   R3 R2    */
                       0x4a10,  /* 0x2e: neg   R2 R1    */
                       0x5100,  /* 0x30: inc   R1 R0    */
                       0x5810,  /* 0x32: io    R0 R1    */
                       0x6760,  /* 0x34: move  R7 R6    */
                       0x6802,  /* 0x36: j     2        */
                       0x7004,  /* 0x38: jsr   4        */
                       0x7800,  /* 0x3a: rtn            */
                       0x8301,  /* 0x3c: sw    R3 1     */
                       0x8a04,  /* 0x3e: lw    R2 4     */
                       0x917b,  /* 0x40: li    R1 123   */
                       0x9951,  /* 0x42: lo    R1 R2 17 */
                       0xa14a,  /* 0x44: beq   R1 R2 10 */
                       0xaa22,  /* 0x46: bne   R2 R1 2  */
                       0xb000   /* 0x48: halt           */
  };

  if (shift_program(mem, 4, 46, 28) != 1)
    printf("shift_program() call didn't return 1 as exp_memory.\n");
  else
    if ((ret= compare_memory(mem, exp_memory, 0, SZ)) != -1) {
      printf("Memory contents appear incorrect after shift_program() call.\n");
      printf("First incorrect address is 0x%02x (0x%04x instead of 0x%04x).\n",
             ret * 2, mem[ret], exp_memory[ret]);
    } else printf("Memory appears correct after shift_program() call!\n");

  return 0;
}
