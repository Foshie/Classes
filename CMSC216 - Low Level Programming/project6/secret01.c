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
  int original[1000];
  int sorted[1000];
  int i,j=999;
  Compare_fn my_cmp = cmp;

  for(i = 0 ; i < 1000 ; i++) {
    original[i] = j--;
    sorted[i] = i;
  } 

  mergesort(&original[0], 1000 , sizeof(int) ,
	    my_cmp);

  for (i = 0; i < 1000 ; i++) {
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
