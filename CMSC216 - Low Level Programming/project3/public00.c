#include "hashtable.h"
#include <stdio.h>

int main() {
  printf("Inserting NULL: %d\n", insert(NULL, NULL, NULL));
  printf("Searching NULL: %d\n", search(NULL, NULL, NULL));
  printf("Deleting NULL: %d\n", delete(NULL, NULL));
  printf("Key count of NULL: %d\n", key_count(NULL));
  printf("Bucket count of NULL: %d\n", bucket_count(NULL));

  return 0;
}

