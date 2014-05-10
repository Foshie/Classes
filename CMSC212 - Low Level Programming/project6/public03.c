/*
 * CMSC 212, Spring 2010, Project #6
 * Public test 03 (public03.c)
 *
 * Creates a Hash_map and calls get() with keys that are not present, to
 * ensure that it didn't modify its parameter "value".  Checks for memory
 * leaks and validity of the heap.
 *
 * Do NOT link this test with either array-hash-map.o or linked-hash-map.o,
 * however, you must set the symbolic link libhash-map.so to point to
 * libarray-hash-map.so before running this test!
 */

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <mcheck.h>
#include "hash-map.h"
#include "iterator.h"

static int int_compare(const Key a, const Key b);
static Hash_map create_example_hash_map(void);

int int_compare(const Key a, const Key b) {
  return ((int) (long) a - (int) (long) b);
}

Hash_map create_example_hash_map(void) {
  Hash_map new_map;

  new_map= create(int_compare, NULL, int_compare, NULL);

  put(&new_map, (Key) (long) 2, (Data) (long) 3);

  return new_map;
}

int main() {
  Hash_map hash_map;
  Data data= (Data) 123;

  mcheck_pedantic(NULL);

  hash_map= create_example_hash_map();

  if (!get(&hash_map, (Key) (long) 1, &data) &&
      !get(&hash_map, (Key) (long) 3, &data) &&
      data == (Data) 123)
    printf("Your hash_map is fine! :)\n");
  else printf("Your hash_map is not working right :(\n");

  clear(&hash_map);

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes. :(\n", mallinfo().uordblks);
  else printf("No memory leak detected. :)\n");

  return 0;
}
