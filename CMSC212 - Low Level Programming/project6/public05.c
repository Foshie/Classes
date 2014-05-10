/*
 * CMSC 212, Spring 2010, Project #6
 * Public test 05 (public05.c)
 *
 * Creates a Hash_map with several elements, checks put() by calling it with
 * existing keys and checks if it replaces the values associated with them
 * rather than creating new key/value pairs.  Keys and values are
 * dynamically allocated.
 *
 * Do NOT link this test with either array-hash-map.o or linked-hash-map.o,
 * however, you must set the symbolic link libhash-map.so to point to
 * libarray-hash-map.so before running this test!
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mcheck.h>
#include "hash-map.h"
#include "iterator.h"

#define NUM 13

typedef struct {
  int numerator;
  int denominator;
} Fraction;

static void die(char msg[]);
static double value(Fraction f);
static int double_compare(const Key a, const Key b);
static int fraction_compare(const Data a, const Data b);
static Hash_map create_example_hash_map(void);

void die(char msg[]) {
  printf("%s\n", msg);
  exit(-1);
}

double value(Fraction f) {
  return ((double) f.numerator) / f.denominator;
}

/* two fractions are equal if their numerators and denominators are
   identical (not if their values as real numbers are equal) */
int fraction_compare(const Data a, const Data b) {
  Fraction frac1= *(Fraction *) a, frac2= *(Fraction *) b;

  if (frac1.numerator == frac2.numerator &&
      frac1.denominator == frac2.denominator)
    return 0;
  else
    if (value(frac1) < value(frac2))
      return -1;
    else
      if (value(frac1) > value(frac2))
        return 1;
      else return (frac1.numerator < frac2.numerator ? -1 : 1);
}

int double_compare(const Key a, const Key b) {
  if (a == b)
    return 0;
  else
    if (a < b)
      return -1;
    else return 1;
}

Hash_map create_example_hash_map(void) {
  Hash_map new_map;
  int i;
  Fraction fractions[NUM]= {{4, 5}, {5, 3}, {7, 4}, {3, 5}, {8, 9},
                            {1, 2}, {1, 10}, {3, 6}, {2, 10}, {5, 8},
                            {2, 3}, {5, 9}};
  Fraction *fp;
  double *ratio;

  new_map= create(fraction_compare, free, double_compare, free);

  for (i= 0; i < NUM; i++) {
    ratio= malloc(sizeof(*ratio));
    if (ratio == NULL)
      die("Memory could not be allocated.");
    *ratio= value(fractions[i]);

    fp= malloc(sizeof(*fp));
    if (fp == NULL)
      die("Memory could not be allocated.");
    *fp= fractions[i];

    /* not bothering to check return value */
    put(&new_map, (Key) fp, (Data) ratio);
  }

  return new_map;
}

int main() {
  Hash_map hash_map;
  Data data;
  Fraction sorted_fractions[NUM]= {{1, 10}, {2, 10}, {1, 2}, {3, 6}, {5, 9},
                            {3, 5}, {5, 8}, {2, 3}, {5, 3}, {7, 4},
                            {4, 5}, {8, 9}};
  int i, correct= 1;
  Fraction *fp;

  mcheck_pedantic(NULL);

  hash_map= create_example_hash_map();

  for (i= 0; i < NUM; i += 3) {

    fp= malloc(sizeof(*fp));
    if (fp == NULL)
      die("Memory could not be allocated.");
    *fp= sorted_fractions[i];

    put(&hash_map, (Key) fp, (Data) (long) 0);  /* existing key, new value */

  }

  for (i= 0; i < NUM && correct; i += 3) {
    get(&hash_map, (Key) &sorted_fractions[i], &data);
    if ((int) (long) data != 0)
      correct= 0;
  }

  if (size(hash_map) == 13 && correct == 1)
    printf("A new key/value pair was not created! :)\n");
  else printf("A new key/value pair was created. :(\n");

  clear(&hash_map);

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes. :(\n", mallinfo().uordblks);
  else printf("No memory leak detected. :)\n");

  return 0;
}
