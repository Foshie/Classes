/*
  Josh Fann
  Section 0202
*/

/*
  Array hash map has an array of struct Map, 
  which contains Data and Key values.*/
#if defined(ARRAY_HASH_MAP)
typedef struct map{
  Key key;
  Data data;
}Map;

typedef struct Hash_map {
  struct map *info;
  int size;
  int capacity;
  Key_compare_fn c_key;
  Key_delete_fn d_key;
  Data_compare_fn c_data;
  Data_delete_fn d_data;
} Hash_map;

/*
  #else is assumed to mean that LINKED_HASH_MAP is defined.
  Linked hash map has a pointer to the head of a Node,
  which contains Key and Data values.

  It is a doubly-linked list to help keep track of nodes
  when writing the get function.

  Note: There is no capacity like in the ARRAY_HASH_MAP 
  because capacity will always be infinite or INT_MAX
*/
#else
typedef struct node {
  Key key;
  Data data;
  struct node *next;
  struct node *prev;
} Node;

typedef struct Hash_map {
  struct node *head;
  int size;
  Key_compare_fn c_key;
  Key_delete_fn d_key;
  Data_compare_fn c_data;
  Data_delete_fn d_data;
} Hash_map;
#endif
