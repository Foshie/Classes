/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 11 (public11.c)
 *
 * Tests pwd() for a filesystem.
 */

#include <stdio.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mkfs(&f);

  pwd(f);
  printf("\n");

  rmfs(&f);

  return 0;
}
