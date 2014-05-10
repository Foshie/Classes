/*
 * CMSC 212, Spring 2010, Project #5
 * Secret test 05 (secret05.c)
 *
 * Creates an Array_hash_map with several elements, and checks put() by
 * calling it with an existing key and seeing if it replaces the value
 * associated with it rather than creating a new key/value pair.  Checks for
 * memory leaks and validity of the heap.
 *
 * You must link this test with array-hash-map.o!
 */

#include <stdio.h>
#include <malloc.h>
#include <mcheck.h>
#define ARRAY_HASH_MAP
#include "hash-map.h"

#define NUM_ITEMS 7

static int int_compare(const Key a, const Key b);
static int char_compare(const Key a, const Key b);
static Hash_map create_example_hash_map(char keys[], int values[]);

int int_compare(const Key a, const Key b) {
  return ((int) (long) a - (int) (long) b);
}

int char_compare(const Data a, const Data b) {
  return ((char) (long) a - (char) (long) b);
}

Hash_map create_example_hash_map(char keys[], int values[]) {
  Hash_map new_map;
  int i;

  new_map= create(int_compare, NULL, char_compare, NULL);

  for (i= 0; i < NUM_ITEMS; i++)
    /* not bothering to check return value */
    put(&new_map, (Key) (long) keys[i], (Data) (long) values[i]);

  return new_map;
}

int main() {
  Hash_map hash_map;
  Data data;
  int i, correct= 1;
  char chars[NUM_ITEMS]= {'q', 'w', 'e', 'r', 't', 'y', 'u'};
  int offsets[NUM_ITEMS]= {8, 1, 2, 10, 4, 5, 9};

  mcheck_pedantic(NULL);

  hash_map= create_example_hash_map(chars, offsets);

  for (i= 0; i < NUM_ITEMS; i += 3)
    put(&hash_map, (Key) (long) chars[i], (Data) (long) i);

  for (i= 0; i < NUM_ITEMS; i += 3) {
    get(&hash_map, (Key) (long) chars[i], &data);
    if ((int) (long) data == offsets[i])
      correct= 0;
  }

  if (size(hash_map) == 7 && current_capacity(hash_map) == 10 && correct == 1)
    printf("No new key/value pair created and hash_map looks fine! :)\n");
  else printf("New key/value pair was created or value not replaced. :(\n");

  clear(&hash_map);

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes detected. :(\n", mallinfo().uordblks);
  else printf("No memory leak detected. :)\n");

  return 0;
}
