/*
 * CMSC 212, Spring 2010, Project #5
 * Secret test 07 (secret07.c)
 *
 * Creates an Array_hash_map with several elements, and calls get() to look
 * up all the values that were added, in increasing order by key.
 * Dynamically allocated keys and values are used.  Keys are structures that
 * indicate the scientific names of animals and the corresponding values are
 * their common names.  Scans the input (key and data) from another file.
 * The compare functions and deleteion function are given.  Checks for
 * memory leaks and validity of the heap.
 *
 * You must link this test with array-hash-map.o!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <mcheck.h>
#define ARRAY_HASH_MAP
#include "hash-map.h"

#define NAME_MAX 80

typedef struct {
  char *genus;
  char *species;
} Animal;

static void die(char msg[]);
static int animal_compare(const Key a, const Key b);
static int string_compare(const Data a, const Data b);
static void animal_delete(Data value);
Hash_map create_example_hash_map(void);

void die(char msg[]) {
  printf("%s\n", msg);
  exit(-1);
}

int animal_compare(const Key a, const Key b) {
  Animal *name1= (Animal *) a, *name2= (Animal *) b;

  if (strcmp(name1->genus, name2->genus) == 0)
    return strcmp(name1->species, name2->species);
  else return strcmp(name1->genus, name2->genus);
}

int string_compare(const Data a, const Data b) {
  return strcmp((char *) a, (char *) b);
}

void animal_delete(Data value) {
  Animal *animal= (Animal *) value;
  free(animal->genus);
  free(animal->species);
  free(animal);
}

Animal *create_animal(char genus[], char species[]) {
  Animal *new_animal= malloc(sizeof(*new_animal));

  if (new_animal == NULL)
    die("Memory could not be allocated.");

  new_animal->genus= malloc(strlen(genus) + 1);
  if (new_animal->genus == NULL)
    die("Memory could not be allocated.");
  else strcpy(new_animal->genus, genus);

  new_animal->species= malloc(strlen(species) + 1);
  if (new_animal->species == NULL)
    die("Memory could not be allocated.");
  else strcpy(new_animal->species, species);

  return new_animal;
}

char *strdup(char str[]) {
  char *p= malloc(strlen(str) + 1);

  if (p == NULL)
    die("Memory could not be allocated.");
  else strcpy(p, str);

  return p;
}

Hash_map create_example_hash_map(void) {
  Hash_map new_map;
  Animal *ap;
  char genus[NAME_MAX], species[NAME_MAX], common_name[NAME_MAX], *temp;

  new_map= create(animal_compare, animal_delete, string_compare, free);

  while (!feof(stdin)) {

    scanf("%s %s ", genus, species);
    fgets(common_name, 80, stdin);
    common_name[strlen(common_name) - 1]= '\0';  /* get rid of newline */

    ap= create_animal(genus, species);

    temp= strdup(common_name);
    if (!put(&new_map, (Key) ap, (Data) temp)) { 
      printf("Can't insert %s\n", common_name);
      free(temp);
    }

    scanf(" ");  /* skip whitespace */

  }

  return new_map;
}

int main() {
  Hash_map hash_map;
  Key key;
  Data data;
  Animal *ap;
  char common_name[NAME_MAX];

  mcheck_pedantic(NULL);

  hash_map= create_example_hash_map();

  while (size(hash_map) > 0)
    if (!get_smallest(hash_map, &key, &data))
      printf("get_smallest() call failed.\n");
    else {
      ap= (Animal *) key;
      strcpy(common_name, (char *) data);
      printf("%s %s: %s\n", ap->genus, ap->species, common_name);
      remove_key(&hash_map, key);
    }

  clear(&hash_map);

  printf("\n");

  if (mallinfo().uordblks != 0)
    printf("Memory leak of %d bytes. :(\n", mallinfo().uordblks);
  else printf("No memory leak detected. :)\n");

  return 0;
}
