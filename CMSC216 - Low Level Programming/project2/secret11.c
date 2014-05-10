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

  /* NULL handling */
  test_assert(bucket_count(&t) == NUM_BUCKETS, "bucket_count", 0);
  test_assert(bucket_count(NULL) == -1, "bucket_count", 1);

  return 0;
}
