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

#define ARRAY_HASH_MAP
#define ALLOC "Memory allocation failed!\n"

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
  if(compare_key == NULL || compare_data == NULL){
    printf("NULL comparison function disallowed.\n");
    exit(-1);
  }
  to_return.info = calloc(10, sizeof(Map));
  if(to_return.info == NULL){
    printf("ALLOC");
    exit(-1);
  }
  to_return.size = 0;
  to_return.capacity = 10;
  to_return.c_key = compare_key;
  to_return.d_key = delete_key;
  to_return.c_data = compare_data;
  to_return.d_data = delete_data;

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
  if(map == NULL)
    return 0;
  if(map->size != 0){
    for(i = 0; i < map->size && map->c_key(map->info[i].key, key) <= 0; i++){
      if(map->c_key(map->info[i].key, key) == 0){
	if(map->d_data != NULL)
	  map->d_data(map->info[i].data);
	if(map->d_key != NULL)
	  map->d_key(key);
	map->info[i].data = value;
	exists = 1;
	map->size--;
      }
    }
    
    /* 
       Checks if map needs to increase the capacity.  If size = capacity, 
       add size of 10 Maps. Or if the new size will need a larger capacity.
    */
    if(map->size == map->capacity || map->size+1 == map->capacity){
      map->capacity += 10;
      map->info = realloc(map->info, map->capacity * sizeof(Map));
    }
    if(!exists)
    for(j = map->size -1; j >= i; j--){
      map->info[j+1].data = map->info[j].data;
      map->info[j+1].key = map->info[j].key;
    }
  }
  if(!exists){
    map->info[i].key = key;
    map->info[i].data = value;
  }
  map->size ++;

  return 1;
}

/*
  Returns current array's size
*/
int size(Hash_map map){
  return map.size;
}

/*
  Function loops through to find the key parameter in array.  If key is 
  found, value parameter is set to the key's corresponding data.  Returns
  0 if map or value is NULL or if key is not found in array.  Returns 1
  otherwise.
*/
int get(Hash_map *map, Key key, Data *value){
  int i;
  if(map != NULL && value != NULL)
    for(i = 0; i < map->size; i++){
      if(map->c_key(map->info[i].key, key) == 0){
	*value = map->info[i].data;
	return 1;
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
  if(map != NULL){
    for(i = 0; (i < map->size) && (map->c_key(map->info[i].key, key) != 0); i++){
    }
    /*Sees if key exists in map*/
    if(map->c_key(map->info[i].key, key) ==0){
      if(map->d_key != NULL)
	map->d_key(map->info[i].key);
      if(map->d_data != NULL)
	map->d_data(map->info[i].data);
      
      for(j = i + 1; j < map->size; j++){
	map->info[j-1].key = map->info[j].key;
	map->info[j-1].data = map->info[j].data;
      }
      map->size --;
      /*
	Checks if there are exactly 15 unused elements unless array's capacity is exactly 15. 
      */
      if(map->capacity - map->size == 15 && map->capacity != 15){
	map->capacity -= 10;
	map->info = realloc(map->info, map->capacity * sizeof(Map));
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
  for(i = 0; i < map.size; i++){
    if(map.c_data(map.info[i].data, value) == 0){
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
  for(i = 0; i < map.size; i++){
    if(map.c_key(map.info[i].key, key) == 0)
      return i;
  }
  return -1;
}

/*
  Returns the map capacity.
*/
int current_capacity(Hash_map map){
  return map.capacity;
}

/*
  Function finds the smallest key in array of map. The first index of 
  the array is the smallest  Then sets key and value paramaters to 
  corresponding elements of first index of the array.  Returns 0 if map's 
  first index is null or key/value parameters are NULL. Returns 1 otherwise.
*/
int get_smallest(Hash_map map, Key *key, Data *value){
  if(map.info == NULL || key == NULL || value == NULL)
    return 0;
  *key = map.info[0].key;
  *value = map.info[0].data;
  return 1;
}

/*
  Clears map.info of all values.  If either delete_fns are not NULL, 
  then it will free the corresponding value of all indices of the array.
  Then function will free map's info.
*/
void clear(Hash_map *map){
  int i;
  if(map == NULL || map->info == NULL)
    return;
  if(map->d_key != NULL || map->d_data != NULL)
    for(i = map->size -1; i >= 0; i--){
      if(map->d_key != NULL)
	map->d_key(map->info[i].key);
      if(map->d_data != NULL)
	map->d_data(map->info[i].data);
    }
  free(map->info);
}
