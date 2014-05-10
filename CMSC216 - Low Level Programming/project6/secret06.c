#include <stdio.h>
#include "mergesort.h"


static int cmp(const void * a, const void * b) {
  double *x = (double *) a;
  double *y = (double *) b;

  if ( *x > *y) return 1;
  if (*x == *y) return 0;
  return -1;
}

int main() {
  double original[] = {3.14};
  double sorted[] = {3.14};
  int i;
  Compare_fn my_cmp = cmp;

  mt_mergesort(&original[0], sizeof(original)/sizeof(*original), sizeof(*original),
	    my_cmp,4);

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
