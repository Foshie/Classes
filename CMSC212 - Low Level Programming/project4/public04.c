/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 04 (public04.c)
 *
 * Calls cd() with a valid directory name and lists the current directory.
 */

#include <stdio.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mkfs(&f);

  mkdir(&f, "Animals");

  cd(&f, "Animals");

  ls(f, "..");
  printf("\n");

  rmfs(&f);

  return 0;
}
