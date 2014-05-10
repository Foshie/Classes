#include <stdio.h>
#include <string.h>
#include "mergesort.h"

typedef struct {
    int x, y;
} point2D;

/* comparison according to Euclidean distance to origin */
static int cmp(const void * a, const void * b) {
  int dist1, dist2;
  point2D *first = (point2D *) a;
  point2D *second = (point2D *) b;

  dist1 = first->x * first->x + first->y * first->y;
  dist2 = second->x * second->x + second->y * second->y;

  return dist1 - dist2;
}

int main() {
  point2D original[] = {{5,3}, {2,8}, {4,0}, {-3,4}, {12,-5}, {-1,1}, {1,0}};
  point2D sorted[] = {{1,0}, {-1,1}, {4,0}, {-3,4}, {5,3}, {2,8}, {12,-5}};
  int i;
  Compare_fn my_cmp = cmp;

  mt_mergesort(&original[0], sizeof (original) / sizeof (*original),
            sizeof (*original), my_cmp, 2);

  for (i = 0; i < sizeof(original)/sizeof(*original); i++) {
    if (original[i].x == sorted[i].x && original[i].y == sorted[i].y) {
      printf("CORRECT: ");
    }
    else {
      printf("INCORRECT: ");
    }
    printf("After sorting, arr[%d] == (%d,%d), should be (%d,%d)\n",
	   i, original[i].x, original[i].y, sorted[i].x, sorted[i].y);
  }

  return 0;
}

