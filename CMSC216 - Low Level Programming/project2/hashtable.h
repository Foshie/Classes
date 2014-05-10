#if ! defined(HASHTABLE_H)
#define HASHTABLE_H

#if ! defined(MAX_STR_SIZE)
#define MAX_STR_SIZE 500
#endif

#if ! defined(NUM_BUCKETS)
#define NUM_BUCKETS 5
#endif

typedef enum { EMPTY, FULL, DIRTY } Bucket_state;

typedef struct {
  char key[MAX_STR_SIZE + 1];
  char value[MAX_STR_SIZE + 1];
} Data_pair;

typedef struct {
  Bucket_state state;
  Data_pair data;
} Hash_bucket;

struct hash_table {
  int key_ct;
  Hash_bucket buckets[NUM_BUCKETS];
};

typedef struct hash_table Table;

void init_table(Table *);
void reset_table(Table *);
int insert(Table *, const char *, const char *);
int search(Table *, const char *, char *);
int delete(Table *, const char *);
int key_count(Table *);
int bucket_count(Table *);
unsigned long hash_code(const char *);

#endif
