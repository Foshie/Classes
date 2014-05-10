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

  /* Delete from empty table */
  test_assert(delete(&t, "June"), "delete", 0);
  test_assert(delete(&t, "May"), "delete", 1);
  test_assert(delete(&t, "August"), "delete", 2);

  return 0;
}
