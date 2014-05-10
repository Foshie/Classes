#include "poly.h"

Polynomial new(void);
void add_term(Polynomial *p, double coeff, int expon);
void print(Polynomial p);
double evaluate(Polynomial p, double n);
Polynomial differentiate(Polynomial p);
Polynomial add(Polynomial p, Polynomial q);
int num_terms(Polynomial p);
int degree(Polynomial p);
void clear(Polynomial *p);
