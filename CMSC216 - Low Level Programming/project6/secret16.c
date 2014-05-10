#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"


static int cmp(const void * a, const void * b) {
  int *x = (int *) a;
  int *y = (int *) b;

  if ( *x > *y) return 1;
  if (*x == *y) return 0;
  return -1;
}

int main() {
  int original[10001];
  int sorted[10001];
  int i;
  Compare_fn my_cmp = cmp;

  srand(216);
  for (i = 0; i < 10001; i++) {
    original[i] = sorted[i] = rand() / 1000000;
  }

  qsort(&sorted[0], sizeof(sorted)/sizeof(*sorted), sizeof(*sorted), my_cmp);
  mt_mergesort(&original[0], sizeof(original)/sizeof(*original),
            sizeof(*original), my_cmp, 2);

  for (i = 0; i < sizeof(original)/sizeof(*original); i++) {
    if (original[i] == sorted[i]) {
      printf("CORRECT: ");
    }
    else {
      printf("INCORRECT: ");
    }
    printf("After sorting, arr[%d] == %d, should be %d\n",
	   i, original[i], sorted[i]);
  }

  return 0;
}
