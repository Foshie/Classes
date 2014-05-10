/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 12 (public12.c)
 *
 * Evaluates the value of several polynomials.
 */

#include <stdio.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new(), poly2= new(), poly3= new();
  int i, expected_answers[3]= {124, 10, 0}, ret[3], error= 0;

  /* Creates new polynomials */

  add_term(&poly1, 4, 3);
  add_term(&poly1, 3, 2);
  add_term(&poly1, -2, 1);
  add_term(&poly1, -5, 0);

  add_term(&poly2, 10, 0);

  ret[0]= evaluate(poly1, 3);
  ret[1]= evaluate(poly2, -4);
  ret[2]= evaluate(poly3, 2);

  for (i=  0; i < 3; i++)
    if (ret[i] != expected_answers[i])
      error= i + 1;

  if (error != 0)
    printf("Unexpected value evaluated for polynomial %d, %d instead of %d.\n",
           error, ret[error - 1], expected_answers[error - 1]);
  else
    printf("Correct.  poly1(3) = %d, poly2(-4) = %d, and poly3(2) = %d.\n",
           ret[0], ret[1], ret[2]);

  clear(&poly1);
  clear(&poly2);

  return 0;
}
