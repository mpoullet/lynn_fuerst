#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float   fX[] = {2, 1, -2, 3, -1, -1, 1}, fAR[7], fAI[7];

void main (void)
    {
    /*
     *********  PROGRAM NO.7   DISCRETE-TIME FOURIER  **********
     *********  SERIES FOR SIGNAL WITH 7 SAMPLE VALUES  ********
     */
    int    iCount, iCount2;

    _clearscreen  (_GCLEARSCREEN);
    printf ("PROGRAM 7: Discrete Fourier Series\n");
    printf ("for real signal with 7 sample values\n\n");

    for (iCount2 = 1; iCount2 < 8; iCount2++)
      for (iCount = 1; iCount < 8; iCount++)
        {
        fAR[iCount2-1] = fAR[iCount2-1] + (1.0/7.0) *
              fX[iCount-1] * cos (2.0 * 3.141593 *
              (float)(iCount2-1) * (float)(iCount-1) / 7.0);
        fAI[iCount2-1] = fAI[iCount2-1] - (1.0/7.0) *
              fX[iCount-1] * sin (2.0 * 3.141593 *
              (float)(iCount2-1) * (float)(iCount-1) / 7.0);
        }

    for (iCount2 = 0; iCount2 < 7; iCount2++)
        printf ("%d     % f, % f\n", iCount2,
        fAR[iCount2], fAI[iCount2]);

    /*
     ***********************************************************
     */
    }
