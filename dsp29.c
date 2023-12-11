/************  PROGRAM NO.29     MATCHED FILTERING  ************/
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include "graph3.h"

double round(float X);

void main(void)
	{
  	double X[421];
  	double Y[421];
  	double H[101];
  	double S[101];
  	int N,K;
  	double NV,SUM,MX,MY;

  	for (N=1; N<=420; N++)
  		{
    	X[N]=0; Y[N]=0;
  		}
		
  	randomize();
  	graphmode();
	/********************  DEFINE INPUT SIGNAL  ********************/
  	S[1]=1.0;S[2]=0.575;
  	for (N=3; N<=60; N++)
    	S[N]=1.575*S[N-1]-0.9025*S[N-2];

	/********  LOAD TWO VERSIONS OF SIGNAL INTO INPUT ARRAY  *******/
  	for (N=1; N<=60; N++)
  		{
    	X[N+110]=S[N];
    	X[N+280]=X[N+280]+S[N];
  		}

	/********  ADD REQUIRED AMOUNT OF WHITE GAUSSIAN NOISE  ********/
  	printf("ENTER NOISE VARIANCE: ");
  	scanf("%lf",&NV);
  	for (N=1; N<=420; N++)
  		{
   		SUM=0;
    	for (K=1; K<=12; K++)
      		SUM=SUM+(random(10000)/(float)10000)-0.5;
    	X[N]=X[N]+NV*SUM;
  		}

	/******************  DEFINE IMPULSE RESPONSE  ******************/
  	for (N=1; N<=60; N++)
    	H[N]=S[61-N];
	
	/************  CONVOLVE INPUT AND IMPULSE RESPONSE  ************/
  	for (N=101; N<=420; N++)
    for (K=1; K<=100; K++)
      	Y[N]=Y[N]+H[K]*X[N-K];

	/******  NORMALISE ARRAYS TO MAX VALUE OF UNITY FOR PLOT  ******/
  	MX=0;MY=0;
  	for (N=101; N<=420; N++)
  		{
    	if (fabs(X[N])>MX)
      	MX=fabs(X[N]);
    	if (fabs(Y[N])>MY)
      	MY=fabs(Y[N]);
  		}

  	for (N=1; N<=420; N++)
  		{
	    X[N]=X[N]/MX;
 	   Y[N]=Y[N]/MY;
 		}

	/***********  PLOT INPUT AND OUTPUT SIGNAL ARRAYS  ************/
  	cleardevice();
  	for (N=101; N<=420; N++)
    	draw(N-100,50,N-100,round(50-X[N]*22),1);

  	for (N=101; N<=420; N++)
    	draw(N-100,150,N-100,round(150-Y[N]*22),1);

	getch();
  	closegraph();
	}
	/***************************************************************/

	double round(float X) 
	{
  	if (fmod(X,1)>= 0.5 )
   		 return ceil(X);
  	else
    	return floor(X);
	}