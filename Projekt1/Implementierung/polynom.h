struct polynom {
 int iDegree;
 float* p_fCoefficients ;
};

/* Polynomial example :
struct polynom A = {
iDegree = 2;
float p_fCoefficients = [1, 2, 0.5];
};

equivalent to : 1 + 2*x + 0.5*x^2
*/

/*
 returns the normalizing constant c and
 calculates the coefficients for the output polynome
*/
float norm(struct polynom *input, struct polynom *output);
