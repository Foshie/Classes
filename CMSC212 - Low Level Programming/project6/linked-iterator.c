/*Josh Fann
Section 0202
Project 6
*/

#include "iterator.h"
#include "linked-iterator.h"
#include <stdio.h>
#include <stdlib.h>

/*Resets the iterator iter so it will still be connected to or iterating 
over the same Hash_map, but the iteration point will be located just as
it would have been immediately after it was created by creater_iterator().*/
void reset(Iterator *iter){
  Linked_iterator *l_iter;
  if(iter != NULL){
     l_iter= (Linked_iterator *) (*iter);
     l_iter->linked_node = l_iter->hash_map->head;
     l_iter->index = 1;
  }
}

/*Returns 1 if the iterator iter hsa not yet iterated over or returned all
of the elements i the Hash_map it is connected to or iterating over(i.e., 
if any are left), and 0 otherwise*/
int has_next(Iterator iter){
  Linked_iterator *l_iter = (Linked_iterator *) iter;
  return l_iter->index <= l_iter->hash_map->size;
}

/*Returns a pointer to the next value in the Hash_map that iter is connected 
  to or iterating over.*/
Data *next(Iterator *iter){
  Linked_iterator *l_iter;
  Data *to_return;
  if(iter == NULL)
    return NULL;
  l_iter = (Linked_iterator *) *iter;
  to_return = &(l_iter->linked_node->data);
  l_iter->index++;
  l_iter->linked_node = l_iter->linked_node->next;
  return to_return;

}

/*Frees all the dynamically allocate memory used by iter.*/
void clear_iterator(Iterator *iter){
  Linked_iterator *temp;
  if(iter != NULL){
    temp = (Linked_iterator *)(*iter);
    free(temp);
  }
}
