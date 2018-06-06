#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "polynom.h"
#include "utils.h"

//10 test cases
//struct polynom{iDegree, p_fCoefficients}

//NOTE: the normalisation constant for polynomes is checked
//in the test_all procedure

struct polynom input[] =  {
	// impossible & nonsense case
	{-1, (float[]){0.f}},

	//10
	{0, (float[]){10.f}},

	//1 + 1x
	{1, (float[]){1.f, 1.f}},

	//0 + 2x + 3x^2
	{2, (float[]){0.f, 2.f, 3.f}},

	//1 + 1x + 4x^2
	{2, (float[]){1.f, 1.f, 4.f}},

  //3 + 0x + 6x^2
	{2, (float[]){3.f, 0.f, 6.f}},

  //-1 + 2x
	{1, (float[]){-1.f, 2.f}},

  //-8 + (-2)x + (-4)x^2
	{2, (float[]){-8.f, -2.f, -4.f}},

  //2 + (-6)x + 4x^2 + 8x^3 + 16x^4
	{4, (float[]){2.f, -6.f, 4.f, 8.f, 16.f}},

  //1.5 + 3x + 4.5x^2 + 1x^3 + 0x^4 + 3x^5
	{5, (float[]){1.5f, 3.f, 4.5f, 1.f, 0.f, 3.f}},
};

struct polynom expectedOutput[] =  {
	//-1 is not a possible degree
  {-1, (float[]){}},

	//1
	{0, (float[]){1.f}},

  //1 + x
	{1, (float[]){1.f, 1.f}},

  //0 + 2/3 * x + 1x^2
	{2, (float[]){0.f, 2.f/3.f, 1.f}},

  //0.25 + 0.25x + 1x^2
	{2, (float[]){0.25f, 0.25f, 1.f}},

  //0.5 + 0x + 1x^2
	{2, (float[]){0.5f, 0.f, 1.f}},

  //-0.5 + 1x
	{1, (float[]){-0.5f, 1.f}},

  //2 + 0.5x + 1x^2
	{2, (float[]){2.f, 0.5f, 1.f}},

  //2/16 - 6/16x + 1/4x^2 + 0.5x^3 + 1x^4
	{4, (float[]){2.f/16.f, -6.f/16.f, 4.f/16.f, 0.5f, 1.f}},

  //1.5/3 + 3/3x + 4.5/3x^2 +1/3x^3 + 0/3x^4 + 3/3x^5
	{5, (float[]){1.5f/3.f, 1.f, 4.5f/3.f, 1.f/3.f, 0.f, 1.f}},

};

//checks whether norm is within the relative error bounds
bool isOkNorm(float expectedNorm, float gotNorm) {
  return fabs(expectedNorm - gotNorm) < REL_ERROR;
}

//checks whether the degrees of the two polynomials is the same
bool isOkDeg(struct polynom expected, struct polynom got) {
  return expected.iDegree == got.iDegree;
}

//checks whether the coefficients of the computed polynomial
//is within the error bounds with respect to the expected polynomial
bool isOkCoeff(struct polynom expected, struct polynom got) {
  for(int i=0; i<=expected.iDegree;++i) {
    if (fabs(expected.p_fCoefficients[i] - got.p_fCoefficients[i]) > REL_ERROR)
      return false;
  }
  return true;
}


void test_all(void) {
  int passed = 0;
  const int TOTAL_CASES = sizeof(input) / sizeof(input[0]);

  for(int i=0; i<TOTAL_CASES; ++i) {
    //in order to avoid boilerplate code
    //output=input[i] will create automatically the
    //p_fCoeff array for output with the needed size
    struct polynom output = input[i];

    int deg = expectedOutput[i].iDegree;
    float expectedNorm = input[i].p_fCoefficients[deg]; //a_N = c
    float outputNorm = norm(&input[i], &output);

    if(!isOkDeg(expectedOutput[i], output) ||
       !isOkNorm(expectedNorm, outputNorm) ||
       !isOkCoeff(expectedOutput[i], output)) {
      printf("\n\nTest #%i Failed:", i+1);
    }
    else {
      printf("\n\nTest #%i passed", i+1);
      ++passed;
    }

    printf("\n\toutput degree:");
    printDeg(input[i]);
    printf("\n\texpected degree:");
    printDeg(expectedOutput[i]);

    printf("\n\t*************************");

    printf("\n\toutput coefficients");
    printf("\n\t");
    printCoeff(output);
    printf("\n\texpected coefficients");
    printf("\n\t");
    printCoeff(expectedOutput[i]);

    printf("\n\t*************************");

    printf("\n\toutput norm %f", outputNorm);
    printf("\n\texpected norm %f", expectedNorm);
  }

  printf("\n\nTotal passed tests %i/%i\n", passed, TOTAL_CASES);
}

int main(void) {
  test_all();
 return 0;
}
