#include "hashtable.h"
#include <stdio.h>
#include <string.h>

void test_assert(int test, const char* name, int index)
{
   if (test) 
     printf("pass %s %d\n", name, index);
   else printf("fail %s %d\n", name, index);
}

int main(int argc, char* argv[])
{
  Table t;
  char str[10];

  /* Initialize the table */
  init_table(&t);

  /* Search for non-existent entries */
  test_assert(key_count(&t) == 0, "key_count", 0);
  test_assert(!insert(&t, "Jack", "2278"), "insert", 1);
  test_assert(!insert(&t, "Mike", "2056"), "insert", 2);
  test_assert(key_count(&t) == 2, "key_count", 3);
  test_assert(search(&t, "Fred", str), "delete", 4);
  test_assert(key_count(&t) == 2, "key_count", 5);
 
  return 0;
}
