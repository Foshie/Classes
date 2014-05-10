#include "hashtable.h"
#include <string.h>
#include <stdio.h>

/* Josh Fann
   jfann 109901918
   Project 2
  
   hashtable.c uses an open addressing, linear probing approach to resolving
   hash collisions.  Both the keys and the values to be inserted into the 
   hash tables are strings.
*/

/*
  Initialize the table to be empty. You can assume that the table 
  has capacity NUM_BUCKETS, as defined in hashtable.h. Do nothing if t is NULL.
*/

void init_table(Table *t){
  int i = 0;
  if(t != NULL){
    t->key_ct = 0;
    while(i < NUM_BUCKETS){
      t->buckets[i].state = EMPTY;
      *t->buckets[i].data.key = '\0';
      *t->buckets[i].data.value = '\0';
      i++;
    }
  }
}

/*
  Reset the table to an empty state, meaning that all buckets are in the empty state. 
  Do nothing if t is NULL.

  Project description states they do exactly the same thing.  If we had to worry about
  memory allocation, this would be different from init_table.
*/
void reset_table(Table *t){
  init_table(t);
}

/*
  Insert a key/value pair into the table. Insertion fails if: 
  a. either key or val is NULL; 
  b. either the key or value string is longer than the MAX_STR_SIZE 
     defined in hashtable.h;
  c. t is NULL; or 
  d. the table is full. 
  If the key is already in the table, its corresponding value in the table should 
  be overwritten with the new value.
  Note that in this case, even if the table is full the insert succeeds. 
qui  Return 0 if insertion is successful, -1 otherwise.
*/
int insert(Table *t, const char *key, const char *val){
  int hash = 0, count = 0, i = 0;
  if(key != NULL && val != NULL && strlen(key) <= MAX_STR_SIZE 
     && strlen(val) <= MAX_STR_SIZE && t != NULL){
    hash = hash_code(key) % NUM_BUCKETS;

    /*Check if key exists in buckets*/
    while(i < NUM_BUCKETS){
      if(t->buckets[i].state == FULL && 
	 (strcmp(key, t->buckets[i].data.key) == 0)){
	  strcpy(t->buckets[i].data.value, val);
	  return 0;
      }
      i++;
    }

    while(count < NUM_BUCKETS){
      /* Places key at next not FULL bucket at or after hash*/
      if(t->buckets[(hash + count) % NUM_BUCKETS].state != FULL){
	strcpy(t->buckets[(hash + count) % NUM_BUCKETS].data.key, key);
	strcpy(t->buckets[(hash + count) % NUM_BUCKETS].data.value, val);
	t->key_ct++;      
	t->buckets[(hash + count) % NUM_BUCKETS].state = FULL;
	return 0;
      }
      count++;
    }
  }  
  return -1;

}
/*
  Search for a key in the table. If the key is present and val is not NULL, 
  the value that is paired with the key in the table should be copied into the 
  buffer val points to (you may assume the buffer is large enough to 
  hold the value). 
  If either t or key is NULL, the search is defined as failing.

  Returns 0 if the key is in the table, -1 if the search fails.
*/
int search(Table *t, const char *key, char *val){
  int i = 0, hash = 0;
  if(t != NULL && key != NULL){
    hash = hash_code(key) %5;
    while(i < NUM_BUCKETS){
      /* Returns 0 if current bucket state is FULL and keys match.*/
      if(t->buckets[(hash + i) % NUM_BUCKETS].state == FULL &&
	 strcmp(key, t->buckets[(hash + i) % NUM_BUCKETS].data.key) == 0){
	if(val!=NULL)
	  strcpy(val, t->buckets[(hash + i) % NUM_BUCKETS].data.value);
	return 0;
      }
      i++;
    }
  }
  return -1;
}
/*
  Attempt to remove the key from the table. If either t or key is NULL, 
  or if the key does not exist in the table, the attempt fails.
  Return 0 if the deletion succeeds, -1 otherwise.
*/
int delete(Table *t, const char *key){
  int i = 0, hash = 0;
    if(t != NULL && key != NULL){
      hash = hash_code(key) % NUM_BUCKETS;
      while(i < NUM_BUCKETS){
	if( t->buckets[(i + hash) % NUM_BUCKETS].state == FULL &&
	    strcmp(key, t->buckets[(i + hash) % NUM_BUCKETS].data.key) == 0){
	  t->buckets[(i + hash) % NUM_BUCKETS].state = DIRTY;
	  (t->key_ct)--;
	  return 0;
	}
	i++;
      }
    }
  return -1;
  
}
/*
  Return the number of keys present in the table, or -1 if t is NULL.
*/
int key_count(Table *t){
  if(t != NULL){
    return t->key_ct;
  }
  return -1;

}
/*
  Return the number of buckets the table has; return -1 if t is NULL.
*/
int bucket_count(Table *t){
  if(t != NULL){
    return NUM_BUCKETS;
  }
  return -1;
}
/*
  Return the hash code of the string, as defined by the algorithm in
  Section 2.2.2. 
  If str is NULL, return 0. 
*/
unsigned long hash_code(const char *str){
  int i = 0;
  unsigned long to_return=0;
  if(str != NULL){
    while(i <(int) strlen(str) -1){
      to_return += (long)str[i];
      to_return *= 65599;
      i++;
    }
    return to_return + str[i];
  }
  return 0;
}
