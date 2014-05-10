#include <stdio.h>
#include "mergesort.h"


static int cmp(const void * a, const void * b) {
  long *x = (long *) a;
  long *y = (long *) b;

  if ( *x > *y) return 1;
  if (*x == *y) return 0;
  return -1;
}

int main() {
  long original[1467];
  int i;

  for (i = 0; i < 1467; i++) {
    original[i] = 143244 - i;
  }

  mt_mergesort(original, sizeof(original)/sizeof(*original), sizeof(*original),
	       cmp, 4);

  for (i = 0; i < sizeof(original)/sizeof(*original); i++) {
    if (original[i] == 141778 + i) {
      printf("CORRECT: ");
    }
    else {
      printf("INCORRECT: ");
    }
    printf("After sorting, arr[%d] == %ld, should be %ld\n",
	   i, original[i], 141778L + i);
  }

  return 0;
}
