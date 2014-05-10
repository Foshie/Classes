/*
  Josh Fann
  CMSC212 0202

  Linked-hash-map simulates Java's HashMap class.  This simulation uses a simple
  method for allowing a program in C to subsitute one implementation of a set 
  of functions for another, without altering the program.  HashMap maps keys 
  to values.  The hash table is not implemented in this simulation.

  Linked-hash-map is a doubly linked list of nodes that have Key keys and 
  Data data.  Linked list is not sorted but inserted to the end of the linked 
  list.  When get is used, the move-to-front heuristic is used, which moves the
  "gotten" node to the head the new head points to the old head node.
*/

#define ALLOC "Memory allocation failed!\n"

#include "linked-iterator.h"
#include "linked-hash-map.h"
#include "hash-map.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

/*
  Returns a Hash_map with size 0.  Initializes the head pointer correctly.  
  Linked hash map does not worry about capacity because it is infinite.  
  If compare_key or compare_data are NULL or malloc-ing goes wrong, exits 
  with -1. 
*/
Hash_map create(Key_compare_fn compare_key, Key_delete_fn delete_key,
                Data_compare_fn compare_data, Data_delete_fn delete_data){

  Hash_map map;
  Linked_hash_map *imp;
  if(compare_key == NULL || compare_data == NULL){
    printf("NULL comparison function disallowed.\n");
    exit(-1);
  }
  imp = malloc(sizeof(Linked_hash_map));
  if(imp == NULL){
    printf(ALLOC);
    exit(-1);
  }
  map.key_compare_fn = compare_key;
  map.key_delete_fn = delete_key;
  map.data_compare_fn = compare_data;
  map.data_delete_fn = delete_data;
  imp->head = malloc(sizeof(Node));
  if(imp->head == NULL){
    printf(ALLOC);
    exit(-1);
  }
  imp->head->next = NULL;
  imp->head->prev = NULL;
  imp->size = 0;
  map.implementation = imp;
  return map;
}

/*
  Inserts a node with key and value at the end of the linked list.  
  If a key already exists, the new value overwrites the old value. 
  Then returns 1 without increasing the size.

  Returns 0 when map is NULL.  Returns 1 otherwise and increase the map's size.
*/
int put(Hash_map *map, Key key, Data value){
  Node *curr, *new_node;
  Linked_hash_map *lmap;
  if(map == NULL){
    return 0;
  }
  lmap = map->implementation;
  curr = lmap->head;
  /* Case 1: Head node is put.*/
  if(lmap->size == 0){
    if(curr == NULL){
      curr = malloc(sizeof(Node));
      if(curr == NULL){
	printf(ALLOC);
	exit(-1);
      }
    }
    curr->key = key;
    curr->data = value;
    curr->next = NULL;
    curr->prev = NULL;
    lmap->head = curr;
  }
  else{
    /* Case 2: If key already exists, overwrite data to value*/
    while(curr->next != NULL && map->key_compare_fn(curr->key, key) != 0){
      curr = curr->next;
    }
    /* If key exists*/
    if(map->key_compare_fn(curr->key, key) == 0){
      if(map->data_delete_fn != NULL)
	map->data_delete_fn(curr->data);
      if(map->key_delete_fn != NULL)
	map->key_delete_fn(key);
      curr->data = value;
      lmap->size-=1;
    }
    else{
      new_node = malloc(sizeof(Node));
      if(new_node == NULL){
	printf(ALLOC);
	exit(-1);
      }
      /* Case 3: At the end of linked list.*/
      new_node->key = key;
      new_node->data = value;
      new_node->next = NULL;
      new_node->prev = curr;
      curr->next = new_node;
    }
  }
  lmap->size += 1;
  return 1;
}

/*
  Returns the current map size.
*/
int size(Hash_map map){
  Linked_hash_map *lmap = map.implementation;
  return lmap->size;
}

/*
  Checks if parameters and head node are valid. Returns 0 otherwise.
  Loops through to find the key parameter in the linked list. 
  If key is found, value parameter is set to node's data.  
  Node's prev and next are then linked together and node becomes the 
  new head node.  Note: If key is in head node, doesn't do anything.  Returns 1
*/
int get(Hash_map *map, Key key, Data *value){
  Node *curr;
  Linked_hash_map *lmap;
  if(map != NULL && value != NULL){
    lmap = map->implementation;
    if(lmap->size != 0){
      curr = lmap->head;
      
      while(curr != NULL){
	/* Key is found!*/
	if(map->key_compare_fn(curr->key, key) == 0){
	  *value = curr->data;
	  /* Case 1: When node found is the head node, just return 1*/
	  if(curr->prev != NULL){
	    /* Case 2: When node found is not on either ends of linked list*/
	    if(curr->next != NULL){
	      curr->next->prev = curr->prev;
	    }
	    /* Case 2, 3: When node found is after the head node*/
	    curr->prev->next = curr->next;
	    curr->prev = NULL;
	    lmap->head->prev = curr;
	    curr->next = lmap->head;
	    lmap->head = curr;
	  }
	  return 1;
	}
	curr = curr->next;
      }
    }
  }
  return 0;
}

/*
  Returns 1 if key exists in linked list and was removed correctly.  
  Map's size decrements by 1 if successful.  Returns 0 if map is NULL or
  the head pointer of map is NULL or if key is not in the linked list.
*/ 
int remove_key(Hash_map *map, Key key){
  Node *curr;
  Linked_hash_map *lmap;
  if(map != NULL && map->implementation != NULL){
    lmap = map->implementation;
    curr= lmap->head;
    /*
      When key is found in linked list, frees node by changing it's prev and nexts' pointers correctly.  Then frees the values inside Node if need be and then free Node.
    */
    while(curr!= NULL){
      if(map->key_compare_fn(curr->key, key) == 0){
	/* Case 1: Node to be removed is at head.*/
	if(curr->prev == NULL){
	  lmap->head = curr->next;
	  if(curr->next != NULL)
	    lmap->head->prev = NULL;
	}
	/* Case 2: Node is between ends of linked list. */
	else{
	  if(curr->next != NULL)
	    curr->next->prev = curr->prev;    
	  /* Case 2, 3: Does not matter if Node is at end or after head.*/
	  curr->prev->next = curr->next;
	}
	/* Checks if delete_fns need to be used for the Node's values.*/
	if(map->key_delete_fn != NULL)
	  map->key_delete_fn(curr->key);
	if(map->data_delete_fn != NULL)
	  map->data_delete_fn(curr->data);
	free(curr);
	(lmap->size)--;
	return 1;
      }
      curr = curr->next;
    }
  }
  return 0;
}

/*
  Returns number of keys in linked list that have the same value.
*/
int num_keys(Hash_map map, Data value){
  int count = 0;
  Linked_hash_map *lmap = map.implementation;
  Node *curr = lmap->head;
  while(curr != NULL && lmap->size != 0){
    if(map.data_compare_fn(value, curr->data)==0){
	count++;
    }
    curr = curr->next;
  }
  return count;
}

/*
  Returns first index of the linked list when key is found. 
  Returns -1 when not found.
*/
int index_of(Hash_map map, Key key){
  int index = 0;
  Linked_hash_map *lmap = map.implementation;
  Node *curr = lmap->head;
  while(curr != NULL && lmap->size != 0){
    if(map.key_compare_fn(key, curr->key) == 0)
      return index;
    index++;
    curr = curr->next;
  }
  return -1;
}

/*
  Because map is a linked-list, INT_MAX will always be returned as 
  current capacity.
*/
int current_capacity(Hash_map map){
  return INT_MAX;
}

/*
  Returns 0 if head node of map, key or value are all NULL.  
  Otherwise, finds key with smallest value.

  First sets the head to smallest node.  Then moves to next node and 
  checks data to see which is larger.  If the new node is smaller, 
  "smallest" is set to the new node.  Returns 1 after parameter's key 
  and value are set to smallest' key and data.
*/
int get_smallest(Hash_map map, Key *key, Data *value){
  Node *curr, *smallest;
  Linked_hash_map *lmap = map.implementation;
  if(key != NULL && value != NULL && lmap->size != 0){
    curr = lmap->head;
    smallest = curr;
    while(curr != NULL){
      if(map.key_compare_fn(curr->key, smallest->key) < 0){
	smallest = curr;
      }
      curr = curr->next;
    }
    *key = smallest->key;
    *value = smallest->data;
    return 1;
  }
  return 0;
}

/* Helper function that frees a node from a linked list.  Parameters k 
   and d are used to see if the delete_fns are NULL.*/
void clear_h(Hash_map *map, Node *root, int k, int d){
  if(root->next != NULL){
    clear_h(map, root->next, k, d);
  }
  if(root->next == NULL){
    /*At head node*/
    if(root->prev != NULL){
      root->prev->next = NULL;
    }
    if(k != 0)
      map->key_delete_fn(root->key);
    if(d != 0)
      map->data_delete_fn(root->data);
    free(root);
  }
}

/*
  Recursively free's all nodes from function. 
*/
void clear(Hash_map *map){
  Node *head;
  Linked_hash_map *lmap = map->implementation;
  if(map != NULL || lmap != NULL){
    if(lmap->head != NULL){
      head = lmap->head;
      clear_h(map, head, map->key_delete_fn != NULL, map->data_delete_fn != NULL);
    }
    free(lmap);
  }
}
/*Creates a Linked_iterator, initializes it appropriately, causing it to be connected
to or refer to the Hash_map that was passed into create_iterator(), with the 
iteration point at its beginning and return it.
*/

Iterator create_iterator(Hash_map map){
  Iterator to_return;
  Linked_iterator *iter;
  Linked_hash_map *lmap = NULL;
  lmap = (Linked_hash_map *) map.implementation;
  iter = malloc(sizeof(Linked_iterator));
  if(iter == NULL){
    printf(ALLOC);
    exit(-1);
  }
  iter->hash_map = lmap;
  iter->index = 1;
  iter->linked_node =lmap->head;
  to_return = (Iterator) iter;
  return to_return;
}
