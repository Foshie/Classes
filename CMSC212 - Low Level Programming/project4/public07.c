/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 07 (public07.c)
 *
 * Tests the touch() function with the same filename more than once, and
 * with '/'.
 */

#include <stdio.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mkfs(&f);

  mkdir(&f, "Animals");

  cd(&f, "Animals");
  touch(&f, "Elephant");
  touch(&f, "Tiger");
  touch(&f, "Lion");
  touch(&f, "Tiger");
  touch(&f, "/");

  ls(f, ".");
  printf("\n");

  rmfs(&f);

  return 0;
}
