/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 03 (public03.c)
 *
 * Creates polynomials with some positive and negative terms and prints
 * them.
 */

#include <stdio.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new(), poly2= new();

  add_term(&poly1, 7, 4);
  add_term(&poly1, -8, 3);
  add_term(&poly1, -5, 2);
  add_term(&poly1, 6, 1);

  printf("poly1 is: ");
  print(poly1);
  printf("\n");

  add_term(&poly2, 9, 6);
  add_term(&poly2, -7, 4);
  add_term(&poly2, 5, 2);
  add_term(&poly2, -3, 0);

  printf("poly2 is: ");
  print(poly2);
  printf("\n");

  clear(&poly1);

  return 0;
}
