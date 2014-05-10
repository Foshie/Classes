/*
 * CMSC 212, Spring 2010, Project #3
 * Public test 10 (public10.c)
 *
 * Uses the num_terms() to find the number of terms in several polynomials.
 */

#include <stdio.h>
#include "polynomial.h"

int main() {
  Polynomial poly1= new(), poly2= new(), poly3= new();
  int i, expected_answers[3]= {4, 1, 0}, ret[3], error= 0;

  /* Creates two new polynomials */

  add_term(&poly1, 5, 7);
  add_term(&poly1, -3, 3);
  add_term(&poly1, 6, 2);
  add_term(&poly1, -4, 0);

  add_term(&poly2, -8, 3);

  ret[0]= num_terms(poly1);
  ret[1]= num_terms(poly2);
  ret[2]= num_terms(poly3);

  for (i=  0; i < 3; i++)
    if (ret[i] != expected_answers[i])
      error= i + 1;

  if (error != 0)
    printf("Unexpected number of terms for polynomial %d, %d instead of %d.\n",
           error, ret[error - 1], expected_answers[error - 1]);
  else
    printf("Correct.  The number of terms are %d, %d, and %d respectively.\n",
           ret[0], ret[1], ret[2]);

  clear(&poly1);
  clear(&poly2);
  clear(&poly3);

  return 0;
}
