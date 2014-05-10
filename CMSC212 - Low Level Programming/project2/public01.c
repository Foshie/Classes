/*
 * CMSC 212, Spring 2010, Project #2
 * Public test 01 (public01.c)
 *
 * Tests the modified print_program().
 */

#include <stdio.h>
#include "machine.h"

#define SZ 128

int main() {
  Mem mem[SZ]= {0x0123,  /* 0x00: add   R1 R2 R3 */
                0x0a34,  /* 0x02: sub   R2 R3 R4 */
                0x1345,  /* 0x04: mul   R3 R4 R5 */
                0x1d43,  /* 0x06: div   R5 R4 R3 */
                0x2432,  /* 0x08: mod   R4 R3 R2 */
                0x2d32,  /* 0x0a: and   R5 R3 R2 */
                0x3325,  /* 0x0c: or    R3 R2 R5 */
                0x3932,  /* 0x0e: xor   R1 R3 R2 */
                0x4320,  /* 0x10: not   R3 R2    */
                0x4a10,  /* 0x12: neg   R2 R1    */
                0x5100,  /* 0x14: inc   R1 R0    */
                0x5810,  /* 0x16: io    R0 R1    */
                0x6760,  /* 0x18: move  R7 R6    */
                0x6802,  /* 0x1a: j     2        */
                0x7004,  /* 0x1c: jsr   4        */
                0x7800,  /* 0x1e: rtn            */
                0x8301,  /* 0x20: sw    R3 1     */
                0x8a04,  /* 0x22: lw    R2 4     */
                0x917b,  /* 0x24: li    R1 123   */
                0x9951,  /* 0x26: lo    R1 R2 17 */
                0xa14a,  /* 0x28: beq   R1 R2 10 */
                0xaa22,  /* 0x2a: bne   R2 R1 2  */
                0xb000   /* 0x2c: halt           */
  };

  if (print_program(mem, 0, 46) != 1)
    printf("print_program() call didn't return 1 as expected.\n");
  else printf("Instuctions should have been printed.\n");

  return 0;
}
