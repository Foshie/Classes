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

  /* Initialize the table */
  init_table(&t);

  /* Insert into the table checking for DIRTY */
  test_assert(key_count(&t) == 0, "key_count", 0);
  test_assert(!insert(&t, "Anne", "2278"), "insert", 1);
  test_assert(!insert(&t, "Alex", "2056"), "insert", 2);
  test_assert(!delete(&t, "Anne"), "delete", 3);
  test_assert(!insert(&t, "John", "2078"), "insert", 4);
  test_assert(key_count(&t) == 2, "key_count", 5);

  return 0;
}
