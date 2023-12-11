#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

#define XDIM 100

float   fX[XDIM + 1], fB = 0.0, fW = 0.0;

void main (void)
    {
    /*
     ***  PROGRAM NO.2  SAMPLED EXPONENTIALS AND SINUSOIDS  ****
     */
    int    iCount;

    _clearscreen  (_GCLEARSCREEN);
    printf ("PROGRAM 2: Sampled exponentials and sinusoids\n");

    printf ("Enter value of Beta-Zero :");
    scanf ("%f", &fB);

    printf ("Enter value of Omega :");
    scanf ("%f", &fW);

    for (iCount = 1; iCount <= XDIM; iCount++)
        fX[iCount] = exp (fB * (float)iCount) *
                     cos (fW * (float)iCount);

    /*
     ************** DRAW AXES, THEN SIGNAL SAMPLES *************
     */
    _setvideomode( _MRES16COLOR );

    _moveto (1, 100);   _lineto (300, 100);

    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        _moveto (3 * iCount, 100);
        _lineto (3 * iCount, (int)(100.0 - fX[iCount] * 30.0 + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
