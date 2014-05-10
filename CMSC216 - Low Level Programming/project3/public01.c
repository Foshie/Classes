#include "hashtable.h"
#include <stdio.h>

int main()
{
  Table *t ;
  char **array;
  int i = 0 ;

  t = create_table();
  printf("Insert sapple = %d\n",insert(t, "sapple", "fruit"));
  printf("Insert tapple = %d\n",insert(t, "tapple", "mruit"));
  printf("Insert kapple = %d\n",insert(t, "kapple", "jmruit"));
  printf("Insert iapple = %d\n",insert(t, "iapple", "truit"));
  printf("Insert japple = %d\n",insert(t, "japple", "sruit"));
  printf("Count: %d\n", key_count(t));
  array = get_keys(t);

  printf("Keys : ");
  for(i=0; i<t->key_ct; i++)
    printf("%s ", array[i]);
  printf("\n");


  array = get_values(t);

  printf("Values : ");
  for(i=0; i<t->key_ct; i++)
    printf("%s ", array[i]);
  printf("\n");

  return 0;

}
