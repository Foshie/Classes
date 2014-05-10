/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 07 (public07.c)
 *
 * Tests adding terms to an existing polynomial.
 */

#include <stdio.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new();

  /* Creating a polynomial */

  add_term(&poly1, 5, 4);
  add_term(&poly1, -3.6, 3);
  add_term(&poly1, 5, 2);
  add_term(&poly1, 2, 0);

  printf("poly1 is: ");
  print(poly1);
  printf("\n");

  /* Adding terms to the created polynomial */

  add_term(&poly1, -8, 4);
  add_term(&poly1, 7, 3);
  add_term(&poly1, -4, 2);
  add_term(&poly1, 3, 0);

  printf("poly1 after adding the terms is: ");
  print(poly1);
  printf("\n");

  clear(&poly1);

  return 0;
}
