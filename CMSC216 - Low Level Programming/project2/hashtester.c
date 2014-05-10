#include "hashtable.h"
#include <stdio.h>
#include <sysexits.h>
#include <stdlib.h>
#include <string.h>
/* Josh Fann
   UID: 109901918
   jfann

   hashtester.c reads commands one line at a time, parses them and 
   then executes certain operations on a hash table.  
   Upon execution, hashtester.c initializes a single hash table, and 
   then performs operations on the table as instructed by the commands 
   the program reads.

*/

#define MAX_LEN 1024
#define ARG_ERR fprintf(stderr, "Wrong amount of arguments."); exit(EX_DATAERR);

void test_insert(Table *, char *, char*);
void test_search(Table *, char *);
void test_delete(Table *, char *);

int main(int argc, char *argv[]){
  int i;
  Table t;
  FILE *input;
  char buffer[MAX_LEN];
  char command[MAX_LEN], a[MAX_LEN], b[MAX_LEN], c[MAX_LEN];
  init_table(&t);  
  if(argc == 1)
   input = stdin;
  if(argc == 2)
    if((input = fopen(argv[1], "r"))== NULL){
      fprintf(stderr, "Error opening file.");
      exit(EX_OSERR);
    }
  if(argc > 2){
   fprintf(stderr,"Too many arguments.");
   exit(EX_USAGE);
  }
  while(fgets(buffer, MAX_LEN, input) != NULL){
   if(strchr(buffer, '\n') == NULL){
     fprintf(stderr, "Command is too long.");
     exit(EX_DATAERR);
   }
   if(sscanf(buffer, "%s", command) == 1){
     if(*command != '#'){
       /* Insert */
       if(strcmp(command, "insert") == 0){               /*Insert*/
	 if(sscanf(buffer, "%s %s %s %s", command, a, b, c) != 3){
	   ARG_ERR;
	 }
	 test_insert(&t, a, b);
       }else if(strcmp(command, "search") == 0){          /*Search*/
	 if(sscanf(buffer, "%s %s %s ", command, a, b) !=2){
	   ARG_ERR;
	 }
	 test_search(&t, a);
       }else if(strcmp(command, "delete") == 0){          /*Delete*/
	 if(sscanf(buffer, "%s %s %s", command, a, b) != 2){
	   ARG_ERR;
	 }
	 test_delete(&t, a);
       }else if(strcmp(command, "reset") == 0){            /*Reset*/
	 if(sscanf(buffer, "%s %s", command, a) != 1){
	   ARG_ERR;
	 }
	 reset_table(&t);
	 printf("Table reset.\n");
	 
       }else if(strcmp(command, "display") == 0){     /*Display*/
	 if(sscanf(buffer, "%s %s %s", command, a, b) != 2){
	   ARG_ERR;
	 }
	 /*Displaying key_count*/
	 if(strcmp(a, "key_count") == 0)
	   printf("Key count: %d\n", key_count(&t));
	 
	 /*Displaying table*/
	 else if(strcmp(a, "table") == 0){
	   for(i = 0; i < NUM_BUCKETS; i++){
	     printf("Bucket %d: ", i);
	     if(t.buckets[i].state == EMPTY)
	       printf("EMPTY");
	     if(t.buckets[i].state == DIRTY)
	       printf("DIRTY");
	     if(t.buckets[i].state == FULL)
	       printf("FULL (%s => %s)", t.buckets[i].data.key, 
		      t.buckets[i].data.value);
	     printf("\n");
	   }
	 }
       }else{
	 ARG_ERR;
       }
     }
   }
  }
  return 0;
}

void test_insert(Table *t, char* key, char* val){
  printf("Insertion of %s => %s", key, val);
  if(!insert(t, key, val))
    printf(" succeeded.\n");
  else
    printf(" failed.\n");
}

void test_search(Table *t, char *key){
  char *val = NULL;
  printf("Search for %s ", key);
  if(!search(t, key, val))
    printf("%s\n", val);
  else
    printf("failed.\n");
}

void test_delete(Table *t, char *key){
  printf("Deletion of %s ", key);
  if(!delete(t, key))
    printf("succeeded.\n");
  else
    printf("failed.\n");

}
