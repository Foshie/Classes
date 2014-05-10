/*Josh Fann
   CMSC212 Project #3
   Section 0202
   4/3/10

   Structs were set up so Polynomial points to the head Term.  Terms are doubly linked lists to keep track of what was right before and what is after current term. 

*/


typedef struct Term{
  int degree;
  double coeff;

  struct Term *next;
  struct Term *prev;
}Term;

typedef struct Polynomial{
  Term *head;
}Polynomial;
