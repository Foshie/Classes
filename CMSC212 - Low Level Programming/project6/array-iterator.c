/*Josh Fann
Section 0202
Project 6
*/

#include "iterator.h"
#include "array-iterator.h"
#include <stdio.h>
#include <stdlib.h>

/*Resets the iterator iter so it will still be connected to or iterating 
over the same Hash_map, but the iteration point will be located just as
it would have been immediately after it was created by creater_iterator().*/
void reset(Iterator *iter){
  Array_iterator *a_iter;
  if(iter != NULL){
    a_iter = (Array_iterator *) (*iter);
    a_iter->current = 0;
    a_iter->array = &(a_iter->hash_map->info[0]);
  }
}



/*Returns 1 if the iterator iter hsa not yet iterated over or returned all
of the elements i the Hash_map it is connected to or iterating over(i.e., 
if any are left), and 0 otherwise*/
int has_next(Iterator iter){
  Array_iterator *a_iter = (Array_iterator *) (iter);
  return (a_iter->current < a_iter->hash_map->size);
}

/*Returns a pointer to the current value in the Hash_map that iter is connected 
  to or iterating over.  Then iterates to the next value.*/
Data *next(Iterator *iter){
  Array_iterator *a_iter;
  Data *to_return;
  if(iter == NULL)
    return NULL;
  a_iter = (Array_iterator *) (*iter);
  to_return = &(a_iter->array->data);
  a_iter->current ++;
  a_iter->array =&(a_iter->hash_map->info[a_iter->current]);
  return to_return;
}


/*Frees all the dynamically allocate memory used by iter.*/
void clear_iterator(Iterator *iter){
  Array_iterator *temp;
  if(iter != NULL){
    temp= (Array_iterator *)(*iter);
    free(temp);
  }
}
