#include <stdio.h>
#include "puzzles.h"

/*
CMSC 216 Fall 10, project 1, public test 04
testing times7()
 */

static void test_case( int x, int y);

int main() {
  printf("%d", (int)sizeof_int());

  test_case(0, 0);
  test_case(1, 1);
  test_case(0xffffffff, 0);
  test_case(0x10000000, 1);
  test_case(4, 12);

  return 0;
}

static void test_case(int x, int y) {
  printf("%d = %d ? %d\n", x, y, equal(x,y));
}
