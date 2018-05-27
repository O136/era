#include<stdio.h>
#include "polynom.h"


void printPolynome(struct polynom p) {
 printf("Degree: %i\n", p.iDegree);
 printf("Coefficients:");
 for(int i=0; i < p.iDegree; ++i) {
   printf(" %f ", p.p_fCoefficients[i]);
 }
 printf("\n");
}

//we assume that iDegree > 0
int main() {
 struct polynom p = { 
 3,
 (float []){1.f, 2.f, 0.5f}
 };
 
 printPolynome(p);

 struct polynom* p2 = malloc();
 
 printf("constant: %f", norm(&p, p2));
 
 printPolynome(*p2);

 for (int i=0; i < 1000; ++i) {
  /*
   Not using assert because it actually breaks the entire
   program, even though there might be tests left to run
  */
  //checking the normalizing constant
  assert(norm(expected[i] == actual_constant));
 }
 return 0;
}
