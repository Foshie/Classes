/*
 * CMSC 212, Spring 2010, Project #5
 * Public test 12 (public12.c)
 *
 * Verifies that the required data structures are used, with the order
 * properties described in the project assignment.  Creates a
 * Linked_hash_map with several elements using character keys and integer
 * values, and looks them up afterward, checking the positions or indices of
 * all the elements that were added to ensure that a Linked_hash_map keeps
 * elements in the order that they were added.
 *
 * You must link this test with linked-hash-map.o!
 */

#include <stdio.h>
#include <stdlib.h>
#define LINKED_HASH_MAP
#include "hash-map.h"

#define NUM_ITEMS 7

static int char_compare(const Key a, const Key b);
static int int_compare(const Key a, const Key b);

int char_compare(const Data a, const Data b) {
  return ((char) (long) a - (char) (long) b);
}

int int_compare(const Key a, const Key b) {
  return ((int) (long) a - (int) (long) b);
}

int main() {
  Hash_map hash_map;
  int i, correct= 1;
  char chars[NUM_ITEMS]= {'q', 'w', 'e', 'r', 't', 'y', 'u'};
  int offsets[NUM_ITEMS]= {0, 1, 2, 3, 4, 5, 6};

  hash_map= create(char_compare, NULL, int_compare, NULL);

  for (i= 0; i < NUM_ITEMS; i++)
    /* not bothering to check return value */
    put(&hash_map, (Key) (long) chars[i], (Data) (long) offsets[i]);

  /* now look up elements in the order they should be stored in */
  for (i= 0; i < NUM_ITEMS && correct; i++)
    if (index_of(hash_map, (Key) (long) chars[i]) != i)
      correct= 0;

  clear(&hash_map);

  if (correct)
    printf("Elements in Linked_hash_map are in correct order!\n");
  else printf("Order of elements in Linked_hash_map is incorrect. :(\n");

  return 0;
}
