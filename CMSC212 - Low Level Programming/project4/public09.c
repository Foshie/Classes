/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 13 (public13.c)
 *
 * Creates two directories containing multiple files and lists their
 * contents.
 */

#include <stdio.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mkfs(&f);

  mkdir(&f, "Animals");
  mkdir(&f, "Birds");

  cd(&f, "Animals");
  touch(&f, "Elephant");
  touch(&f, "Tiger");
  touch(&f, "Lion");

  cd(&f, "..");

  cd(&f, "Birds");
  touch(&f, "Sparrow");
  touch(&f, "Eagle");

  cd(&f, "..");

  ls(f, "Animals");
  printf("\n");
  ls(f, "Birds");
  printf("\n");

  rmfs(&f);

  return 0;
}


