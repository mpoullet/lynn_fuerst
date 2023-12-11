/*******  PROGRAM N0.28     PROCESSING RANDOM SEQUENCES  *******/
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
  	double GN[1201];
  	double X[1201];
  	double Y[1201];
  	double H[11];
  	double J[20];
  	double XACF[102];
  	double YACF[102];
  	double EST[102];
  	int N,K,L,M,P,Q;
  	double C,SUM,MY,A,B,Z,MYE,VARE;

  	randomize();
  	graphmode();
  	for (N=1; N<=1200; N++)
    	Y[N]=0;
  	for (N=1; N<=19; N++)
    	J[N]=0;
  	for (N=1; N<=101; N++)
    	EST[N]=0;
	/************  ENTER PROCESSOR'S IMPULSE RESPONSE  *************/
  	H[1]=1;H[2]=2;H[3]=1;H[4]=-1;H[5]=-2;
  	H[6]=-1;H[7]=1;H[8]=2;H[9]=1;H[10]=0;
	/*******  FORM GAUSSIAN NOISE, ZERO MEAN, UNIT VARIANCE  *******/
  	cleardevice();
  	for (N=1; N<=1200; N++)
  		{
    	C=0;
    	for (K=1; K<=12; K++)
      	C=C+(random(10000)/(float)10000)-0.5;
    	GN[N]=C;
  		}

	/******** LOW-PASS FILTER & ADD UNIT MEAN TO FORM X[N]  ********/
  	for (N=4; N<=1200; N++)
    	X[N]=(GN[N]+GN[N-1]+GN[N-2]+GN[N-3])*0.5+1;
	
	/*************  PLOT 320 VALUES OF X[N] ON SCREEN  *************/
  	for (N=1; N<=320; N++)
    	draw(N,50,N,round(50-X[N+100]*6),1);
	
	/*****************  DEFINE AND PLOT INPUT ACF  *****************/
  	for (K=1; K<=101; K++)
    	XACF[K]=1;
  	XACF[48]=1.25;XACF[49]=1.5;XACF[50]=1.75;XACF[51]=2;
  	XACF[52]=XACF[50];XACF[53]=XACF[49];XACF[54]=XACF[48];
  	for (N=1; N<=83; N++)
    	draw(N,180,N,round(180-XACF[N+9]*25),1);
	
	/**********  FIND ACF OF PROCESSOR'S IMPULSE RESPONSE **********/
  	for (K=1; K<=10; K++)
    for (L=1; L<=K; L++)
      	J[K]=J[K]+H[L]*H[10-K+L];
  	for (K=11; K<=19; K++)
    	J[K]=J[20-K];
	
	/***************  PREDICT MEAN VALUE OF OUTPUT  ****************/
  	SUM=0;
  	for (K=1; K<=10; K++)
    	SUM=SUM+H[K];
  	MY=1*SUM;
	
	/***************  PREDICT AND PLOT OUTPUT ACF  *****************/
  	for (M=10; M<=92; M++)
  		{
    	SUM=0;
    	for (K=1; K<=19; K++)
      		SUM=SUM+XACF[M-10+K]*J[K];
    	YACF[M]=SUM;
  		}
		
  	for (N=1; N<=83; N++)
    	draw(N+120,180,N+120,round(180-YACF[N+9]*50/YACF[51]),1);
	
	/************  CONVOLVE X[N] AND H[N] TO FORM Y[N]  ************/
  	for (N=15; N<=1200; N++)
    	for (K=1; K<=10; K++)
     		 Y[N]=Y[N]+H[K]*X[N-K];
	
	/*************  PLOT 320 VALUES OF Y[N] ON SCREEN  *************/
  	A=9/sqrt(YACF[51]);
  	for (N=1; N<=320; N++)
    	draw(N,100,N,round(100-Y[N+100]*A),1);
	
	/***************  ESTIMATE AND PLOT OUTPUT ACF  ****************/
  	B=20*YACF[51];
  	for (K=1; K<=100; K++)
    	{
		for (M=10; M<=92; M++)
    		{
      		P=M-51;
      		for (L=1; L<=10; L++)
      			{
				Q=10*(K-1)+L+60;
				EST[M]=EST[M]+Y[Q]*Y[Q+P];
      			}
      		draw(M+227,180,M+227,round(180-EST[M]/B),1);
    		}
  
  		printf("PRESS ANY KEY TO CONTINUE\n");
  		getch();
  		cleardevice();
	
	/******  PREDICT AND ESTIMATE OUTPUT MEAN AND VARIANCE   ******/
  	SUM=0;
  	for (N=15; N<=1200; N++)
    	SUM=SUM+Y[N];
  	MYE=SUM/1185;
  	printf("OUTPUT MEAN (PREDICTED)=%f\n", MY);
  	printf("OUTPUT MEAN (ESTIMATED)=%f\n",MYE);
  	SUM=0;
  	for (N=15; N<=1200; N++)
    	SUM=SUM+(Y[N]-MY)*(Y[N]-MY);
  	VARE=SUM/1185;
  	printf("OUTPUT VARIANCE (PREDICTED)=%f\n",YACF[51]-MY*MY);
  	printf("OUTPUT VARIANCE (ESTIMATED)=%f\n",VARE);
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