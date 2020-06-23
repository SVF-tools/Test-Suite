/*
 * Quake benchmark
 * Loukas Kallivokas and David O'Hallaron
 * Carnegie Mellon University, November, 1997
 * http://www.cs.umd.edu/~hollings/cs714/f15/quake.c
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "aliascheck.h"
#define AMAX_NAME  128

#ifndef PI
#  define PI 3.141592653589793238
#endif

/*--------------------------------------------------------------------------*/ 

double ***disp, ***K;
double **v;
int *ARCHmatrixindex, *Acol;


int main(int argc, char **argv)
{
  int i, j, k, disptplus, pp;
  int Anext, Alast, col;
  double sum0, sum1, sum2, sum3;


	disp = (double ***) malloc( 3*sizeof(double**));
        for(disptplus = 0; disptplus < 3; disptplus++){
           disp[disptplus] = (double **) malloc( 5000*sizeof(double*));
           for(i = 0; i < 5000; i++)
              disp[disptplus][i] = (double *) malloc( 4*sizeof(double));
        }
	if(disp[2][4999] == NULL) 
	{printf("null pointer 2!\n"); return 0;}

	K = (double ***) malloc( 3*sizeof(double**));
        for(disptplus = 0; disptplus < 3; disptplus++){
           K[disptplus] = (double **) malloc( 5000*sizeof(double*));
           for(i = 0; i < 5000; i++)
              K[disptplus][i] = (double *) malloc( 4*sizeof(double));
        }
	if(K[2][4999] == NULL) 
	{printf("null pointer 2!\n"); return 0;}

        v = (double **) malloc( 5000*sizeof(double*));
        for(i = 0; i < 5000; i++)
           v[i] = (double *) malloc( 4*sizeof(double));
	if(v[4999] == NULL) 
	{printf("null pointer 2!\n"); return 0;}

        ARCHmatrixindex = (int *) malloc( 5001*sizeof(int));
	if(ARCHmatrixindex == NULL) 
	{printf("null pointer 2!\n"); return 0;}

        Acol = (int *) malloc( 4*sizeof(int));
	if(Acol == NULL) 
	{printf("null pointer 2!\n"); return 0;}

  for(disptplus = 0; disptplus < 3; disptplus++)
    for (i = 0; i < 5000; i++)
      for (j = 0; j < 4; j++){
        disp[disptplus][i][j] = 0.0;
        K[disptplus][i][j] = 1.1*i + j;
  }

  for (i = 0; i < 5000; i++)
    for (j = 0; j < 4; j++)
      v[i][j] = 1.1*i + j;

  for(i = 0; i < 5001; i=i+3){
    ARCHmatrixindex[i] = 0;
    ARCHmatrixindex[i+1] = 1;
    ARCHmatrixindex[i+2] = 2;
  }
       
  for(i = 0; i < 4; i++){
    Acol[i] = 300*i;
  }


for(pp = 0; pp < 100000; pp++){
  for (i = 0; i < 5000; i++) {

    Anext = ARCHmatrixindex[i];
    Alast = ARCHmatrixindex[i + 1];


    while (Anext < Alast) {
      col = Acol[Anext];


      disp[1][col][0] += K[Anext][0][0]*v[i][0] + K[Anext][1][0]*v[i][1] + K[Anext][2][0]*v[i][2];
      disp[1][col][1] += K[Anext][0][1]*v[i][0] + K[Anext][1][1]*v[i][1] + K[Anext][2][1]*v[i][2];
      disp[1][col][2] += K[Anext][0][2]*v[i][0] + K[Anext][1][2]*v[i][1] + K[Anext][2][2]*v[i][2];
      disp[1][col][3] += K[Anext][0][3]*v[i][0] + K[Anext][1][3]*v[i][1] + K[Anext][2][3]*v[i][2];
      NOALIAS(disp,K);
      NOALIAS(disp,v);
      NOALIAS(disp[1],K[Anext]);
      NOALIAS(disp[1],v[i]);
      NOALIAS(disp[1][col],v[i]);
      Anext++;
    }


  }
}

  double rst = disp[1][4999][2];

        for(disptplus = 0; disptplus < 3; disptplus++){
           for(i = 0; i < 5000; i++)
              free(disp[disptplus][i]);
           free(disp[disptplus]);
        }
        free(disp);

        for(disptplus = 0; disptplus < 3; disptplus++){
           for(i = 0; i < 5000; i++)
              free(K[disptplus][i]);
           free(K[disptplus]);
        }
        free(K);

        for(i = 0; i < 5000; i++)
              free(v[i]);
        free(v);

        free(ARCHmatrixindex);
        free(Acol);



  if(rst > 5.5)
    return 0;
  else
    return 1;

}
/* --------------------------------------------------------------------------*/




