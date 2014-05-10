#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

void test_assert(int test, const char* name, int index)
{
   if (test) 
     printf("pass %s %d\n", name, index);
   else printf("fail %s %d\n", name, index);
}

int main(int argc, char* argv[])
{
  int result;

  /* Run hashtester with input on stdin */
  result = system("./hashtester secret18a.in");

  /* Test the return value (stored in higher bits - system specific) */
  test_assert(result >> 8 == EX_DATAERR, "EX_DATAERR", 0);

  /* Run hashtester with input on stdin */
  result = system("./hashtester secret18b.in extra_arg");

  /* Test the return value (stored in higher bits - system specific) */
  test_assert(result >> 8 == EX_USAGE, "EX_USAGE", 1);

  /* Run hashtester with input on stdin */
  result = system("./hashtester not_exist");

  /* Test the return value (stored in higher bits - system specific) */
  test_assert(result >> 8 == EX_OSERR, "EX_OSERR", 2);

  
  return 0;
}

