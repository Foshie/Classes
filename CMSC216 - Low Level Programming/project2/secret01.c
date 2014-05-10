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

  /* Insert and Search the table with linear probing*/
  test_assert(key_count(&t) == 0, "key_count", 0);
  test_assert(!insert(&t,"John","3412"), "insert", 1);
  test_assert(!insert(&t,"Anne","2234"), "insert", 2);
  test_assert(key_count(&t) == 2, "key_count", 3);
  test_assert(!search(&t, "John", str), "search", 4);
  test_assert(!strcmp(str, "3412"), "search", 5);
  test_assert(!search(&t, "Anne", str), "search", 6);
  test_assert(!strcmp(str, "2234"), "search", 7);


  return 0;
}
