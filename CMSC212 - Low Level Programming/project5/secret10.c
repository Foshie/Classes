/*
 * CMSC 212, Spring 2010, Project #5
 * Secret test 10 (secret10.c)
 *
 * Creates a Linked_hash_map with several elements, removes all its keys,
 * then adds more elements.  Looks up the elements that were re-added.
 * Checks for memory leaks and validity of the heap.
 *
 * You must link this test with array-hash-map.o!
 */

#include <stdio.h>
#include <malloc.h>
#include <mcheck.h>
#include <limits.h>
#define LINKED_HASH_MAP
#include "hash-map.h"

#define NUM_ITEMS 8

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
  char chars[NUM_ITEMS]= {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i'};
  int offsets[NUM_ITEMS]= {0, 1, 2, 3, 4, 5, 6, 7};

  mcheck_pedantic(NULL);

  hash_map= create_example_hash_map(chars, offsets);

  for (i= 0; i < NUM_ITEMS; i++)
   remove_key(&hash_map, (Key) (long) chars[i]);

  for (i= 0; i < NUM_ITEMS; i += 2)
    put(&hash_map, (Key) (long) chars[i], (Data) (long) offsets[i]);

  for (i= 0; i < NUM_ITEMS && correct; i += 2) {
    get(&hash_map, (Key) (long) chars[i], &data);
    if ((int) (long) data != i)
      correct= 0;
  }

  if (size(hash_map) == 4 && current_capacity(hash_map) == INT_MAX && correct)
    printf("Hash_map seems to be correct!\n");
  else printf("Hash_map is incorrect.\n");

  clear(&hash_map);

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes detected. :(\n", mallinfo().uordblks);
  else printf("No memory leak detected. :)\n");

  return 0;
}
