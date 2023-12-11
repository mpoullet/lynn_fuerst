#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define XDIM     64
#define ARDIM    64
#define AIDIM    64
#define MAGDIM   64
#define PHASEDIM 64

float   fX[XDIM + 1], fAR[ARDIM + 1], fAI[AIDIM + 1],
        fMAG[MAGDIM + 1], fPHASE[PHASEDIM + 1];

void main (void)
    {
    /*
     *****  PROGRAM NO.8   DISCRETE-TIME FOURIER SERIES ******
     *** 64 REAL SAMPLE VALUES, SPECTRAL MAGNITUDE & PHASE  **
     */
    int    iCount, iCount2;
    float  fMax1, fMax2, fMax3, fB;

    _clearscreen  (_GCLEARSCREEN);

    printf ("PROGRAM 8: Discrete Fourier Series\n");
    printf ("64 real sample values, spectral magnitude ");
    printf ("& phase\n\n");

    printf ("Press any key to start...\n");
    getch();

    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        fB = 2.0 * 3.141593 * (float)(iCount - 1);
        fX[iCount] = sin (fB / 64.0) + cos (fB / 16.0) +
               0.6 * cos (fB / 8.0) + 0.5 * sin (fB / 4.0);
        }

    for (iCount = 1; iCount <= XDIM; iCount++)
        for (iCount2 = 1; iCount2 <= XDIM; iCount2++)
            {
            fAR[iCount] = fAR[iCount] + (1.0 / 64.0) *
                    fX[iCount2] * cos (2.0 * 3.141593 *
                    (float)(iCount - 1) * (float)(iCount2 - 1) / 64.0);
            fAI[iCount] = fAI[iCount] - (1.0 / 64.0) *
                    fX[iCount2] * sin (2.0 * 3.141593 *
                    (float)(iCount - 1) * (float)(iCount2 - 1) / 64.0);
            }

    /*
     ******* CONVERT TO SPECTRAL MAGNITUDE AND PHASE ***********
     */
    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        if (fabs (fAI[iCount]) < 0.001)
            fAI[iCount] = 0.0;
        if (fabs (fAR[iCount]) < 0.00001)
            fAR[iCount] = 0.00001;
        fMAG[iCount] = sqrt (pow (fAR[iCount], 2.0) +
                        pow (fAI[iCount], 2.0));
        fPHASE[iCount] = atan (fAI[iCount] / fAR[iCount]);
        }

    /*
     ********** NORMALISE TO MAXIMUM OF UNITY FOR PLOT *********
     */
    fMax1 = fMax2 = fMax3 = 0.001;

    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        if (fabs (fX[iCount]) > fMax1)
            fMax1 = fabs (fX[iCount]);
        if (fabs (fMAG[iCount]) > fMax2)
             fMax2 = fabs (fMAG[iCount]);
        if (fabs (fPHASE[iCount]) > fMax3)
            fMax3 = fabs (fPHASE[iCount]);
        }

    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        fX[iCount] /= fMax1;
        fMAG[iCount] /= fMax2;
        fPHASE[iCount] /= fMax3;
        }

    /*
     ******** PLOT SIGNAL, SPECTRAL MAGNITUDE AND PHASE ********
     */
    _setvideomode( _MRES16COLOR );

    for (iCount = 1; iCount <= XDIM; iCount++)
      {
      _moveto (5*(iCount - 1), 50);
      _lineto (5*(iCount - 1), (int)(50 - fX[iCount] * 25.0 + 0.5));
      _moveto (5*(iCount - 1), 120);
      _lineto (5*(iCount - 1), (int)(120 - fMAG[iCount] * 30.0 + 0.5));
      _moveto (5*(iCount - 1), 160);
      _lineto (5*(iCount - 1), (int)(160 - fPHASE[iCount] * 20.0 + 0.5));
      }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
