#include <stdio.h>

int main() {
  int arr[500];
  int i, n, key;

  scanf("%d", &n);
  scanf("%d", &key);
  for (i = 0; i < n; i++)
    scanf("%d", arr + i);
  for (i = 0; i < n; i++) {
    if (arr[i] < key)
      printf("%d ", arr[i]);
  }
  for (i = 0; i < n; i++) {
    if (arr[i] == key)
      printf("%d ", arr[i]);
  }
  for (i = 0; i < n; i++) {
    if (arr[i] > key)
      printf("%d ", arr[i]);
  }

  printf("\n");

  return 0;
}

int main(){

  scanf(n);
  if(n==0)
    jump to Print
  scanf(key);
  int i = 0;
  
  Loop1{
    scanf(arr+i);
    i = i+1;
    if(i-n <0)
      goto Loop1;
  }
  i=0;
  Loop2{
    if(arr[i]-key > 0)
      goto Loop2Check;
    printf(arr[i]);
    printf(" ");
    Loop2Check{
      i = i+1;
      if(i-n <0)
	goto Loop2;
    }
  }
  i=0;
  Loop3{
    if(arr[i]-key<0)
      goto Loop3Check;
    printf(arr[i]);
    printf(" ");
    Loop3Check{
      i=i+1;
      if(i-n<0)
	goto Loop3;
    }
  }

  printf(/*Delete 1 space*/);
 Print:
  printf("\n");
  return 0;
}
