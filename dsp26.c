/*********  PROGRAM NO.26   PROBABILITY MASS FUNCTIONS  ********/
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include "graph3.h"


double round(float X);

void main(void) {
    double X[301];
    double Y[301];
    int K,N,B,D;
    double C;
    /********************  UNIFORM DISTRIBUTION  *******************/
    for (K=0; K<=300; K++)
        {
        X[K]=0; Y[K]=0;
        }
		
    randomize();
    graphmode();
    
	for (K=1; K<=3000; K++)
        {
        B=(random(10000)/(float)10000)*300;
        X[B]=X[B]+1;
        draw(B,50,B,round(50-X[B]),1);
        }
		
	/************  GAUSSIAN DISTRIBUTION (APPROXIMATE)  ************/
    for (K=1; K<=3000; K++)
        {
        C=0;
        for (N=1; N<=30; N++)
            C=C+(random(10000)/(float)10000);
        D=(int)(C*10);
        Y[D]=Y[D]+1;
        draw(D,180,D,round(180-Y[D]),1);
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
