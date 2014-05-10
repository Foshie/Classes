#include "hashtable.h"
#include <sysexits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MEM_ERR fprintf(stderr, "Memory allocation failed.\n"); exit(EX_OSERR);

/*
  Josh Fann
  jfann 109901918
  Project 3

  hashtable.c implements a closed addressing, chaining approach using the hash
  code defined in Project 2.  The hash table is now made of key count, bucket
  count, and an array of pointers pointing to the head node of a linked list.
  
  The chaining approach utilizes a linked list in each bucket index.  When the
  average number of keys per list becomes > 5, the whole table resizes to 
  decrease the amount of nodes per linked list (Increases efficiency).

*/
void resize(Table *t);
Table *create(int size);
int compare(const void *a, const void *b);

/*
  Allocate and return a properly initialized hash table 
  (with a bucket count of INIT_BUCKETS as specified in hashtable.h).
*/
Table *create_table(){
  return create(INIT_BUCKETS);
}

/*
  Reset the table to an empty state. Do nothing if t is NULL.  Does nothing if
  key_ct = 0 as well.

*/
void reset_table(Table *t){
  Data_pair_node *ahead, *curr;
  int i = 0;
  if(t != NULL && key_count(t) > 0){
    while(i < bucket_count(t)){
      curr = t->buckets[i];
      /* If nothing exists at the bucket, curr moves to next index
	 Otherwise: 1. Set a temp node to curr's next. 
	            2. Free current node's key and value.
		    3. Free current node.
		    4. Set the curr to the future temp.
		    5. Decrement key_ct.(Should be 0 at end of fn.)
      */
      while(curr != NULL){
	ahead = curr->next;
	free(curr->key);
	free(curr->value);
	free(curr);
	curr = ahead;
	t->key_ct--;
      }
      i++;
    }
  }
}

/*
  Attempts to insert a key/value pair into the table. Insertion fails if key, 
  val or t is NULL. If the key is already in the table, its corresponding 
  value in the table should be overritten by the value parameter given.

  Return 0 if the insert is successful, -1 otherwise.
*/
int insert(Table *t, const char *key, const char *value){
  Data_pair_node *curr = NULL, *prev = NULL, *new_pair = NULL;
  int index = hash_code(key) % (bucket_count(t));
  if(key != NULL && value != NULL && t != NULL){

    new_pair = malloc(sizeof(Data_pair_node));
    new_pair->key = malloc(((int)strlen(key) + 1) * sizeof(char)); 
    new_pair->value = malloc(((int)strlen(value) + 1) * sizeof(char));   
    if(new_pair == NULL || new_pair->key == NULL || new_pair->value == NULL){
      MEM_ERR;
    }
   
    strcpy(new_pair->key, key);
    strcpy(new_pair->value, value);
    new_pair->next = NULL;

    curr = t->buckets[index];
    /*Iterates curr through the linked list to find an existing key or 
      the end of the linked list.*/
    while(curr != NULL){
      /*If node with key already exists, overwrites node's value. And exits.*/
      if(strcmp(key, curr->key) == 0){
	free(curr->value);
	curr->value = new_pair->value;
	free(new_pair->key);
	free(new_pair);
	return 0;
      }else{
	/*Keeps track of previous node. For inserting at end of list.*/
	prev = curr;
	curr = curr->next;
      }
    }
    /*If prev == NULL, then hash_bucket has no linked list.  Point index 
      of buckets to newly created node(making the head node)*/
    if(prev == NULL){
      t->buckets[index] = new_pair;
    }else{
      /*Insert new_pair at end of list.*/
      prev->next = new_pair;
    }
    t->key_ct++;

    /*Checks if table needs to be resized after insert.*/
    if(((double)key_count(t) / (double) bucket_count(t)) > 5)
      resize(t);

    return 0;
  }
  return -1;
}

/*
  Search for a key in the table. If the key is present and val is not NULL, 
  the value that is paired with the key in the table should be copied, 
  and *val should be set to point to that copy. If either t or key is NULL,
  the search is defined to fail. 

  Return 0 if the key is found in the table, -1 otherwise.(If there are no keys
  in the table, will instantly return -1.)

  Loops through the linked list of the hashed key.  If it does exist, writes
  the node's value to the paramter passed in val.  If not, does nothing
  and returns -1.
*/
int search(Table *t, const char *key, char **val){
  Data_pair_node *curr;
  if(key != NULL && t != NULL && val != NULL && key_count(t)){
    /*sets curr to head of bucket*/
    curr = t->buckets[hash_code(key) % bucket_count(t)];
    while(curr != NULL){
      if(strcmp(key, curr->key) == 0){
	*val = calloc(strlen(curr->value) + 1, sizeof(char));
	if(*val == NULL){
	  MEM_ERR;
	}
	strcpy(*val, curr->value);
	return 0;
      }
      curr = curr->next;
    }
  }
  return -1;
}

/*
  Attempt to remove the key from the table. If either t or key is NULL, or if
  the key does not exist in the table, the attempt fails.

  Return 0 if the deletion succeeds, -1 otherwise. (If there are no keys in
  the table, returns -1.)

  Searches if the key exists in the hashed bucket.  If so, removes the head 
  while resetting its previous node to the next node.  
Frees the key and value first.  Then frees the node.
*/
int delete(Table *t, const char *key){
  Data_pair_node *curr, *prev = NULL;

  if(t!= NULL && key != NULL && key_count(t)){
    /*Sets curr to head of indexed bucket*/
    curr = t->buckets[hash_code(key) % bucket_count(t)];
    while(curr!= NULL){
      /*Finds node to delete*/
      if(strcmp(curr->key, key) == 0){
	/*If head node is deleted, sets new head node to curr->next.*/
	if(prev == NULL){
	  t->buckets[hash_code(key) % t->bucket_ct] = curr->next;
	}else/*Otherwise just set the prev's next to the curr's next node.*/
	  prev->next = curr->next;

	free(curr->key);
	free(curr->value);
	free(curr);
	t->key_ct--;
	return 0;
      }
      prev = curr;
      curr = curr->next;
    }
  }
  return -1;
}

/*
  Return the number of keys present in the table, or -1 if t is NULL.
*/
int key_count(Table *t){
  if(t != NULL)
    return t->key_ct;
  return -1;
}

/*
  Return the number of buckets the table currently has; return -1 if t is NULL.
*/
int bucket_count(Table *t){
  if(t != NULL)
    return t->bucket_ct;
  return -1;
}

/*
  Return the hash code of the string, as defined by the algorithm in 
  Section 2.2.2. If str is NULL, return 0.
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

/*
  Return an array of all keys present in the table. The keys should be in 
  ascending sorted order. The array, and all its contents, should be 
  dynamically allocated, with the elements of the array being copies of the
  keys in the table. The caller is responsible for later freeing the memory 
  in the array. 

  If t is NULL, the function should return NULL. Also returns NULL if there are
  no stored in the Table.

  1. Store an array of strings of all keys in the Table in order of buckets.
  2. Use quicksort to sort all keys in lexicographical order.
*/
char **get_keys(Table *t){
  Data_pair_node *curr;
  int bucket_index = 0, j=0;
  char **to_return;

  if(t!= NULL && key_count(t)){

    to_return = calloc(key_count(t), sizeof(char*));
    if(to_return == NULL){
      MEM_ERR;
    }

    /*Iterates through the buckets array*/
    while(bucket_index < bucket_count(t)){
      curr = t->buckets[bucket_index];

      /*Iterates through the linked list of the indexed buckets.*/
      while(curr != NULL){

	to_return[j] = malloc(sizeof(curr->key+1));
	if(to_return[j] == NULL){
	  MEM_ERR;
	}

	/*Copies the key to the array to_return*/
	strcpy(to_return[j], curr->key);
	curr = curr->next;
	j++;
      }
      bucket_index++;
    }
    /*Uses compare to sort the array of strings lexicographically.*/
    qsort(to_return, key_count(t), sizeof(char *), compare);
    return to_return;
  }
  return NULL;
}

/*
  Return an array of all values present in the table. The values should be 
  sorted by the keys associated with them (so if the pairs "apple")"zebra" and 
  "banana")"koala" are in the table, the value array would be 
  ["zebra", "koala"], because "apple" is lexicographically less than 
  "banana"). Once again, the array and all contents should be dynamically 
  allocated, and the caller must take care of freeing the array. 

  If t is NULL, this function will also return NULL.  Returns NULL also when 
  there are no keys in the table.

  1. Calls get_keys to get a sorted list of keys.
  2. While iterating through the array of keys, searches the value corresponding
  to that key and copies it to the return array at the key's index.

  No other sorting needed.
*/
char **get_values(Table *t){
  int i = 0;
  char **value, **keys;
  char *get_val = NULL;

  if(t != NULL && key_count(t)){
    /*Calls get_keys to store a sorted array of the keys.*/
    keys = get_keys(t);

    value = calloc(key_count(t), sizeof(char*));
    if(value == NULL){
      MEM_ERR;
    }

    /*Loops through the key array.*/
    while(i < key_count(t)){
      /*Sets get_val to the value corresponding to key in t*/
      search(t, keys[i], &get_val);

      value[i] = malloc(sizeof(get_val+1));
      if(value[i] == NULL){
	MEM_ERR;
      }
      strcpy(value[i], get_val);
      /* Must free get_val and keys[i] as you increment so you can rewrite 
	 get_val, and you can free keys later without losing memory.*/
      free(get_val);
      free(keys[i]);
      i++;
    }
    /* keys is a temporary variable used only for this function. 
    Should no exist afterwards.*/
    free(keys);
    return value;
  }
  return NULL;
}

/*
  Frees all memory associated with the given table, including keys and values. 
  If t is NULL, the function should do nothing.

  First resets the table(all nodes are freed with freed data).
  Frees buckets, then the table.
*/
void destroy_table(Table *t){
  if(t!= NULL){
    reset_table(t);
    free(t->buckets);
    free(t);
  }
}

/*
  create returns a properly allocated and initalized Table of size.

  (Can be called by create_table, resize)
*/

Table *create(int size){
  Table *to_return = malloc(sizeof(Table));
  if(to_return == NULL){
    MEM_ERR;
  }
  to_return->key_ct = 0;
  to_return->bucket_ct = size;
  to_return->buckets = calloc(size, sizeof(Hash_bucket));
  if(to_return->buckets == NULL){
    MEM_ERR;
  }
  return to_return;
}

/*
  compare is a function used in qsort to compare strings in an array.
*/
 int compare(const void *a, const void *b){
   return strcmp(*(char **)a, *(char **)b);
 }

/* Doubles the bucket size of the hash table when the average list length 
   is more than 5 elements.

   Creates a new table of size- 2*bucket_ct.  Inserts the nodes from t into
   the bigger table.  Free all nodes of bucket and the bucket itself.  Set
   bigger table's bucket equal to old table's bucket. Free the big table.
   Increase bucket count.
*/
void resize(Table *t){
  Table *bigger;
  int index = 0;
  Data_pair_node *curr;

  if(t != NULL){
    bigger = create(bucket_count(t)*2);

    /*Inserts all nodes of t into the bigger table.*/
    while(index < bucket_count(t)){
      curr = t->buckets[index];
      while(curr != NULL){
	insert(bigger, curr->key, curr->value);
	curr = curr->next;
      }
      index++;
    }

    /*Free all nodes.  Then free bucket array.*/
    reset_table(t);
    free(t->buckets);

    /*Set bigger bucket to older bucket*/
    t->buckets = bigger->buckets;
    t->key_ct = key_count(bigger);
    t->bucket_ct = bucket_count(bigger);
    /*Free big table.  Old table is now big table.*/
    free(bigger);
  }
}
