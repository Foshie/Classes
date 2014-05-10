/*
 * CMSC 212, Spring 2010, Project #5
 * Secret test 11 (secret11.c)
 *
 * Creates an Array_hash_map with several elements, clears it, and adds more
 * elements.  Looks up the elements that were added.  Dynamically-allocated
 * keys and values are used.  Keys are structures representing fractions
 * (storing a numerator and denominator), and the corresponding values are
 * doubles; a fraction key maps to its value as a real number.  Different
 * keys can map to the same value (e.g., 1/2 and 3/6 both map to 0.5).  Note
 * that although a double is the same size as a pointer on the Grace
 * machines the doubles cannot be stored directly in a void pointer, and
 * must be dynamically allocated, since ONLY INTEGER TYPES can be cast to
 * pointers in C, which does not include real (floating-point) types.
 * Checks for memory leaks and validity of the heap.
 *
 * You must link this test with array-hash-map.o!
 */

#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>
#include <malloc.h>
#define ARRAY_HASH_MAP
#include "hash-map.h"

#define NUM_FRACTIONS 9

typedef struct {
  int numerator;
  int denominator;
} Fraction;

static void die(char msg[]);
static double value(Fraction f);
static int double_compare(const Key a, const Key b);
static int fraction_compare(const Data a, const Data b);
static Hash_map create_example_hash_map(Fraction fracts[], int start);

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

Hash_map create_example_hash_map(Fraction fracts[], int start) {
  Hash_map new_map;
  Fraction *fp;
  double *ratio;
  int i;

  /* note we're using the library function free() as the key and data delete
     function */
  new_map= create(fraction_compare, free, double_compare, free);

  for (i= start; i < NUM_FRACTIONS; i++) {
  
    ratio= malloc(sizeof(*ratio));
    if (ratio == NULL)
      die("Memory could not be allocated.");
    *ratio= value(fracts[i]);

    fp= malloc(sizeof(*fp));
    if (fp == NULL)
      die("Memory could not be allocated.");
    *fp= fracts[i];

    /* not bothering to check return value */
    put(&new_map, (Key) fp, (Data) ratio);

  }

  return new_map;
}

int main() {
  Hash_map hash_map;
  Fraction fractions[NUM_FRACTIONS]= {{3, 5}, {7, 9}, {1, 2}, {1, 10}, {3, 6},
                                      {2, 10}, {5, 8}, {2, 3}, {5, 9}};
  Data data;
  Fraction *fp;
  int i, correct= 1;

  mcheck_pedantic(NULL);

  hash_map= create_example_hash_map(fractions, 0);

  clear(&hash_map);

  hash_map= create_example_hash_map(fractions, 2);

  for (i= 2; i < NUM_FRACTIONS - 2 && correct; i++) {

    fp= malloc(sizeof(*fp));
    if (fp == NULL)
      die("Memory could not be allocated.");
    *fp= fractions[i];

    if (!get(&hash_map, fp, &data))
      correct= 0;
    else  /* comparing real numbers is inexact, so just see if they're close */
      if (* (double *) data - value(*fp) > 0.0000000001)
        correct= 0;

    free(fp);

  }

  if (correct)
    printf("Hash_map seems to be correct!\n");
  else printf("Hash_map appears to be incorrect.\n");

  clear(&hash_map);

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes detected. :(\n", mallinfo().uordblks);
  else printf("No memory leak detected. :)\n");

  return 0;
}
