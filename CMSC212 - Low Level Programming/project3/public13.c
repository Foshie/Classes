/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 13 (public13.c)
 *
 * Tests differentiating a polynomial.
 */

#include <stdio.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new(),s;

  add_term(&poly1, 6, 4);
  add_term(&poly1, -3, 3);
  add_term(&poly1, 3.5, 2);

  printf("poly1 is: ");
  print(poly1);
  printf("\n");

  s= differentiate(poly1);

  printf("poly1' is: ");
  print(s);
  printf("\n");

  clear(&poly1);
  clear(&s);

  return 0;
}
