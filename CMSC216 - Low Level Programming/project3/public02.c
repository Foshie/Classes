#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>



int main() {
  
  Table *t;  
  char *key = "A00000001";
  char *value = "University of Maryland";
  char *get_val = NULL;
  
  t = create_table();

  printf("Inserting key = %s, testValue = %s, result=%d\n", key, value,insert(t, key, value));
  printf("Searching key = %s, result=%d\n", key, search(t, key, &get_val));
  
  if(get_val)
    printf("Searched value =%s\n", get_val);
  else
    printf("Searched value is not found\n");
  
  printf("Key count of table is %d\n", key_count(t));
  printf("Bucket count of table is %d\n", bucket_count(t));
	
  free(get_val);
  destroy_table(t);

  return 0;
}

