#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>



int main() {
  
  Table *t;
  char *get_val = NULL;
  
  t = create_table();
  printf("Search for %s, %d\n", "a", search(t, "a", &get_val));

  printf("Insertion for %s, testValue = %s, result=%d\n", "a", "b", insert(t, "a", "b"));
  
  printf("Search for %s, %d\n", "a", search(t, "a", &get_val));

  reset_table(t);

  printf("Key count of table is %d\n", key_count(t));
	
  free(get_val);
  destroy_table(t);

  return 0;
}
