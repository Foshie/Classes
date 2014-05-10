/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 06 (public06.c)
 *
 * Adds multiple files to a directory and lists the contents of the current
 * directory.
 */

#include <stdio.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mkfs(&f);

  mkdir(&f, "Animals");

  cd(&f, "Animals");
  touch(&f, "Elephant");
  touch(&f, "Lion");
  touch(&f, "Tiger");

  ls(f, ".");
  printf("\n");

  rmfs(&f);

  return 0;
}
