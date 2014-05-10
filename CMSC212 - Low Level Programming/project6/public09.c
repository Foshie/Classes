/*
 * CMSC 212, Spring 2010, Project #6
 * Public test 09 (public09.c)
 *
 * Tests resetting an iterator.  Creates a Hash_map with several elements,
 * iterates through some of them with an iterator, resets the iterator to
 * the beginning of the Hash_map, and iterates through all of the elements.
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

#define NUM 10

static int int_compare(const Key a, const Key b);
static int char_compare(const Key a, const Key b);
static Hash_map create_example_hash_map(void);

int int_compare(const Key a, const Key b) {
  return ((int) (long) a - (int) (long) b);
}

int char_compare(const Data a, const Data b) {
  return ((char) (long) a - (char) (long) b);
}

Hash_map create_example_hash_map(void) {
  Hash_map new_map;
  int i;
  char chars[NUM]= {'q', 'w', 'e', 'r', 't', 'y', 'u', 'a', 'b', 'c'};
  int offsets[NUM]= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  new_map= create(char_compare, NULL, int_compare, NULL);

  for (i= 0; i < NUM; i++)
    /* not bothering to check return value */
    put(&new_map, (Key) (long) chars[i], (Data) (long) offsets[i]);

  return new_map;
}

int main() {
  Hash_map hash_map;
  Data data;
  Iterator iter;
  int i, correct= 1;
  int sorted_offsets[NUM]= {7, 8, 9, 2, 0, 3, 4, 6, 1, 5};

  mcheck_pedantic(NULL);

  hash_map= create_example_hash_map();

  iter= create_iterator(hash_map);
  for (i= 0; i < 5 && correct; i++) {
    data= next(&iter);
    if ((int) *((long *) data) != sorted_offsets[i])
      correct= 0;
  }

  if (!get(&hash_map, (Key) (long) 'a', &data) || data != (Data) 7 ||
      !get(&hash_map, (Key) (long) 'q', &data) || data != (Data) 0 ||
      !get(&hash_map, (Key) (long) 'c', &data) || data != (Data) 9)
    correct= 0;

  reset(&iter);

  for (i= 0; i < NUM && correct; i++) {
    data= next(&iter);
    if ((int) *((long *) data) != sorted_offsets[i])
      correct= 0;
  }

 if (correct && !has_next(iter))
    printf("Correct values were accessed when iterating! :)\n");
  else printf("Incorrect results occurred when iterating. :(\n");

  clear(&hash_map);

  clear_iterator(&iter);

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes. :(\n", mallinfo().uordblks);
  else printf("No memory leak detected. :)\n");

  return 0;
}
