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
  /* Test the hashing function */
  test_assert(hash_code(NULL) == 0, "hash_code", 0);
  test_assert(hash_code("") == 0, "hash_code", 1);
  test_assert(hash_code("0") == 48L, "hash_code", 2);
  test_assert(hash_code("a") == 97L, "hash_code", 3);
  test_assert(hash_code("abcd") == 27382309816246402L, "hash_code", 4);
  test_assert(hash_code("wasHiNGtON__DC") == 8256878809472844751L, "hash_code", 5);
  test_assert(hash_code("university of maryland, college park") == 11155914042891554084UL, "hash_code", 6);
  test_assert(hash_code("university of maryland, college park:go terps:run rabbit run") == 3682992939691343922L, "hash_code", 7);

  return 0;
}

