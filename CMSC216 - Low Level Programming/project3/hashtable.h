#if ! defined(HASHTABLE_H)
#define HASHTABLE_H

#if ! defined(INIT_BUCKETS)
#define INIT_BUCKETS 5
#endif

typedef struct node {
  char *key;
  char *value;
  struct node *next;
} Data_pair_node;

typedef Data_pair_node * Hash_bucket;

struct hash_table {
  int key_ct;
  int bucket_ct;
  Hash_bucket *buckets;
};

typedef struct hash_table Table;

Table *create_table();
void reset_table(Table *);
void destroy_table(Table *);

unsigned long hash_code(const char *);

int insert(Table *, const char *, const char *);
int search(Table *, const char *, char **);
int delete(Table *, const char *);
int key_count(Table *);
int bucket_count(Table *);
char **get_keys(Table *);
char **get_values(Table *);

#endif
