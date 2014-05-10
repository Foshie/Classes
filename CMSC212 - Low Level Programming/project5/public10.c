/*
 * CMSC 212, Spring 2010, Project #5
 * Public test 10 (public10.c)
 *
 * Creates a Linked_hash_map with several elements, checks its size and
 * capacity, and looks up several elements that were and were not added.
 * Dynamically-allocated keys and values are used.  Keys are structures
 * representing fractions (storing a numerator and denominator), and the
 * corresponding values are doubles; a fraction key maps to its value as a
 * real number.  Different keys can map to the same value (e.g., 1/2 and 3/6
 * both map to 0.5).  Note that although a double is the same size as a
 * pointer on the Grace machines the doubles cannot be stored directly in a
 * void pointer, and must be dynamically allocated, since ONLY INTEGER TYPES
 * can be cast to pointers in C, which does not include real
 * (floating-point) types.
 *
 * You must link this test with array-hash-map.o!
 */

#include <stdio.h>
#include <stdlib.h>
#define LINKED_HASH_MAP
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

int main() {
  Hash_map hash_map;
  Data data;
  Fraction fractions[NUM_FRACTIONS]= {{3, 5}, {7, 9}, {1, 2}, {1, 10}, {3, 6},
                                      {2, 10}, {5, 8}, {2, 3}, {5, 9}};
  Fraction *fp, frac;
  double *ratio;
  int i, correct= 1;

  /* note we're using the library function free() as the key and data delete
     function */
  hash_map= create(fraction_compare, free, double_compare, free);

  for (i= 0; i < NUM_FRACTIONS; i++) {

    ratio= malloc(sizeof(*ratio));
    if (ratio == NULL)
      die("Memory could not be allocated.");
    *ratio= value(fractions[i]);

    fp= malloc(sizeof(*fp));
    if (fp == NULL)
      die("Memory could not be allocated.");
    *fp= fractions[i];

    /* not bothering to check return value */
    put(&hash_map, (Key) fp, (Data) ratio);

  }

  for (i= 0; i < NUM_FRACTIONS && correct; i++) {
    frac= fractions[i];
    /* check that the fractions with even indices in the array are present */
    if (i % 2 == 0 && !get(&hash_map, (Key) &frac, &data))
      correct= 0;
    else {
      /* for the fractions with odd indices, check that different (modified)
         fraction values are not present */
      frac.numerator++;
      frac.denominator -= 2;
      if (get(&hash_map, (Key) &frac, &data))
        correct= 0;
    }
  }

  clear(&hash_map);

  if (correct)
    printf("Hash_map seems to be correct!\n");
  else printf("Hash_map appears to be incorrect. :(\n");

  return 0;
}
