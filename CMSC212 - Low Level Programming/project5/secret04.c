/*
 * CMSC 212, Spring 2010, Project #5
 * Secret test 04 (secret04.c)
 *
 * Creates a Linked_hash_map with several elements, resizes it (first
 * increasing and then decreasing), checks its size and capacity, and looks
 * up several elements that were and were not added.  Integer keys and
 * character values are used.  Keys are numbers of days in April 2010, and
 * values are characters representing the day of the week they fall on (U =
 * Sunday, M = Monday, T = Tuesday, W = Wednesday, H = Thursday, F = Friday,
 * S = Saturday).
 *
 * You must link this test with linked-hash-map.o!
 */

#include <stdio.h>
#include <limits.h>
#define LINKED_HASH_MAP
#include "hash-map.h"

#define NUM_ITEMS 22

static int int_compare(const Key a, const Key b);
static int char_compare(const Key a, const Key b);
static Hash_map create_example_hash_map(int keys[], char values[]);

int int_compare(const Key a, const Key b) {
  return ((int) (long) a - (int) (long) b);
}

int char_compare(const Data a, const Data b) {
  return ((char) (long) a - (char) (long) b);
}

Hash_map create_example_hash_map(int keys[], char values[]) {
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
  int i, correct= 1;
  int days[NUM_ITEMS]= {23, 19, 27, 5, 10, 28, 25, 22, 26, 6, 8, 24, 4, 11,
                        18, 12, 13, 20, 7, 14, 21, 29};
  char letters[NUM_ITEMS]= {'F', 'M', 'T', 'M', 'S', 'W', 'U', 'H', 'M', 'T',
                            'H', 'S', 'U', 'U', 'U', 'M', 'T', 'T', 'W', 'W',
                            'W', 'H'};

  hash_map= create_example_hash_map(days, letters);

  if (size(hash_map) == 22 && current_capacity(hash_map) == INT_MAX) {

    for (i= 4; i < NUM_ITEMS; i++)
      /* not bothering to check return value */
      remove_key(&hash_map, (Key) (long) days[i]);

    /* now look up elements in the order they should be stored in */
    for (i= 0; i < 3 && correct; i++)
      if (index_of(hash_map, (Key) (long) days[i]) != i)
        correct= 0;

    /* check that some of the keys are present */
    if (size(hash_map) == 4 && current_capacity(hash_map) == INT_MAX &&
        correct)
      printf("Hash_map data and resizing seem to be correct!\n");
    else printf("Hash_map data or resizing appears to be incorrect.\n");

  } else printf("Your hash_map capacity or size is not increasing. :(\n");

  clear(&hash_map);

  return 0;
}
