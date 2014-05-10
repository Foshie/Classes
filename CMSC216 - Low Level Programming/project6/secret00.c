#include <stdio.h>
#include "mergesort.h"


static int cmp(const void * a, const void * b) {
  int *x = (int *) a;
  int *y = (int *) b;

  if ( *x > *y) return 1;
  if (*x == *y) return 0;
  return -1;
}

int main() {
  int original[] = {9000,8000,7000,6000,5000,4000,3000,2000,1000,0};
  int sorted[] = {0,1000,2000,3000,4000,5000,6000,7000,8000,9000};
  int i;
  Compare_fn my_cmp = cmp;

  mergesort(&original[0], sizeof(original)/sizeof(*original), sizeof(*original),
	    my_cmp);

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
