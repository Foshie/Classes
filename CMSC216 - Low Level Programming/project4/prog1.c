#include <stdio.h>

int main() {
  int x, y, tmp;

  scanf("%d", &x);
  scanf("%d", &y);

  /* Want x >= y */
  if (x < y) {
    tmp = x;
    x = y;
    y = tmp;
  }

  while (1) {
    tmp = x % y;
    if (tmp == 0) {
      printf("%d\n", y);
      break;
    }

    x = y;
    y = tmp;
  }

  return 0;
}
