/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 01 (public01.c)
 *
 * Creates a polynomial with one positive non-constant term and prints
 * it.
 */

#include <stdio.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new();

  add_term(&poly1, 4, 3);

  printf("poly1 is: ");
  print(poly1);
  printf("\n");

  clear(&poly1);

  return 0;
}
