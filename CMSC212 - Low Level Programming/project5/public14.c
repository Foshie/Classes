/*
 * CMSC 212, Spring 2010, Project #5
 * Public test 14 (public14.c)
 *
 * Verifies that a Linked_hash_map use sthe move-to-front heuristic upon
 * lookup.  Creates a Linked_hash_map with several elements using character
 * keys and integer values, and looks some of them up afterward.  Then
 * checks the positions or indices of all the elements that were added, to
 * ensure that elements are stored in a Linked_hash_map in the order they
 * were added, modified by being moved to the front when they are looked up.
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
  Data data;
  int i, correct= 1;
  char chars[NUM_ITEMS]= {'q', 'w', 'e', 'r', 't', 'y', 'u'};
  int offsets[NUM_ITEMS]= {0, 1, 2, 3, 4, 5, 6};
  char ordered_chars[NUM_ITEMS]= {'u', 't', 'e', 'q', 'w', 'r', 'y'};

  hash_map= create(char_compare, NULL, int_compare, NULL);

  for (i= 0; i < NUM_ITEMS; i++)
    /* not bothering to check return value */
    put(&hash_map, (Key) (long) chars[i], (Data) (long) offsets[i]);

  /* look up some, but not all, of the items added */
  for (i= 0; i < NUM_ITEMS; i += 2)
    /* not using value looked up */
    get(&hash_map, (Key) (long) chars[i], &data);

  /* now look up elements in the order they should be stored in */
  for (i= 0; i < NUM_ITEMS && correct; i++)
    if (index_of(hash_map, (Key) (long) ordered_chars[i]) != i)
      correct= 0;

  clear(&hash_map);

  if (correct)
    printf("Elements in Linked_hash_map are in correct order!\n");
  else printf("Order of elements in Linked_hash_map is incorrect. :(\n");

  return 0;
}
