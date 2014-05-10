/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 02 (public02.c)
 *
 * Creates a filesystem and tries to create directories with invalid names.
 */

#include <stdio.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mkfs(&f);

  mkdir(&f, ".");

  mkdir(&f, "..");

  mkdir(&f, "/");

  rmfs(&f);

  return 0;
}
