#include <stdio.h>
#include "polynom.h"
#include "utils.h"

void printDeg(struct polynom p) {
  printf("%i", p.iDegree);
}

void printCoeff(struct polynom p) {
  for(int i=0; i<=p.iDegree; ++i) {
    printf("%f ", p.p_fCoefficients[i]);
  }
}
