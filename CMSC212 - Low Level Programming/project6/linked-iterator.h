#if !defined(LINKED_ITERATOR_H)
#define LINKED_ITERATOR_H

#include "linked-hash-map.h"
typedef struct{
  Linked_hash_map *hash_map;
  Node *linked_node;
  int index;

}Linked_iterator;

#endif
