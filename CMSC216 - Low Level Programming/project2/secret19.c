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
  result = system("./hashtester2 < secret19.in");

  /* Test the return value (stored in higher bits - system specific) */
  test_assert(result >> 8 == EX_DATAERR, "EX_DATAERR", 0);

  return 0;
}

