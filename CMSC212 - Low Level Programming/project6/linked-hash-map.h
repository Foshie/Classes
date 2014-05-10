#if !defined(LINKED_HASH_MAP_H)
#define LINKED_HASH_MAP_H

#include "hash-map.h"
typedef struct node{
  Key key;
  Data data;
  struct node *next;
  struct node *prev;
} Node;

typedef struct{
  struct node *head;
  int size;
} Linked_hash_map;
#endif
