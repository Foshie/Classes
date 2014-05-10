/*
 * CMSC 212, Spring 2010, Project #5
 * Public test 01 (public01.c)
 *
 * Creates an Array_hash_map with one element, and checks its size and its
 * capacity.  Integer keys and values are used, so the same comparison
 * function works for both keys and values.
 *
 * You must link this test with array-hash-map.o!
 */

#include <stdio.h>
#define ARRAY_HASH_MAP
#include "hash-map.h"

static int int_compare(const Key a, const Key b);

int int_compare(const Key a, const Key b) {
  return ((int) (long) a - (int) (long) b);
}

int main() {
  Hash_map hash_map;
  int size_ans, capacity_ans;

  hash_map= create(int_compare, NULL, int_compare, NULL);

  /* not bothering to check return value */
  put(&hash_map, (Key) 212, (Data) 1);

  size_ans= size(hash_map);
  capacity_ans= current_capacity(hash_map);

  if (size_ans == 1 && capacity_ans == 10)
    printf("Hash_map size and capacity are correct!\n");
  else
    if (size_ans != 1)
      printf("Hash_map size was %d, 1 was expectec.\n", size_ans);
    else printf("Hash_map capacity was %d, 10 was expected.\n", capacity_ans);

  clear(&hash_map);

  return 0;
}
