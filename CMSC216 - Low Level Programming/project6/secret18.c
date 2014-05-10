#include <stdio.h>
#include "mergesort.h"

int main() {
  long original[] = {9,8,7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7,-8,-9};
  long sorted[] = {9,8,7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7,-8,-9};
  int i;

  mergesort(original, sizeof(original)/sizeof(*original), sizeof(*original),
	       NULL);

  for (i = 0; i < sizeof(original)/sizeof(*original); i++) {
    if (original[i] == sorted[i]) {
      printf("CORRECT: ");
    }
    else {
      printf("INCORRECT: ");
    }
    printf("After sorting, arr[%d] == %ld, should be %ld\n",
	   i, original[i], sorted[i]);
  }

  return 0;
}
