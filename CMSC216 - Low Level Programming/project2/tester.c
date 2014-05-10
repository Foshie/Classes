
  Table t;

  init_table(&t);
  /* New Line*/
  if(*str == '\0'){

  }
  /* Comment*/
  if(*str == '#'){

  }
  /* Command*/
  else{

    
    /*Reset Table*/
    reset_table(&t);
    printf("Table reset.");

    /*Display Item*/
    if(strcmp(arg1, "key_count")==0)
      printf("Key count: %d", key_count(&t));
    else if(strcmp(arg1, "table") == 0)
      for(int i = 0; i < NUM_BUCKETS){
	printf("Bucket %d: %s", i, t->buckets[i].state);
	if(t->buckets[i].state == FULL)
	  printf("(%s => %s)", t->buckets[i].data.key, 
		 t->buckets[i].data.value);
	printf("\n");
      }
  }
  return 0;
}

void test_insert(Table *t, char* key, char* val){
  printf("Insertion of %s => %s", key, val);
  if(!insert(&t, key, val))
    printf("succeeded.");
  else
    printf("failed.");
}

void test_search(Table *t, char *key){
  char *val = NULL;
  printf("Search for %s ", key);
  if(!search(&t, key, val))
    printf("%s", val);
  else
    printf("failed.");
}

void test_delete(Table *t, char *key){
  printf("Deletion of %s ", key);
  if(!delete(&t, key))
    printf("succeeded.");
  else
    printf("failed.");
