/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 04 (public04.c)
 *
 * Creates polynomials with some positive and negative terms added in
 * different orders and prints them.
 */

#include <stdio.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new(), poly2= new();

  add_term(&poly1, 2, 2);
  add_term(&poly1, -3.6, 3);
  add_term(&poly1, 5, 1);
  add_term(&poly1, -6, 5);

  printf("poly1 is: ");
  print(poly1);
  printf("\n");

  add_term(&poly2, 8, 5);
  add_term(&poly2, 0, 4);
  add_term(&poly2, -4, 3);
  add_term(&poly2, 3, 7);
  add_term(&poly1, 2.5, 2);

  printf("poly2 is: ");
  print(poly2);
  printf("\n");

  clear(&poly1);
  clear(&poly2);

  return 0;
}
