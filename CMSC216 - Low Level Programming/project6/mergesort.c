#include <pthread.h>
#include <err.h>
#include <sysexits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"
/* Josh Fann
   Directory ID: jfann  UID: 109901918
   Project 6 mergesort.c
*/

/* This project implements two mergesort implementations: one without multi-
   threading and one with the ability to operate up to 4 threads.
*/


typedef struct{
  void *arr;
  size_t num_elem;
  size_t elem_size;
  Compare_fn cmp;
}Thread_args;

void *mt_helper(void *args){
  Thread_args *arg = args;
  mergesort(arg->arr, arg->num_elem, arg->elem_size, arg->cmp);
  return NULL;
}

/* This function sorts the first num_elem elements of the array arr using the
   comparison function f to define the ordering of elements.  It should use the
   mergesort algorithm to perform its sorting.  If either arr or f is NULL, 
   the function should just return, doing nothing to the input array.
*/
void merge(char *left, char *right, size_t num1, size_t num2, 
	   size_t elem_size, Compare_fn cmp){
  int index = 0, l_index = 0, r_index = 0;
  int l_size = num1 * elem_size, r_size = num2*elem_size;
  char *temp = calloc(elem_size, (num1+ num2));
  if(temp == NULL){
    err(EX_OSERR, "Memory allocation failed.\n");
  }
  /*Compares first index of left array to first index of right array.  If 
    left is smaller, inserts into temp array.  If right is smaller, inserts
    into temp array.  Finally, if one of the arrays reaches the end, the other
    array fills temp with that other array.

    Then copy num_1 of elements into left array and num2 of elements in right
    array.  Both arrays when put together are in sorted order.  Then free temp
  */
  while((l_index < l_size) && (r_index < (r_size))){
    while((l_index< (l_size)) && 
	  (cmp(left + l_index, right + r_index) <= 0)){
      memcpy(temp + index, left + l_index, elem_size);
      index += elem_size;
      l_index += elem_size;
    }
    if(l_index < l_size){
      while((r_index < r_size) && (cmp(right + r_index, 
				     left + l_index) <=0)){
	memcpy(temp + index, right + r_index, elem_size);
	index += elem_size;
	r_index += elem_size;
      }
    }
  }
  memcpy(temp + index, left + l_index, l_size - l_index);
  memcpy(left, temp, l_size);
  
  memcpy(temp + index, right + r_index, r_size - r_index);
  memcpy(right, temp + l_size, r_size);
  free(temp);
}

void mergesort(void *arr, size_t num_elem, size_t elem_size, Compare_fn cmp){
  char *t_arr = (char *) arr;
  int num_left = num_elem/2, num_right;
  if(t_arr != NULL && cmp != NULL){
    /*Base case*/
    if(num_elem > 1){
      /*Determines if num_left needs to increment 1 if num_elem is odd*/
      if(num_elem %2 == 1)
	num_left +=1;
      num_right = num_elem/2;
      
      /* Goes to lowest levels and will compare the left and right of 1 element
	 arrays.  Then "merges" them by rearranging them in the passed in arrays
      */
      mergesort(t_arr, num_left, elem_size, cmp);
      mergesort(t_arr + num_left*elem_size, num_right, elem_size, cmp);
      merge(t_arr, t_arr + num_left*elem_size, num_left, num_right, 
           elem_size, cmp);
  
    }
  }
}

/* This function splits the work to be done among thread_ct new worker threads
   (i.e., there should be thread_ct + 1 threads, including the main thread).  
   So the main thread should not do any sorting work while the worker threads
   are doing their work.  If thread_ct is not one of {1, 2, 4}, this function
   should just return.
*/
void mt_mergesort(void *arr, size_t num_elem, size_t elem_size, Compare_fn cmp,
                  int num_threads){

  int i=0;
  int  r_size=0, l_size=0;
  int offset = 1, right_offset=1;
  int modcount = num_elem % num_threads;
  pthread_t tid[4];
  char* t_arr = (char *) arr;
  Thread_args arg[4];
  if(cmp != NULL && arr != NULL){
    if(num_threads == 1 || num_threads == 2 || num_threads == 4){
      /* Creates num_threads with given parameters to pass into mergesort*/
      for(i = 0; i < num_threads; i++){
	if(modcount == 0)
	  offset = 0;
	else
	  modcount--;
	
	arg[i].elem_size = elem_size;
	arg[i].cmp = cmp;
	arg[i].num_elem = num_elem/num_threads + offset;
	arg[i].arr = t_arr + elem_size*(l_size);
	l_size += arg[i].num_elem;

	if(pthread_create(&tid[i], NULL, mt_helper, &arg[i]))
	  err(EX_OSERR, "Create thread fail.\n");
      }

      /* Reap threads*/
      for(i = 0; i < num_threads; i++){
	if(pthread_join(tid[i], NULL))
	  err(EX_OSERR, "Thread join error.\n");
      }

      /* Merge sorted parts of the array from the threads together*/
      l_size = 0;
      offset = 1;
      modcount = num_elem%num_threads;
      for(i = 0; i < num_threads-1; i++){
	if(modcount == 0)
	  offset = 0;
	else
	  modcount--;
	l_size += num_elem/num_threads + offset;
	/*looks ahead to see if next part of array is offest by 1*/
	if(modcount == 0)
	  right_offset = 0;
	r_size = num_elem/num_threads + right_offset;
	merge(t_arr, t_arr + l_size*elem_size, l_size, r_size, elem_size, cmp);
      }
    }
  }
}
