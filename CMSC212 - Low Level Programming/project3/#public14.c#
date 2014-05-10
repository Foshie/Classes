/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 14 (public14.c)
 *
 * Adds two existing polynomial and checks for memory leaks.
 */

#include <stdio.h>
#include <malloc.h>
#include <mcheck.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new(), poly2= new(), r;
  unsigned int initial_mem, mem_used;

  mcheck_pedantic(NULL);

  initial_mem= mallinfo().uordblks;

  add_term(&poly1, 6, 6);
  add_term(&poly1, 3, 4);
  add_term(&poly1, -2, 3);
  add_term(&poly1, -5, 2);
  add_term(&poly1, 10, 1);
  add_term(&poly1, -8, 0);

  printf("poly1 is: ");
  print(poly1);
  printf("\n");

  add_term(&poly2, 8, 0);
  add_term(&poly2, -6, 6);
  add_term(&poly2, 5, 5);
  add_term(&poly2, -3, 4);
  add_term(&poly2, 4, 7);
  add_term(&poly2, 5, 2);

  printf("poly2 is: ");
  print(poly2);
  printf("\n");

  r= add(poly1, poly2);

  printf("poly1 + poly2 is: ");
  print(r);
  printf("\n");

  clear(&poly1);
  clear(&poly2);
  clear(&r);

  mem_used= mallinfo().uordblks - initial_mem;

  if (mem_used != 0)
    printf("Memory leak of %d bytes :(.\n", mem_used);
  else printf("No memory leak detected :).\n");

  return 0;
}
