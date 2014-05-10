/*
 * CMSC 212, Spring 2010, Project #5
 * Secret test 01 (secret01.c)
 *
 * Creates an Array_hash_map with several elements, resizes it checks its
 * size and capacity, and looks up several elements that were and were not
 * added.  Integer keys and character values are used.  Keys are numbers of
 * days in April 2010, and values are characters representing the day of the
 * week they fall on (U = Sunday, M = Monday, T = Tuesday, W = Wednesday, H
 * = Thursday, F = Friday, S = Saturday).
 *
 * You must link this test with array-hash-map.o!
 */

#include <stdio.h>
#define ARRAY_HASH_MAP
#include "hash-map.h"

#define NUM_ITEMS 11

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
  Data data;
  int days[NUM_ITEMS]= {23, 19, 27, 5, 10, 28, 25, 22, 26, 6, 8};
  char letters[NUM_ITEMS]= {'F', 'M', 'T', 'M', 'S', 'W', 'U', 'H', 'M', 'T',
                            'H'};
  int i, size_ans, capacity_ans, correct= 1;
  int sorted[NUM_ITEMS]= {5, 6, 8, 10, 19, 22, 23, 25, 26, 27, 28};

  hash_map= create_example_hash_map(days, letters);

  size_ans= size(hash_map);
  capacity_ans= current_capacity(hash_map);

   /* now look up elements in the order they should be stored in */
  for (i= 0; i < NUM_ITEMS && correct; i++)
    if (index_of(hash_map, (Key) (long) sorted[i]) != i)
      correct= 0;

  /* check that some of the keys are present */
  if (size_ans == 11 && capacity_ans == 20 && correct == 1 &&
      get(&hash_map, (Key) (long) days[1], &data) &&
      get(&hash_map, (Key) (long) days[4], &data) &&
      get(&hash_map, (Key) (long) days[8], &data) &&
      get(&hash_map, (Key) (long) days[9], &data))
    printf("Hash_map data and resizing seem to be correct!\n");
  else printf("Hash_map data or resizing appears to be incorrect.\n");

  clear(&hash_map);

  return 0;
}
