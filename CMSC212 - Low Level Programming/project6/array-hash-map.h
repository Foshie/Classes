#if !defined(ARRAY_HASH_MAP_H)
#define ARRAY_HASH_MAP_H
#include "hash-map.h"
typedef struct map{
  Key key;
  Data data;
}Map;

typedef struct{
  struct map *info;
  int size;
  int capacity;
} Array_hash_map;
#endif
