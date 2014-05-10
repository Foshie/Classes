#include <stdio.h>
#include "puzzles.h"

/*
CMSC 216 Fall 10, project 1, public test 01
testing is_nonzero()
 */

static void test_case(int x);

int main() {
  test_case(0);
  test_case(1);
  return 0;
}

static void test_case(int x) {
  printf("is_nonzero(%d) is %d, correct answer is %d\n", x, is_nonzero(x), x != 0);
}
