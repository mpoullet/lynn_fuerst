#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEEDIM    200
#define WDIM      320

float fSEE[SEEDIM + 1], fW[WDIM + 1];

void main (void)
    {
    /*
     ********************** PROGRAM NO.16 **********************
     **** SPECTRAL PROPERTIES OF VON HANN & HAMMING WINDOWS ****
     */
    int    iCount, iCount2, iX, iM;
    float  fA, fB, fC, fFREQ, fPEAK, fDB;

    _clearscreen  (_GCLEARSCREEN);

    printf ("PROGRAM 16: Spectral properties of von Hann ");
    printf ("& Hamming windows\n\n");

    printf ("Select window type: 1 = von Hann, 2 = Hamming :");
    scanf ("%d", &iX);

    printf ("\n  Enter (integer) value of M :");
    scanf ("%d", &iM);

    /*
     **** LOAD ONE HALF OF WINDOW (EXCLUDING CENTRAL VALUE) ****
     *******************INTO ARRAY fSEE ************************
     */
    if (iX == 1)
        {fA = 0.5; fB = 0.5; fC = (float)iM + 1.0;}
    else
        {fA = 0.54; fB = 0.46; fC = (float)iM;}

    for (iCount = 1; iCount <= iM; iCount++)
        fSEE[iCount] =
            fA + fB * cos ((float)iCount * 3.141593 / fC);

    _setvideomode( _MRES16COLOR );

    /*
     *************** DRAW RECTANGULAR GRID FOR PLOT ************
     */
    for (iCount = 0; iCount <= 5; iCount++)
        {
        _moveto (0, 30 + 20 * iCount);
        _lineto (320, 30 + 20 * iCount);
        _moveto (64 * iCount, 30);
        _lineto (64 * iCount, 130);
        }

    _moveto (319, 30);
    _lineto (319, 130);

    /*
     *********************** ESTIMATE SPECTRUM *****************
     */
    for (iCount = 1; iCount <= 320; iCount++)
        {
        fFREQ = 3.141593 * (float)(iCount - 1) / 320.0;
        fW[iCount] = 1.0;
        for (iCount2 = 1; iCount2 <= iM; iCount2++)
            fW[iCount] += 2.0 * fSEE[iCount2] *
                         cos ((float)iCount2 * fFREQ);

    /*
     *** NORMALISE TO PEAK VALUE, CONVERT TO DECIBELS & PLOT ***
     */
        if (iCount == 1)
            fPEAK = fW[iCount];

        fW[iCount] /= fPEAK;
        fDB = 20.0 * (float) log (fabs (fW[iCount])) * 0.4343;

        if (fDB < -50.0)
            fDB = -50.0;

        _moveto (iCount, 130);
        _lineto (iCount, (int)(30 - 2.0 * fDB + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );  

    /*
     ***********************************************************
     */
    }
