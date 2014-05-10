/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 05 (public05.c)
 *
 * Creates a polynomial with some positive and negative terms, where several
 * add_term() calls have the same exponent value, and prints them.
 */

#include <stdio.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new();

  add_term(&poly1, 2, 2);
  add_term(&poly1, -3.6, 3);
  add_term(&poly1, 5, 0);
  add_term(&poly1, 4, 5);
  add_term(&poly1, -6, 2);
  add_term(&poly1, -3, 3);
  add_term(&poly1, -2, 0);

  printf("poly1 is: ");
  print(poly1);
  printf("\n");

  clear(&poly1);

  return 0;
}
