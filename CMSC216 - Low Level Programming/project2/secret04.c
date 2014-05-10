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

  /* Insert into full table */
  test_assert(key_count(&t) == 0, "key_count", 0);
  test_assert(!insert(&t, "Jack", "2278"), "insert", 1);
  test_assert(!insert(&t, "Mike", "2056"), "insert", 2);
  test_assert(!insert(&t, "John", "8745"), "insert", 3);
  test_assert(!insert(&t, "Lucy", "4761"), "insert", 4);
  test_assert(!insert(&t, "Jill", "1058"), "insert", 5);
  test_assert(key_count(&t) == 5, "key_count", 6);
  test_assert(insert(&t, "Greg", "7564"), "insert", 7);
 
 


  return 0;
}
