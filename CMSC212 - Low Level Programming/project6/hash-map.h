#if !defined(HASH_MAP_H)
#define HASH_MAP_H

#include "iterator.h"
#include "types.h"

typedef int (*Key_compare_fn)(const Key x, const Key y);
typedef void (*Key_delete_fn)(Key key);
typedef int (*Data_compare_fn)(const Data x, const Data y);
typedef void (*Data_delete_fn)(Data value);

typedef struct {
  Key_compare_fn key_compare_fn;
  Key_delete_fn key_delete_fn;
  Data_compare_fn data_compare_fn;
  Data_delete_fn data_delete_fn;
  void *implementation;
} Hash_map;

Hash_map create(Key_compare_fn compare_key, Key_delete_fn delete_key,
                Data_compare_fn compare_data, Data_delete_fn delete_data);
int put(Hash_map *map, Key key, Data value);
int size(Hash_map map);
int get(Hash_map *map, Key key, Data *value);
int remove_key(Hash_map *map, Key key);
int num_keys(Hash_map map, Data value);
int index_of(Hash_map map, Key key);
int current_capacity(Hash_map map);
int get_smallest(Hash_map map, Key *key, Data *value);
void clear(Hash_map *map);
Iterator create_iterator(Hash_map map);

#endif
