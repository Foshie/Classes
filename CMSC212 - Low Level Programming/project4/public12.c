/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 12 (public12.c)
 *
 * Tests pwd() with a valid subdirectory as the current working directory.
 */

#include <stdio.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mkfs(&f);

  mkdir(&f, "Fruits");
  cd(&f, "Fruits");
  mkdir(&f, "Apple");
  cd(&f, "Apple");
  touch(&f, "Green");
  pwd(f);
  printf("\n");

  rmfs(&f);
  return 0;
}
