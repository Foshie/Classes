/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 02 (public02.c)
 *
 * Creates a polynomial with some positive terms and prints it.
 */

#include <stdio.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new();

  add_term(&poly1, 20, 6);
  add_term(&poly1, 6.7543, 5);
  add_term(&poly1, 5.2, 3);
  add_term(&poly1, 4, 1);
  add_term(&poly1, 3, 0);

  printf("poly1 is: ");
  print(poly1);
  printf("\n");

  clear(&poly1);

  return 0;
}
