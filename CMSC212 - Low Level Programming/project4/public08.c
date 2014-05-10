/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 08 (public08.c)
 *
 * Creates two directories and lists them.
 */

#include <stdio.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mkfs(&f);

  mkdir(&f, "Animals");
  mkdir(&f, "Birds");
  mkdir(&f, "Animals");

  ls(f, ".");
  printf("\n");

  rmfs(&f);

  return 0;
}
