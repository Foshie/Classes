/*
 * CMSC 212, Spring 2010, Project #4
 * Public test 15 (public15.c)
 *
 * Creates a filesystem with some contents, removes it, creates another
 * filesystem with some contents, and checks for memory leaks and validity
 * of the heap after removing it.
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
  mkdir(&f, "Birds");

  ls(f, "/");
  printf("\n");

  cd(&f, "Animals");
  mkdir(&f, "Herbivores");
  mkdir(&f, "Carnivores");

  ls(f, ".");
  printf("\n");

  cd(&f, "/");
  cd(&f, "Birds");
  touch(&f, "Sparrow");
  touch(&f, "Crow");

  ls(f, ".");
  printf("\n");

  rmfs(&f);

  mkfs(&f);

  mkdir(&f, "Fruits");

  cd(&f, "Fruits");
  touch(&f, "apple");

  ls(f, ".");
  printf("\n");

  rmfs(&f);

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes :(. \n", mallinfo().uordblks);
  else printf("No memory leak detected :).\n");

  return 0;
}
