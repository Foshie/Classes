/*
 * CMSC 212, Spring 2010, Project #5
 * Public test 06 (public06.c)
 *
 * Creates a Linked_hash_map with several elements, checks its size and
 * capacity, and removes several elements that were added.  Integer keys and
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

#define NUM_ITEMS 8

static int int_compare(const Key a, const Key b);
static int char_compare(const Key a, const Key b);

int int_compare(const Key a, const Key b) {
  return ((int) (long) a - (int) (long) b);
}

int char_compare(const Data a, const Data b) {
  return ((char) (long) a - (char) (long) b);
}

int main() {
  Hash_map hash_map;
  Data data;
  int i, size_ans, capacity_ans;
  int days[NUM_ITEMS]= {23, 19, 27, 5, 10, 28, 25, 22};
  char letters[NUM_ITEMS]= {'F', 'M', 'T', 'M', 'S', 'W', 'U', 'H'};

  hash_map= create(int_compare, NULL, char_compare, NULL);

  for (i= 0; i < NUM_ITEMS; i++)
    /* not bothering to check return value */
    put(&hash_map, (Key) (long) days[i], (Data) (long) letters[i]);

  for (i= 0; i < NUM_ITEMS; i += 3)
    /* not bothering to check return value */
    remove_key(&hash_map, (Key) (long) days[i]);

  size_ans= size(hash_map);
  capacity_ans= current_capacity(hash_map);

  /* check that some of the keys are present */
  if (size_ans == 5 && capacity_ans == INT_MAX &&
      !get(&hash_map, (Key) (long) days[0], &data) &&
      get(&hash_map, (Key) (long) days[1], &data) &&
      get(&hash_map, (Key) (long) days[2], &data) &&
      !get(&hash_map, (Key) (long) days[3], &data) &&
      get(&hash_map, (Key) (long) days[4], &data) &&
      !get(&hash_map, (Key) (long) days[6], &data) &&
      !get(&hash_map, (Key) (long) 31, &data) &&
      !get(&hash_map, (Key) (long) 11, &data))
    printf("Hash_map size, capacity, and data are correct!\n");
  else printf("Hash_map size, capacity, or data are incorrect. :(\n");

  clear(&hash_map);

  return 0;
}
