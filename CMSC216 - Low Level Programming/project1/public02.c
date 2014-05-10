#include <stdio.h>
#include "puzzles.h"

/*
CMSC 216 Fall 10, project 1, public test 02
testing floor_log2()
 */

static void test_case(unsigned int x);

int main() {
  test_case(0);
  test_case(1);
  return 0;
}

static void test_case(unsigned int x) {
  printf("floor_log2(%d) = %d\n", x, floor_log2(x));
}
