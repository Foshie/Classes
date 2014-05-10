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
  char b[MAX_STR_SIZE + 1];

  /* Initialize the table */
  init_table(&t);

  /* Insert into the table */
  insert(&t, "202", "DC");
  insert(&t, "301", "W_MD");

  /* Search within the table */
  test_assert(!search(&t, "301", NULL), "search", 0);
  test_assert(!search(&t, "202", b), "search", 1);
  test_assert(!strcmp(b, "DC"), "search", 2);

  return 0;
}
