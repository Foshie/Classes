/*
 * CMSC 212, Spring 2010, Project #6
 * Public test 13 (public13.c)
 *
 * Creates a Hash_map with several elements. Looks up several elements using
 * two iterators and makes sure that the two iterators each maintain their
 * own state.
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

#define NUM 25

static int int_compare(const Key a, const Key b);
static Hash_map create_example_hash_map(void);

int int_compare(const Key a, const Key b) {
  return ((int) (long) a - (int) (long) b);
}

Hash_map create_example_hash_map(void) {
  Hash_map new_map;
  int i, power_of_two= 1;

  new_map= create(int_compare, NULL, int_compare, NULL);

  for (i= 0; i < NUM; i++, power_of_two *= 2)
    /* not bothering to check return value */
    put(&new_map, (Key) (long) i, (Data) (long) power_of_two);

  return new_map;
}

int main() {
  Hash_map hash_map;
  Data data1, data2;
  Iterator iter1, iter2;
  int i, expected_value1= 1, expected_value2= 1, correct= 1;

  mcheck_pedantic(NULL);

  hash_map= create_example_hash_map();

  i= 0;
  iter1= create_iterator(hash_map);
  for (i= 0; i < 5 && correct; i++) {
    data1= next(&iter1);
    if ((int) *((long *) data1) != expected_value1)
      correct= 0;
    expected_value1 *= 2;
  }

  iter2= create_iterator(hash_map);
  while ((has_next(iter1) || has_next(iter2)) && correct) {

    if (has_next(iter1)) {
      data1= next(&iter1);
      if ((int) *((long *) data1) != expected_value1)
        correct= 0;
      expected_value1 *= 2;
    }

    if (has_next(iter2)) {
      data2= next(&iter2);
      if ((int) *((long *) data2) != expected_value2)
        correct= 0;
      expected_value2 *= 2;
    }

  }

  clear(&hash_map);

  clear_iterator(&iter1);
  clear_iterator(&iter2);

  if (correct)
    printf("Correct values were accessed by two simultaneous iterators! :)\n");
  else printf("Incorrect results found with two simultaneous iterators. :(\n");

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes. :(\n", mallinfo().uordblks);
  else printf("No memory leak detected. :)\n");

  return 0;
}
