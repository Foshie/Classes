/*
 * CMSC 212, Spring 2010, Project #5
 * Secret test 14 (secret14.c)
 *
 * Checks the functions that have pointer parameters by passing NULL into
 * them.
 *
 * You must link this test with linked-hash-map.o!
 */

#include <stdio.h>
#include <limits.h>
#define LINKED_HASH_MAP
#include "hash-map.h"

static int int_compare(const Key a, const Key b);

int int_compare(const Key a, const Key b) {
  return ((int) (long) a - (int) (long) b);
}

int main() {
  Hash_map hash_map;

  hash_map= create(int_compare, NULL, int_compare, NULL);

  printf("Let's try passing NULL into some of the Hash_map functions.\n");

  put(NULL, (Key) (long) 1, (Data) (long) 0);
  get(NULL, (Key)(long) 1, NULL);
  remove_key(NULL, (Key) (long) 1);
  get_smallest(hash_map, NULL, NULL);
  clear(NULL);

  if (size(hash_map) == 0 && current_capacity(hash_map) == INT_MAX)
    printf("No problem passing NULL into the functions!\n");
  else printf("Some problem occurred passing NULL into the functions.\n");

  clear(&hash_map);

  return 0;
}
