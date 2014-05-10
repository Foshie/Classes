/*
 * CMSC 212, Spring 2010, Project #6
 * Public test 11 (public11.c)
 *
 * Creates a Hash_map with several elements. doubles the values associated
 * with the keys while iterating over it, and verifies the sum of the new
 * values by iterating over them.
 *
 * Do NOT link this test with either array-hash-map.o or linked-hash-map.o,
 * however, you must set the symbolic link libhash-map.so to point to
 * libarray-hash-map.so before running this test!
 */

#include <stdio.h>
#include <malloc.h>
#include <mcheck.h>
#include "hash-map.h"
#include "iterator.h"

#define NUM 20

static int int_compare(const Key a, const Key b);
static Hash_map create_example_hash_map(void);

int int_compare(const Key a, const Key b) {
  return ((int) (long) a - (int) (long) b);
}

Hash_map create_example_hash_map(void) {
  Hash_map new_map;
  int i;

  new_map= create(int_compare, NULL, int_compare, NULL);

  for (i= 0; i < NUM; i++)
    /* not bothering to check return value */
    put(&new_map, (Key) (long) i, (Data) (long) (i*i));

  return new_map;
}

int main() {
  Hash_map hash_map;
  Data data;
  Iterator iter;
  int i= 0, sum= 0, expected_sum= 4940;

  mcheck_pedantic(NULL);

  hash_map= create_example_hash_map();

  iter= create_iterator(hash_map);

  while (has_next(iter)) {
    data= next(&iter);
    *((int *) data)= ((int) *((long *) data)) * 2;
    i++;
  }

  reset(&iter);
  while (has_next(iter)) {
    data= next(&iter);
    sum += (int) *((long *) data);
  }

  clear(&hash_map);

  clear_iterator(&iter);

  if (sum == expected_sum)
    printf("The elements were modified correctly! :)\n");
  else printf("The elements were not modified correctly. :(\n");

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes. :(\n", mallinfo().uordblks);
  else printf("No memory leak detected. :)\n");

  return 0;
}
