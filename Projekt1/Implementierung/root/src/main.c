#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "polynom.h"
#include "utils.h"

struct polynom* readInput() {
  struct polynom* p = malloc(sizeof *p);

  printf("Degree: ");
  scanf("%d", &p->iDegree);

  int i = 0;
  printf("Coefficients(separated by space): ");

  p->p_fCoefficients  = (float*)malloc((p->iDegree +1)*sizeof(float));
  while (i <= p->iDegree && scanf("%f", &p->p_fCoefficients[i++]) == 1);

  return p;
}

void printExample(){
  printf("EXAMPLE\n\n");
  printf("\tDegree: 2");
  printf("\n\tCoefficents: 1 2 2");
  printf("\n\tInput polynomial: 1 + 2x + 2x^2\n");
  printf("\n\nNormalizing constant c = 2, multiplies the output polynomial\n\n");
  printf("\tDegree: 2");
  printf("\n\tCoefficents: 0.5 1 1");
  printf("\n\tOutput polynomial: 0.5x + x + x^2\n");
}

int main() {
  printExample();
  char choice;

  do{
    printf("\n\n\n");
    printf("Enter X for a polynomial or any other key to exit\n\n");
    scanf(" %c", &choice);
    printf("\n\n");
    choice = toupper(choice);

    if(choice == 'X') {
      struct polynom* in = readInput();

      printf("\nInput polynomial: ");
      printf("\n\tDegree: ");
      printDeg(*in);
      printf("\n\tCoefficients: ");
      printCoeff(*in);


      struct polynom* out  = malloc(sizeof *out);
      out->p_fCoefficients = (float*)malloc((in->iDegree + 1)*sizeof(float));
      float normc = norm(in, out);
      if(fabs(normc) < REL_ERROR) {
        printf("\nInvalid polynomial!\nMake sure the last coefficient > 0,and degree >= 0\n");
        break;
      }

      printf("\n\nnormalizing constant %f\n", normc);

      printf("\nOutput polynomial: ");
      printf("\n\tDegree: ");
      printDeg(*out);
      printf("\n\tCoefficients: ");
      printCoeff(*out);
      fflush(stdout);
      free(in->p_fCoefficients);
      free(in);

      free(out->p_fCoefficients);
      free(out);
      printf("\n");
     }

  }while (choice == 'X');

  return 0;
}
