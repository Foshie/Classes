/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 15 (public15.c)
 *
 * Adds terms to an existing polynomial and checks for memory leaks.
 */

#include <stdio.h>
#include <malloc.h>
#include <mcheck.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new();
  unsigned int initial_mem, mem_used;

  mcheck_pedantic(NULL);

  initial_mem= mallinfo().uordblks;

  add_term(&poly1, 4, 5);
  add_term(&poly1, -3, 4);
  add_term(&poly1, 4, 3);

  printf("poly1: ");
  print(poly1);
  printf("\n");

  add_term(&poly1, -4, 5);

  printf("poly1 after adding -4x^5 is: ");
  print(poly1);
  printf("\n");

  add_term(&poly1, -4, 3);

  printf("poly1 after adding -4x^3 is: ");
  print(poly1);
  printf("\n");

  add_term(&poly1, 3, 4);

  printf("poly1 after adding 3x^4 is: ");
  print(poly1);
  printf("\n");

  clear(&poly1);

  mem_used= mallinfo().uordblks - initial_mem;

  if (mem_used != 0)
    printf("Memory leak of %d bytes :(.\n", mem_used);
  else printf("No memory leak detected :).\n");

  return 0;
}
