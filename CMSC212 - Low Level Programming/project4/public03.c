/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 03 (public03.c)
 *
 * Creates a filesystem with a few valid and invalid directories and files.
 */

#include <stdio.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mkfs(&f);

  mkdir(&f, "police");
  mkdir(&f, "pol/ice");
  mkdir(&f, "police");
  touch(&f, "Culprits");

  ls(f, ".");
  printf("\n");

  rmfs(&f);
  return 0;
}
