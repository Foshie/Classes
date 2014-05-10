/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 08 (public08.c)
 *
 * Uses the add() function to add two polynomials with no like terms.
 */

#include <stdio.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new(), poly2= new(), r;

  /* Creates two new polynomials */

  add_term(&poly1, 5, 7);
  add_term(&poly1, -3, 3);
  add_term(&poly1, 6, 2);
  add_term(&poly1, -4, 0);

  printf("poly1 is: ");
  print(poly1);
  printf("\n");

  add_term(&poly2, -8, 6);
  add_term(&poly2, 1, 5);
  add_term(&poly2, -3.4, 4);
  add_term(&poly2, -4, 1);

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

  return 0;
}
