/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 05 (public05.c)
 *
 * Adds a single file to a directory and lists the contents of the directory.
 */

#include <stdio.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mkfs(&f);

  mkdir(&f, "Animals");

  cd(&f, "Animals");
  touch(&f, "Elephant");

  ls(f, ".");
  printf("\n");

  rmfs(&f);

  return 0;
}
