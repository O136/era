#include <stdio.h>
#include "polynom.h"

//returns the normalisation constant c
float norm(struct polynom *input, struct polynom *output) {

 int degree = input->iDegree;
 output->iDegree = degree;

 float a_N = input->p_fCoefficients[degree-1];

 for (int i=0; i < degree; ++i) {
        output->p_fCoefficients[i] = a_N / input->p_fCoefficients[i];
 }

 return a_N; //c = a_N
}

