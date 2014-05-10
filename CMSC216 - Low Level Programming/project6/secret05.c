#include <stdio.h>
#include "mergesort.h"


static int cmp(const void * a, const void * b) {
  char *x = (char *) a;
  char *y = (char *) b;

  if ( *x > *y) return 1;
  if (*x == *y) return 0;
  return -1;
}

int main() {
  char original[] = {'d'};
  char sorted[] = "d";
  int i;

  mergesort(original, sizeof(original)/sizeof(*original), sizeof(*original),
	    cmp);

  for (i = 0; i < sizeof(original)/sizeof(*original); i++) {
    if (original[i] == sorted[i]) {
      printf("CORRECT: ");
    }
    else {
      printf("INCORRECT: ");
    }
    printf("After sorting, arr[%d] == %c, should be %c\n",
	   i, original[i], sorted[i]);
  }

  return 0;
}
