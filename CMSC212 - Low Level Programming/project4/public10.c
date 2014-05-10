/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 10 (public10.c)
 *
 * Creates two directories with multiple subdirectories and prints them.
 */

#include <stdio.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mkfs(&f);

  mkdir(&f, "Animals");
  mkdir(&f, "Employees");

  cd(&f, "Animals");
  mkdir(&f, "Herbivores");
  mkdir(&f, "Carnivores");

  cd(&f,"/");

  cd(&f, "Employees");
  mkdir(&f, "Full-time");
  mkdir(&f, "Part-time");

  cd(&f, "/");

  ls(f,"/");
  printf("\n");
  ls(f, "Animals");
  printf("\n");
  ls(f, "Employees");
  printf("\n");

  rmfs(&f);

  return 0;
}

