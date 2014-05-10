/*
 * CMSC 212, Spring 2010, Project #6
 * Public test 01 (public01.c)
 *
 * Creates an empty Hash_map and calls some of the functions on it, checking
 * the return value and ensuring that the functions did not change their
 * parameters' values.  Checks for memory leaks and validity of the heap.
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

static int int_compare(const Key a, const Key b);
static Hash_map create_example_hash_map(void);

int int_compare(const Key a, const Key b) {
  return ((int) (long) a - (int) (long) b);
}

Hash_map create_example_hash_map(void) {
  Hash_map new_map;

  new_map= create(int_compare, NULL, int_compare, NULL);

  return new_map;
}

int main() {
  Hash_map hash_map;
  Data data= (Data) 123;
  Key key= (Key) 456;

  mcheck_pedantic(NULL);

  hash_map= create_example_hash_map();

  /* calling some of the functions with an empty Hash_map */
  if (!get(&hash_map, (Key) (long) 1, &data) &&
      !get_smallest(hash_map, &key, &data) &&  num_keys(hash_map, 0) == 0 &&
      index_of(hash_map, (Key) (long) 5) == -1 && data == (Data) 123 &&
      key == (Key) 456)
    printf("Your functions can handle an empty hash_map correctly!\n");
  else printf("Oops!  Error in handling anempty hash_map.\n");

  clear(&hash_map);

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes. :(\n", mallinfo().uordblks);
  else printf("No memory leak detected. :)\n");

  return 0;
}
