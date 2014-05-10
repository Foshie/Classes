/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 06 (public06.c)
 *
 * Creates a polynomial with coefficients of 1, and one with a constant term
 * 1, and prints them.
 */

#include <stdio.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new(), poly2= new();

  add_term(&poly1, 1, 4);
  add_term(&poly1, 1, 5);
  add_term(&poly1, 1, 2);
  add_term(&poly1, -1, 1);

  printf("poly1 is: ");
  print(poly1);
  printf("\n");

  add_term(&poly2, 1, 0);

  printf("poly2 is: ");
  print(poly2);
  printf("\n");

  clear(&poly1);
  clear(&poly2);

  return 0;
}
