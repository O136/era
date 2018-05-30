#ifndef POLYNOM_H
#define POLYNOM_H

//used to compare floats
#define REL_ERROR 0.0001

/* Polynomial example :
   struct polynom A = {
   iDegree = 2;
   float p_fCoefficients = [1, 2, 0.5];
   };

   equivalent to : 1 + 2*x + 0.5*x^2
*/

struct polynom {
 int iDegree;
 float* p_fCoefficients;
};


/*
 returns the normalizing constant c,
 calculates and writes the coefficients
 for the output polynome
*/
extern float norm(struct polynom *input, struct polynom *output) asm("norm");

#endif
