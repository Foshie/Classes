#include <stdio.h>
#include <string.h>
#include "mergesort.h"

typedef struct {
    char *dept;
    int code;
} course;


static int cmp(const void * a, const void * b) {
  int retval;
  course *x = (course *) a;
  course *y = (course *) b;

  retval = strcmp(x->dept, y->dept);
  if (retval) return retval;
  return x->code - y->code;
}

int main() {
  course original[] = {{"CMSC", 250}, {"MATH", 101}, {"CMSC", 216}};
  course sorted[] = {{"CMSC", 216}, {"CMSC", 250}, {"MATH", 101}};
  int i;
  Compare_fn my_cmp = cmp;

  mergesort(&original[0], sizeof (original) / sizeof (*original),
            sizeof (*original), my_cmp);

  for (i = 0; i < sizeof(original)/sizeof(*original); i++) {
    if (strcmp(original[i].dept, sorted[i].dept) == 0 &&
            original[i].code == sorted[i].code) {
      printf("CORRECT: ");
    }
    else {
      printf("INCORRECT: ");
    }
    printf("After sorting, arr[%d] == %s%d, should be %s%d\n",
	   i, original[i].dept, original[i].code,
           sorted[i].dept, sorted[i].code);
  }

  return 0;
}

