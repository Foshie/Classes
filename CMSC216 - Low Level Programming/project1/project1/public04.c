#include <stdio.h>
#include "puzzles.h"

/*
CMSC 216 Fall 10, project 1, public test 04
testing times7()
 */

static void test_case(unsigned int x);

int main() {
  test_case(3);
  test_case(11);
  return 0;
}

static void test_case(unsigned int x) {
  printf("times7(%u) is %u\n", x, times7(x));
}
