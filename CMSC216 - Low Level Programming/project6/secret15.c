#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"


static int cmp(const void * a, const void * b) {
  double *x = (double *) a;
  double *y = (double *) b;

  if ( *x > *y) return 1;
  if (*x == *y) return 0;
  return -1;
}

int main() {
  double original[5743];
  double sorted[5743];
  int i;
  Compare_fn my_cmp = cmp;

  srand(5743);
  for (i = 0; i < 5743; i++) {
    original[i] = sorted[i] = rand() * 0.000001;
  }

  qsort(&sorted[0], sizeof(sorted)/sizeof(*sorted), sizeof(*sorted), my_cmp);
  mergesort(&original[0], sizeof(original)/sizeof(*original), sizeof(*original),
	    my_cmp);

  for (i = 0; i < sizeof(original)/sizeof(*original); i++) {
    if (original[i] == sorted[i]) {
      printf("CORRECT: ");
    }
    else {
      printf("INCORRECT: ");
    }
    printf("After sorting, arr[%d] == %f, should be %f\n",
	   i, original[i], sorted[i]);
  }

  return 0;
}
