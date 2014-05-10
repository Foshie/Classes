#include <stdio.h>
#include <string.h>
#include "mergesort.h"

typedef struct {
    char *dept;
    int code;
    double section;
} course;


static int cmp(const void * a, const void * b) {
  int retval;
  course *x = (course *) a;
  course *y = (course *) b;

  retval = strcmp(x->dept, y->dept);
  if (retval) return retval;
  if (x->code - y->code) return x->code - y->code;
  if(x->section < y->section) return -1;
  if(x->section == y->section) return 0;
  return 1;
}

int main() {
  course original[] = {{"CMSC", 250, 1.1}, {"MATH", 101, 1.2}, {"CMSC", 216, 1.2}, {"MATH", 101, 1.3}};
  course sorted[] =   {{"CMSC", 216, 1.2}, {"CMSC", 250, 1.1}, {"MATH", 101, 1.2}, {"MATH", 101, 1.3}};
  int i;
  Compare_fn my_cmp = cmp;

  mergesort(&original[0], sizeof (original) / sizeof (*original),
            sizeof (*original), my_cmp);

  for (i = 0; i < sizeof(original)/sizeof(*original); i++) {
    if (strcmp(original[i].dept, sorted[i].dept) == 0 &&
            original[i].code == sorted[i].code &&
	    original[i].section == sorted[i].section) {
      printf("CORRECT: ");
    }
    else {
      printf("INCORRECT: ");
    }
    printf("After sorting, arr[%d] == %s %d %f, should be %s %d %f\n",
	   i, original[i].dept, original[i].code, original[i].section,
           sorted[i].dept, sorted[i].code, sorted[i].section);
  }

  return 0;
}

