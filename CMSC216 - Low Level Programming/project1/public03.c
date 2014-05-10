#include <stdio.h>
#include "puzzles.h"

/*
CMSC 216 Fall 10, project 1, public test 03
testing pop_count()
 */

static void test_case(unsigned int x);

int main() {
  test_case(0x2);
  test_case(0xf0);
  return 0;
}

static void test_case(unsigned int x) {
  printf("pop_count(0x%x) is %d\n", x, pop_count(x));
}
