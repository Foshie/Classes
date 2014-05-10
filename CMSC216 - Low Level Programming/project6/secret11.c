#include <stdio.h>
#include <err.h>
#include <sysexits.h>
#include <stdlib.h>
#include <string.h>
#include <mcheck.h>
#include <malloc.h>
#include "mergesort.h"

#define ARR_SIZE 10000

static int cmp(const void * a, const void * b) {
  return *(char *) a - *(char *) b;
}

int main() {
  char *original;
  char *result;
  int i;
  size_t memory_used;
  Compare_fn my_cmp;

  mcheck_pedantic(NULL);
  memory_used = mallinfo().uordblks;

  my_cmp = cmp;

  original = malloc(ARR_SIZE);
  result = malloc(ARR_SIZE);
  if (!original || !result) {
    err(EX_OSERR, "error allocating memory");
  }

  srand(3);
  for (i = 0; i < ARR_SIZE; i++) {
    original[i] = rand() % 10 + 49; /* get char '0' through '9' */
  }

  memcpy(result, original, ARR_SIZE);

  qsort(result, ARR_SIZE, sizeof(*result), my_cmp);

  mergesort(original, ARR_SIZE, sizeof(*original), my_cmp);

  for (i = 0; i < ARR_SIZE; i++) {
    if (original[i] != result[i]) {
      printf("The sorted array does not match the expected result\n");
      break;
    }
  }

  if (i == ARR_SIZE)
    printf("All elements in the sorted array match the expected result\n");

  free(original);
  free(result);

  memory_used = mallinfo().uordblks - memory_used;
  if (memory_used)
    printf("Detected memory leak (%d bytes)\n", (int) memory_used);
  else
    printf("No memory leak detected!\n");

  return 0;
}
