#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM     64

float   fX[DIM + 1], fXXR[DIM + 1], fXXI[DIM + 1],
        fMAG[DIM + 1], fPHASE[DIM + 1], fC[DIM + 1], fS[DIM + 1];

/*
*** WHEN COMPARING WITH THE TEXT, NOTE THAT IN THE C PROGRAMS **
******* FLOATING-POINT VARIABLES ARE PREFIXED WITH AN f, *******
************** INTEGER VARIABLES WITH AN i *********************
*/

void main (void)
    {
    /*
     ***** PROGRAM NO. 23  DISCRETE FOURIER TRANSFORM (DFT) ****
     ******* BY DIRECT CALCULATION, AND WITH TABLE LOOKUP ******
     ****** REAL SIGNAL, N=64, SPECTRAL MAGNITUDE & PHASE ******
     */
    int    iCount, iCount2, iP, iI, iL;
    float  fMax1, fMax2, fMax3, fB, fW0;

    _clearscreen  (_GCLEARSCREEN);
    printf ("PROGRAM 23: Discrete Fourier Transform (DFT)\n");
    printf ("by direct calculation, and with table lookup.\n");
    printf ("Real signal, N=64, spectral magnitude & phase.\n");
    printf ("Press any key to start first DFT ...");
    getch();
    /*
     ******************** GENERATE SIGNAL **********************
     */
    for (iCount = 1; iCount <= DIM; iCount++)
        {
        fB = 2.0 * 3.141593 * (iCount - 1);
        fX[iCount] = sin (fB / 64.0) + cos (fB / 16.0) +
                     0.6 * cos (fB / 8.0) + 0.5 * sin (fB / 4.0);
        }

    for (iCount = 1; iCount <= DIM; iCount++)
        for (iCount2 = 1; iCount2 <= DIM; iCount2++)
            {
            fXXR[iCount] = fXXR[iCount] + fX[iCount2] *
                          cos (2.0 * 3.141593 * (float)(iCount - 1) *
                          (float)(iCount2 - 1) / 64.0);
            fXXI[iCount] = fXXI[iCount] - fX[iCount2] *
                          sin (2.0 * 3.141593 * (float)(iCount - 1) *
                          (float)(iCount2 - 1) / 64.0);
            }

    for (iP = 0; iP < 2; iP++)
        {
        _setvideomode( _MRES16COLOR );

        if (iP == 0)
           printf ("\n\nPress any key to start second DFT...");

        if (iP)
            {
            for (iCount = 1; iCount <= DIM; iCount++)
                {
                fXXR[iCount] = 0.0;
                fXXI[iCount] = 0.0;
                }

            /******** FORM TABLE LOOKUP ***********************/

            fW0 = 2.0 * 3.141593 / 64.0;

            for (iCount = 1; iCount <= DIM; iCount++)
                {
                fC[iCount] = cos (fW0 * ((float) (iCount - 1)));
                fS[iCount] = sin (fW0 * ((float) (iCount - 1)));
                }

            for (iCount = 1; iCount <= DIM; iCount++)
                for (iCount2 = 1; iCount2 <= DIM; iCount2++)
                    {
                    iI = (iCount -1) * (iCount2 - 1);
                    iL = iI % 64;

                    fXXR[iCount] = fXXR[iCount] + fX[iCount2] *
                        fC[iL + 1];
                    fXXI[iCount] = fXXI[iCount] - fX[iCount2] *
                        fS[iL + 1];
                    }

            }

        /*
         ********* CONVERT TO SPECTRAL MAGNITUDE AND PHASE *****
         */
        for (iCount = 1; iCount <= DIM; iCount++)
            {
            if (fabs (fXXI[iCount]) < 0.001)
                fXXI[iCount] = 0.0;
            if (fabs (fXXR[iCount]) < 0.00001)
                fXXR[iCount] = 0.00001;
            fMAG[iCount] = sqrt (pow (fXXR[iCount], 2.0) +
                            pow (fXXI[iCount], 2.0));
            fPHASE[iCount] = atan (fXXI[iCount] / fXXR[iCount]);
            }

        /*
         ******* NORMALISE TO MAXIMUM OF UNITY FOR PLOT ********
         */
        fMax1 = fMax2 = fMax3 = 0.001;

        for (iCount = 1; iCount <= DIM; iCount++)
            {
            if (fabs (fX[iCount]) > fMax1)
                fMax1 = fabs (fX[iCount]);
            if (fabs (fMAG[iCount]) > fMax2)
                 fMax2 = fabs (fMAG[iCount]);
            if (fabs (fPHASE[iCount]) > fMax3)
                fMax3 = fabs (fPHASE[iCount]);
            }

        for (iCount = 1; iCount <= DIM; iCount++)
            {
            fX[iCount] /= fMax1;
            fMAG[iCount] /= fMax2;
            fPHASE[iCount] /= fMax3;
            }

        /*
         ********PLOT SIGNAL, SPECTRAL MAGNITUDE AND PHASE *****
         */
        for (iCount = 1; iCount <= DIM; iCount++)
            {
            _moveto (5 * (iCount - 1), 50);
            _lineto (5 * (iCount - 1), (int)(50 - fX[iCount] *
                25.0 + 0.5));
            _moveto (5 * (iCount - 1), 120);
            _lineto (5 * (iCount - 1), (int)(120 - fMAG[iCount] *
                30.0 + 0.5));
            _moveto (5 * (iCount - 1), 160);
            _lineto (5 * (iCount - 1), (int)(160 - fPHASE[iCount] *
                20.0 + 0.5));
            }

        getch();
        _setvideomode( _DEFAULTMODE );
        }

    /*
     ***********************************************************
     */
    }
