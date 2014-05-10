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
  int * original = NULL;
  int * sorted = NULL ;
  int i;
  Compare_fn my_cmp = cmp;

  mergesort(&original[0], 0, 4, my_cmp);

  for (i = 0; i < 0 ; i++) {
    if (original[i] == sorted[i]) {
      printf("CORRECT: ");
    }
    else {
      printf("INCORRECT: ");
    }
    printf("After sorting, arr[%d] == %d, should be %d\n",
	   i, original[i], sorted[i]);
  }
  if(original == NULL )
    printf("CORRECT: ");
  else
    printf("INCORRECT: ");
  printf("After sorting, arr == NULL, should be NULL\n");

  return 0;
}
