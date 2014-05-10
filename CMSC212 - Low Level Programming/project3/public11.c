/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 11 (public11.c)
 *
 * Uses the degree() function to find the degree of several polynomials.
 */

#include <stdio.h>
#include<limits.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new(), poly2= new(), poly3= new();
  int i, expected_answers[3]= {5, 0, 1}, ret[3], error= 0;

  /* Creates new polynomials */

  add_term(&poly1, 5.2, 5);
  add_term(&poly1, -4, 3);
  add_term(&poly1, 5, 1);
  add_term(&poly1, -7, 0);

  add_term(&poly2, -2, 0);

  add_term(&poly3, 4, 1);
  add_term(&poly3, 2, 0);

  ret[0]= degree(poly1);
  ret[1]= degree(poly2);
  ret[2]= degree(poly3);

  for (i=  0; i < 3; i++)
    if (ret[i] != expected_answers[i])
      error= i + 1;

  if (error != 0)
    printf("Unexpected degree for polynomial %d, %d instead of %d.\n",
           error, ret[error - 1], expected_answers[error - 1]);
  else
    printf("Correct.  The degrees are %d, %d and %d respectively.\n", ret[0],
           ret[1], ret[2]);

  clear(&poly1);
  clear(&poly2);
  clear(&poly3);

  return 0;
}
