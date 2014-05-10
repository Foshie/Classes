/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 14 (public14.c)
 *
 * Creates two directories with multple files and subdirectories and
 * navigates through them while cheking for memory leaks and validity of the
 * heap.
 */

#include <stdio.h>
#include <malloc.h>
#include <mcheck.h>
#include "filesystem.h"

int main(){
  Filesystem f;


  mkfs(&f);

  mkdir(&f, "Animals");
  mkdir(&f, "Birds");

  ls(f, "/");
  printf("\n");

  cd(&f, "Animals");
  mkdir(&f, "Herbivores");
  mkdir(&f, "Carnivores");

  ls(f, ".");
  printf("\n");

  cd(&f, "Carnivores");
  touch(&f, "Tiger");
  touch(&f, "Bear");

  ls(f, ".");
  printf("\n");

  cd(&f,"..");

  cd(&f, "Herbivores");
  touch(&f, "Deer");
  touch(&f, "Cow");
  touch(&f, "Bear");

  ls(f, ".");
  printf("\n");

  cd(&f, "/");

  cd(&f, "Birds");
  touch(&f, "Sparrow");
  touch(&f, "Crow");

  ls(f, ".");
  printf("\n");

  rmfs(&f);

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes :(. \n", mallinfo().uordblks);
  else printf("No memory leak detected :).\n");

  return 0;
}
