#if !defined(ARRAY_ITERATOR_H)
#define ARRAY_ITERATOR_H

#include "array-hash-map.h"
typedef struct iterator{
  Array_hash_map *hash_map;
  Map *array;
  int current;

}Array_iterator;

#endif
