/* Josh Fann
   CMSC212 Project #3
   Section 0202
   4/3/10
*/

#include "poly.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Dynamically allocates memory of size Polynomial.  If does not work, returns "Memory allocation failed"*/
Polynomial new(void){
  Polynomial *to_return = malloc(sizeof(Polynomial));
  if(to_return == NULL){
    printf("Memory allocation failed: \n");
    exit(1);
  }
  return *to_return;
}

/*Adds term to polynomial of coefficient coeff of degree expon.  If term of same degree exists, adds the coefficients and sets new coeff.  If new coeff is 0, term is removed from polynomial.  That term's memory is then freed. */
void add_term(Polynomial *p, double coeff, int expon){
  Term *current = p->head, *new_term = malloc(sizeof(Term));
  if(new_term == NULL){
    printf("Memory allocation failed:\n");
    return;
  }
  if(coeff == 0){
    free(new_term);
    return;
  }
  new_term->coeff = coeff;
  new_term->degree = expon;
  if(current == NULL){
    new_term->next = NULL;
    new_term->prev = NULL;
    p->head = new_term;
    return;
  }
  while(current != NULL){
    if(current->degree == expon){
      current->coeff += coeff;
      free(new_term);
      if(current->coeff == 0){
	/*If first node is to be removed*/
	if(current->degree == p->head->degree)
	  p->head = current->next;
	else{
	  (current->prev)->next = current->next;
	}
	/* If current isn't at last node*/
	if(current->next == NULL){
	  (current->prev)->next = NULL;
	}
	free(current);
      }
      return;
    }else if(current->degree < expon){ /* When term should be inserted before current term*/
      if(current->degree == p->head->degree){ /*If the inserted term should be in the first index*/
	new_term->prev = NULL;
	p->head = new_term;
      }else{  /*If the inserted term is after the first term.  Sets previous term's next to new_term.  new_term's prev is the previous term*/
	(current->prev)->next = new_term;
	new_term->prev = current->prev;
      }
      new_term->next = current;
      current->prev = new_term;
      return;
    }
    if(current->next == NULL){
      current->next = new_term;
      new_term->next = NULL;
      new_term->prev = current;
      return;
    }
    current = current->next;
  }
}
/*Prints statements as described in the project description.  Negatives are taken care of by a -1 multiplied by the coefficent if coeff < 0.  Then a " - " or "-"(if the first term is negative) is appended in front of the number. */
void print(Polynomial p){
  Term *current = p.head;
  int count = 0, neg;
  if(current == NULL)
    printf("0");
  while(current != NULL){
    if(current->coeff !=0){
      if(current->coeff > 0)
	neg = 1;
      else
	neg = -1;
      if(count != 0){    /*not first term*/
	if(current->coeff >0){
	  printf(" + ");
	  neg = 1;
	}
	else if(current->coeff <0){
	  printf(" - ");
	  neg = -1;
	}
      }else
	if(current->coeff < 0)
	  printf("-");

      if(current->degree > 1){
	if(neg*(current->coeff) == 1)
	  printf("x^%d", current->degree);
	else
	  printf("%gx^%d", neg*(current->coeff), current->degree);
      }else if(current->degree == 1){
	if(neg*(current->coeff) == 1)
	  printf("x");
	else
	  printf("%gx", neg*(current->coeff));
      }else if(current->degree == 0){
	printf("%g", neg*(current->coeff));
      }
    }
    count++;
    current = current->next;
  }
}
/*Uses Horner method to evaluate polynomial.  Using a bit of recursion, polynomial loops through and multiplies previous value times double n. Then adds the current Term's coeff.  Does the exponents of ones with 0 as well.*/
double evaluate(Polynomial p, double n){
  double value = 0;
  Term *current = p.head;
  int index;
  if(current == NULL)
    return value;

  index = p.head->degree;
  while(current != NULL){
    value *= n;
    if(current->degree == index){
      value += current->coeff;
      index--;
    }
    current = current->next;
  }
  return value;
}

/*Differentiates and removes last term if it is of 0 degree*/
Polynomial differentiate(Polynomial p){
  Polynomial diff = new();
  Term *current = p.head;

  while(current != NULL){
    if(current->degree > 0){
      add_term(&diff, ((current->coeff) * (current->degree)), 
	       current->degree -1);
      current = current->next;
    }
  }
  return diff;
}

/*Creates a new polynomial.  Copies all terms of one polynomial to the linked list.  Then adds each of the second linked list's terms.  Removes any that come out to be of 0 coeff.*/
Polynomial add(Polynomial p, Polynomial q){
  Polynomial added = new();
  Term *current = p.head;

  while(current != NULL){
    add_term(&added, current->coeff, current->degree);
    current = current->next;
  }
  current = q.head;

  while(current != NULL){
    add_term(&added, current->coeff, current->degree);
    current = current->next;
  }
  return added;
}

/*Returns number of terms in the polynomial.  Uses a counter until the current node is NULL.  Then returns the counter */
int num_terms(Polynomial p){
  int count=0;
  Term *current = p.head;

  while(current!=NULL){
    count++;
    current = current->next;
  }
  return count;
}

/*Returns the highest degree of polynomial.  Highest degree in this ordered polynomial is the head node's degree.*/
int degree(Polynomial p){
  if(p.head->degree == 0)
    return 0;
  else
    return p.head->degree;
}

/*Free's all Terms in the Polynomial passed through. */
void clear(Polynomial *p){
  Term *prev = p->head;
  Term *current;
  if (prev != NULL)
    current = prev->next;

  while (prev != NULL){
    free(prev);

    if (current != NULL){
      prev = current;
      current = current->next;
    } else
      prev = NULL;
  }
  return;
}    
