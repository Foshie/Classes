#include "hashtable.h"
#include <stdio.h>
#include <malloc.h>



int main() {
	
  Table *t;  
  char *key = "A0001test";
  char *value = "TestValue";
  char *get_val = NULL;

  t = create_table();

  printf("Inserting key = %s testValue = %s result = %d\n", key, value,insert(t, key, value));
  printf("Searching key = %s, result = %d\n", key,search(t, key, &get_val));
  printf("Searched value = %s\n", get_val);
  printf("Deleting key = %s, result = %d\n", key, delete(t, key));

  free(get_val);
  get_val = NULL;
  printf("Searching key = %s, result = %d\n", key,search(t, key, &get_val));

  printf("Key count of table is %d\n", key_count(t));
  printf("Bucket count of table is %d\n", bucket_count(t));

  free(get_val);
  destroy_table(t);

  return 0;
}

