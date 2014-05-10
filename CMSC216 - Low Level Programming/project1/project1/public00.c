#include <stdio.h>
#include "puzzles.h"

/*
CMSC 216 Fall 10, project 1, public test 00
testing bit_and()
 */

static void test_case(int a, int b);

int main() {
  test_case(0x5, 0x7);
  test_case(0xd, 0x11);
  return 0;
}

static void test_case(int a, int b) {
  printf("bit_and(0x%x, 0x%x) is 0x%x\n", a, b, bit_and(a, b));
}
