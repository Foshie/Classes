#include <stdio.h>
#include <string.h>
#include "mergesort.h"


static int cmpstringp(const void *a, const void *b) {
  return strcmp(* (char * const *) a, * (char * const *) b);
}

int main() {
  char *original[] = {
      "university", "of", "maryland", "college", "park", "computer", "science"
  };
  char *sorted[] = {
      "college", "computer", "maryland", "of", "park", "science", "university"
  };
  int i;

  mergesort(&original[0], sizeof(original)/sizeof(*original), sizeof(*original),
	    cmpstringp);

  for (i = 0; i < sizeof(original)/sizeof(*original); i++) {
    if (strcmp(original[i], sorted[i]) == 0) {
      printf("CORRECT: ");
    }
    else {
      printf("INCORRECT: ");
    }
    printf("After sorting, arr[%d] == %s, should be %s\n",
	   i, original[i], sorted[i]);
  }

  return 0;
}
