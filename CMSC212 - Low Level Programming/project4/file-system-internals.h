/* Josh Fann
   Section 0202
   Project 4
   
   Filesystem contains 2 pointers.  1, root keeps track of the root directory at all times.  2, curr keeps track of the user's current directory.

   Each node has a pointer to its parent node, and if it is a subdirectory, will point to a child node as well.  Next refers to the next node in the current directory.  
   Int type differentiates whether a node is a file or directory.  Name is the file/directory's name
*/

typedef struct node{
  char *name;
  int type; 
  /*type = 0 for file, type = 1 for directory*/
 
  struct node *child;
  struct node *parent;
  struct node *next;
}Node;

typedef struct Filesystem{
  Node *root;
  Node *curr;
}Filesystem;
