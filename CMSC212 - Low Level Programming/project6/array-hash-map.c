/*
  Josh Fann
  CMSC212 0202

  Array-hash-map simulates Java's HashMap class.  This simulation uses a simple
  method for allowing a program in C to subsitute one implementation of a set 
  of functions for another, without altering the program.  HashMap maps keys 
  to values.  The hash table is not implemented in this simulation.

  The Array-hash-map implementation uses one dynamically-allocated array that 
  stores a struct Map which contains Key keys and Data data.  The array 
  increases its capacity by 10 if no free space is left.  If hash map has 
  exactly fifteen unused elements when removing an element, the array's max
  capacity will be reduced by 10.  The array implementation stores elements
  in increasing sorted order determined by the compare_key function pointers.
*/

#define ALLOC "Memory allocation failed!\n"
#include "array-iterator.h"
#include "array-hash-map.h"
#include "hash-map.h"
#include <stdlib.h>
#include <stdio.h>

/*
  Returns a Hash_map with array size 0 and capacity size 10.  
  If compare_key or compare_data are NULL or calloc-ing goes wrong, 
  exits with -1. 
*/
Hash_map create(Key_compare_fn compare_key, Key_delete_fn delete_key,
                Data_compare_fn compare_data, Data_delete_fn delete_data){
  Hash_map to_return;
  Array_hash_map *imp;
  if(compare_key == NULL || compare_data == NULL){
    printf("NULL comparison function disallowed.\n");
    exit(-1);
  }
  imp = malloc(sizeof(Array_hash_map));
  if(imp == NULL){
    printf(ALLOC);
    exit(-1);
  }
  to_return.key_compare_fn = compare_key;
  to_return.key_delete_fn = delete_key;
  to_return.data_compare_fn = compare_data;
  to_return.data_delete_fn = delete_data;
  imp->info = calloc(10, sizeof(Map));
  if(imp->info == NULL){
    printf(ALLOC);
    exit(-1);
  }
  imp->size = 0;
  imp->capacity = 10;
  to_return.implementation = imp;
  return to_return;
}

/*
  Inserts a key and value at correct index of the array.  Array is sorted
  when inserting the info.  If a key already exists, the new value overwrites
  the old value. Then returns 1 without increasing the size.

  Function searches for first occurence where the key is less than the array's
  stored key.   After the index of where the key should be is found, checks 
  if the new size will be equal to the capacity.  If it is, increase the 
  capacity by 10, then realloc's the array with new size: capacity 
  *sizeof(Map).  Then loops through to shift the array to the right to make
  space for the key.  Overwrites the current index's key and data values.  
  Increments the size by 1.

  Returns 0 when map is NULL.  Returns 1 otherwise.
*/
int put(Hash_map *map, Key key, Data value){
  int i=0, j, exists=0;
  Array_hash_map *amap;
  if(map == NULL)
    return 0;
  amap = map->implementation;
  if(amap->size != 0){
    for(i = 0; i < amap->size && 
	  map->key_compare_fn(amap->info[i].key, key) <= 0; i++){
      if(map->key_compare_fn(amap->info[i].key, key) == 0){
	if(map->key_delete_fn != NULL)
	  map->key_delete_fn(key);    
	if(map->data_delete_fn != NULL)
	  map->data_delete_fn(amap->info[i].data); 
	amap->info[i].data = value;
	exists = 1;
	amap->size--;
      }
    }
    
    /* 
       Checks if map needs to increase the capacity.  If size = capacity, 
       add size of 10 Maps. Or if the new size will need a larger capacity.
    */
    if(amap->size == amap->capacity || amap->size+1 == amap->capacity){
      amap->capacity += 10;
      amap->info = realloc(amap->info, amap->capacity * sizeof(Map));
    }
    if(!exists)
      for(j = amap->size -1; j >= i; j--){
	amap->info[j+1].data = amap->info[j].data;
	amap->info[j+1].key = amap->info[j].key;
      }
  }
  if(!exists){
    amap->info[i].key = key;
    amap->info[i].data = value;
  }
  amap->size ++;

  return 1;
}

/*
  Returns current array's size
*/
int size(Hash_map map){
  Array_hash_map *amap = map.implementation;
  return amap->size;
}

/*
  Function loops through to find the key parameter in array.  If key is 
  found, value parameter is set to the key's corresponding data.  Returns
  0 if map or value is NULL or if key is not found in array.  Returns 1
  otherwise.
*/
int get(Hash_map *map, Key key, Data *value){
  int i;
  Array_hash_map *amap;
  if(map != NULL && value != NULL){
    amap = map->implementation;
    for(i = 0; i < amap->size; i++){
      if(map->key_compare_fn(amap->info[i].key, key) == 0){
	*value = amap->info[i].data;
	return 1;
      }
    }
  }
  return 0;
}

/* 
   First search through array to find if key exists in array.  Returns 0 
   if map is null or if key does not exist in array.  Checks if the 
   delete_fns passed through are NULL.  If not, use delete_fns to free 
   the Data and Key pointers of the index in array.  Then loop from the 
   end of the array(size not capacity) and shift the array to the left. 
   Decrement the map's size by 1.  Returns 1 otherwise.

   If the difference between the capacity and size of the array is 15 
   (Don't need to check >15 because it won't jump over 15...hopefully), 
   decrease the capacity by 10, and reallocate the size of the array.
*/
int remove_key(Hash_map *map, Key key){
  int i, j;
  Array_hash_map *amap;
  if(map != NULL){
    for(i = 0; (i < amap->size) && (map->key_compare_fn(amap->info[i].key, key) != 0); i++){
    }
    /*Sees if key exists in map*/
    if(map->key_compare_fn(amap->info[i].key, key) ==0){
      if(map->key_delete_fn != NULL)
	map->key_delete_fn(amap->info[i].key);
      if(map->data_delete_fn != NULL)
	map->data_delete_fn(amap->info[i].data);
      
      for(j = i + 1; j < amap->size; j++){
	amap->info[j-1].key = amap->info[j].key;
	amap->info[j-1].data = amap->info[j].data;
      }
      amap->size --;
      /*
	Checks if there are exactly 15 unused elements unless array's capacity is exactly 15. 
      */
      if(amap->capacity - amap->size == 15 && amap->capacity != 15){
	amap->capacity -= 10;
	amap->info = realloc(amap->info, amap->capacity * sizeof(Map));
      }
      return 1;
    }
  }
  return 0;
}


/*
  Function returns number of keys with the same value in array.
*/
int num_keys(Hash_map map, Data value){
  int i, num = 0;
  Array_hash_map *amap = map.implementation;
  for(i = 0; i < amap->size; i++){
    if(map.data_compare_fn(amap->info[i].data, value) == 0){
      num++;
    }
  }
  return num;
}
/*
  Returns the first index that key appears in array.  If not found, returns -1.
*/
int index_of(Hash_map map, Key key){
  int i;
  Array_hash_map *amap = map.implementation;
  for(i = 0; i < amap->size; i++){
    if(map.key_compare_fn(amap->info[i].key, key) == 0)
      return i;
  }
  return -1;
}

/*
  Returns the map capacity.
*/
int current_capacity(Hash_map map){
  Array_hash_map *amap = map.implementation;
  return amap->capacity;
}

/*
  Function finds the smallest key in array of map. The first index of 
  the array is the smallest  Then sets key and value paramaters to 
  corresponding elements of first index of the array.  Returns 0 if map's 
  first index is null or key/value parameters are NULL. Returns 1 otherwise.
*/
int get_smallest(Hash_map map, Key *key, Data *value){
  Array_hash_map *amap;
  if(key != NULL && value != NULL){
    amap = map.implementation;
    if(amap->size != 0){
      *key = amap->info[0].key;
      *value = amap->info[0].data;
      return 1;
    }
  }
  return 0;
}

/*
  Clears map.info of all values.  If either delete_fns are not NULL, 
  then it will free the corresponding value of all indices of the array.
  Then function will free map's info.
*/
void clear(Hash_map *map){
  int i;
  Array_hash_map *amap;
  if(map != NULL || map->implementation!= NULL){
    amap = map->implementation;
    if(amap->info != NULL){
      if(map->key_delete_fn != NULL || map->data_delete_fn != NULL)
	for(i = amap->size -1; i >= 0; i--){
	  if(map->key_delete_fn != NULL)
	    map->key_delete_fn(amap->info[i].key);
	  if(map->data_delete_fn != NULL)
	    map->data_delete_fn(amap->info[i].data);
	}
      free(amap->info);
    }
    free(amap);
  }
}

/*Creates a Linked_iterator, initializes it appropriately, causing it to be connected
to or refer to the Hash_map that was passed into create_iterator(), with the 
iteration point at its beginning and return it.
*/
Iterator create_iterator(Hash_map map){
  Iterator to_return = NULL;
  Array_iterator *itr;
  Array_hash_map *a_map = NULL;
  a_map = (Array_hash_map *) map.implementation;
  itr = malloc(sizeof(Array_iterator));
  if(itr == NULL){
    printf(ALLOC);
    exit(-1);
  }
  itr->hash_map = a_map;
  itr->array = a_map->info;
  itr->current = 0;
  to_return = (Iterator) itr;
  return to_return;

}
