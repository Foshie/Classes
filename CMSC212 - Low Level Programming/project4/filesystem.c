#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"


#define INVALID ("Missing or invalid operand.\n")
#define NODIR ("%s: No such file or directory.\n")
#define ALLOCATION ("(Memory allocation failed: \n")
#define EXISTS ("Cannot create directory %s: File exists.\n")

/* Josh Fann
   Project 4
   Section 0202

*/
void clear_next(Node *root);
void clear_child(Node *root);

void mkfs(Filesystem *files){
  Node *root = malloc(sizeof(Node));
  if(root == NULL){
    printf(ALLOCATION);
    return;
  }
  files->root = root;
  files->root->parent = NULL;
  files->root->next = NULL;
  files->root->child = NULL;
  files->root->type = 1;
  files->root->name = '\0';
  files->curr = files->root;

}
/*Creates a file if arg is a name that does not refer to an existing file/directory in the current directory or arg is not a ., .., /, empty string, or of a forward slash somewhere in arg.  Similar to mkdir because the way filesystem is setup.  Only difference is the setting of type.  Type is set to 0 to signify a file.*/

void touch(Filesystem *files, const char arg[]){
  Node *head = files->curr, *current, *prev = NULL, *new_term = calloc(1, sizeof(Node));
  
  /*If arg is an empty string(Null string).  Or a '/' is somewhere in the arg other than first character. */
  if(arg[0] == '\0'){
   printf(INVALID); 
   free(new_term);
   return;
 }

  /*If arg is a '.', '..', or '/', function has no effect.  Free new_term.*/ 
  if(arg[0] == '.'){
    free(new_term);
    return;
  }

  if(strchr(arg, '/') != NULL){
    if((int)strcmp(arg, "/") != 0)
      printf(INVALID);
    free(new_term);
    return;
  }

  /*Allocate memory to store file's name */
  new_term->name = malloc(((int)strlen(arg)+1) * sizeof(char));
 
  /*Check if current directory is empty.  If it is, create child file of directory.  Then exit function. */
  if(head->child == NULL){
    strcpy(new_term->name, arg);
    new_term->child = NULL;
    new_term->parent = head;
    new_term->next = NULL;
    new_term->type = 0;
    head->child = new_term;
    return;
  }
  current = head->child;
  new_term->child = NULL;
  new_term->parent = head;
  
  /*Looks through all children of current directory if arg already exists.  If it does, free new_term and exit.  List should be sorted lexicographically.  Exits loop after reaching the last node or arg should come before the current node's name.*/
  while(current != NULL && (int)strcmp(current->name, arg) <= 0){
    if(strcmp(current->name, arg) == 0){
      free(new_term->name);
      free(new_term);
      return;
    }
    prev = current;
    current = current->next;
  }
  if(prev == NULL)
    head->child = new_term;
  else
    prev->next = new_term;
  new_term->next = current;
  new_term->type = 0;
  strcpy(new_term->name, arg);
}

/*Creates a subdirectory of the current directory if arg does not refer to an existing file or directory in the current directory, a ., .., /, empty string, or a / somewhere in arg.  Due to the way filesystem is setup, mkdir and touch are essentially the same functions.  The only difference is that type is set to 1, indicating it is a directory. */

void mkdir(Filesystem *files, const char arg[]){
  Node *head = files->curr;
  Node *current; 
  Node *prev = NULL;
  Node *new_term = malloc(sizeof(Node));

  if(strchr(arg, '.') != NULL){
    printf(EXISTS, arg);
    return;
  }

  if(arg[0] == '\0'){
   printf(INVALID);
   free(new_term);
   return;
  }

  if(strchr(arg, '/') != NULL){
    if((int)strcmp(arg, "/") != 0)
      printf(INVALID);
    else
      printf(EXISTS, arg);
    return;
  }
  new_term->name = malloc(((int)strlen(arg)+1) * sizeof(char));

  if(head->child == NULL){
    strcpy(new_term->name, arg);
    new_term->child = NULL;
    new_term->parent = head;
    new_term->next = NULL;
    new_term->type = 1;
    head->child = new_term;
    return;
  }
  current = head->child;
  new_term->child = NULL;
  new_term->parent = head;
  new_term->type = 1;
  
  while(current != NULL && strcmp(current->name, arg) <=0){
    if(strcmp(current->name, arg) == 0){
      printf("Cannot create directory %s: File exists.\n", arg);
      free(new_term->name);
      free(new_term);
      return;
    }
    prev = current;
    current = current->next;
  }
  if(prev == NULL)
    head->child = new_term;
  else
    prev->next = new_term;
  new_term->next = current;
  strcpy(new_term->name, arg);
}

/* Changes directory to specified argument.  If arg is a special character: ., .., / or '\0' then print correct error statements.  Otherwise change directories.*/
void cd(Filesystem *files, const char arg[]){
  Node *dir = files->curr, *current;

  if(arg == '\0'){
    return;
  }
  if(arg[0] == '.'){
    if(arg[1] == '.'){
      if(files->curr->parent != NULL)
	files->curr = files->curr->parent;
    }
  return;
  }
  if(strchr(arg, '/') != NULL){
    if(strcmp(arg, "/") ==0)
      files->curr = files->root;
    else
      printf(NODIR, arg);
    return;
  }
  current = dir->child;
  while(current != NULL){
    if(strcmp(current->name, arg) == 0){
      if(current->type == 0){
	printf("%s: Not a directory.", arg);
	return;
      }
      else{
	files->curr = current;
	return;
      }
    }
    current = current->next;
  }
  printf(NODIR, arg);
}

/*This helper function only deals with directories passed through by the ls() function.  Loops through all children of current directory.*/
void ls_helper(Node *dir){
  Node *current = dir->child;
  while(current != NULL){
    printf("%s", current->name);
    if(current->type ==1)
      printf("/");
    printf("\n");
    current = current->next;
  }
}

/*ls() only determines what list of Nodes ls_helper will loop through to output.*/
void ls(Filesystem files, const char arg[]){
  Node *dir = files.curr, *curr_child = files.curr->child;
  if(arg[0] == '/'){
    ls_helper(files.root);
    return;
  }
  if(arg[0] == '.'|| arg[0] == '\0'){

    /*Will not enter if current directory is root.  Goes straight to what '.' would do.*/
    if(strstr(arg, "..")!= NULL && dir->parent != NULL){
      ls_helper(dir->parent);
      return;
    }
    ls_helper(dir);
    return;
  }

  /* Loops through the current directory's child to see if arg is a name that does refers to an existing file or directory. */
  while(curr_child != NULL){
    if(strcmp(arg, curr_child->name) == 0){
      /*If arg is a file, print the name of the file.*/
      if(curr_child->type == 0)
	printf("%s", arg);
      else
	ls_helper(curr_child);
      return;
    }
    curr_child = curr_child->next;
  }
  printf(NODIR, arg);
}
/*Recursive helper function for pwd.  Finds the root node, then prints from root to current directory.*/
void pwd_helper(Node *current){
  if(current->parent!= NULL)
    pwd_helper(current->parent);
  if(current->parent == NULL)
    return;
  printf("/%s", current->name);

}
void pwd(Filesystem files){
  Node *current = files.curr;

  /* Check to see if currently in root directory*/
  if(current->parent == NULL){
    printf("/\n");
    return;
  }
  pwd_helper(current);
  printf("\n");
}


void clear_next(Node *root){

  if(root->next != NULL)
    clear_next(root->next);

  clear_child(root);
}

void clear_child(Node *root){
  
  if(root->child != NULL){
    if(root->child->next != NULL)
      clear_next(root->child->next);
    clear_child(root->child);
  }
  /*Base Case*/
  if(root->parent!=NULL)
    free(root->name);
  free(root);

}

/* Using clear_next, clear_child, rmfs first finds the most extensive path.  Then recursively clear all nodes in files.*/
void rmfs(Filesystem *files){
  Node *root = files->root;
  clear_child(root);
}
