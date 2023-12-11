/*******  PROGRAM NO.27  ESTIMATES OF MEAN AND VARIANCE  *******/
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
    double X[321];
    double M[17];
    double V[17];
    int J,K,N;
    double A,B,C,RM,RV,Z;

    randomize();
    graphmode();
    for (N=1; N<=16; N++)
        {
        M[N]=0; V[N]=0;
        }
		
    /*******  FORM 320 VALUES OF GAUSSIAN SEQUENCE, AND PLOT  ******/
    for (N=1; N<=320; N++)
        {
        C=0;
        for (K=1; K<=12; K++)
            C=C+(random(10000)/(float)10000)-0.5;
        X[N]=C;
        draw(N,50,N,round(50-X[N]*10),1);
        }
		
    /************  ESTIMATE SAMPLE MEANS AND VARIANCES  ************/
    for (J=1; J<=16; J++)
        {
        for (K=1; K<=20; K++)
            {
            N=K+20*(J-1)-1;
            M[J]=M[J]+X[N]/20;
            V[J]=V[J]+X[N]*X[N]/20;
            }
        draw(N,100,N,round(100-M[J]*50),1);
        draw(N,160,N,round(160-V[J]*20),1);
        }
		
	printf("PRESS ANY KEY TO CONTINUE ");
    getch();
    cleardevice();
    /*************  ESTIMATE RUNNING MEAN AND VARIANCE  ************/
    A=0;B=0;
    for (N=1; N<=320; N++)
        {
        A=A+X[N];RM=A/N;B=B+X[N]*X[N];RV=B/N;
        draw(N,80,N,round(80-RM*50),1);
        draw(N,150,N,round(150-RV*20),1);
        }
		
  	getch();
  	closegraph();
		}
	/***************************************************************/

	double round(float X) {
	if (fmod(X,1)>= 0.5 )
    	return ceil(X);
  	else
  	  return floor(X);
	}