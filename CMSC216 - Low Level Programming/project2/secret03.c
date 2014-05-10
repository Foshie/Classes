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

  /* Empty Strings insertion and hash code */
  test_assert(hash_code("") == 0, "hash_code",0);
  test_assert(key_count(&t) == 0, "key_count", 1);
  test_assert(!insert(&t, "", "2278"), "insert", 2);
  test_assert(key_count(&t) == 1, "key_count", 3);
 


  return 0;
}
