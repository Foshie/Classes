/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 13 (public13.c)
 *
 * Creates a  directory with multiple subdirectories and files and navigates
 * through them while checking for memory leaks and validity of the heap.
 */

#include <stdio.h>
#include <malloc.h>
#include <mcheck.h>
#include "filesystem.h"

int main(){
  Filesystem f;

  mcheck_pedantic(NULL);

  mkfs(&f);

  mkdir(&f, "Animals");

  cd(&f, "Animals");
  mkdir(&f, "Herbivores");
  mkdir(&f, "Carnivores");

  cd(&f, "Carnivores");
  touch(&f, "Tiger");
  touch(&f, "Bear");

  cd(&f,"..");

  cd(&f, "Herbivores");
  touch(&f, "Deer");
  touch(&f, "Cow");

  cd(&f, "..");

  ls(f,"/");
  printf("\n");
  ls(f, ".");
  printf("\n");
  ls(f, "Herbivores");
  printf("\n");
  ls(f, "Carnivores");
  printf("\n");

  rmfs(&f);

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes :(. \n", mallinfo().uordblks);
  else printf("No memory leak detected :).\n");

  return 0;
}

