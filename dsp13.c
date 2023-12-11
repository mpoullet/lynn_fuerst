#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HDIM     200

float   fH[HDIM + 1];

void main (void)
    {
    /*
     ******************* PROGRAM NO.13 *************************
     ** NONRECURSIVE FILTER DESIGN BY FOURIER TRANSFORM METHOD *
     ******* IMPULSE RESPONSE TRUNCATED TO (2M+1) TERMS ********
     */
    int    iCount, iCount2, iM;
    float  fW, fW0, fW1, fA, fB, fH0, fHF;

    _clearscreen (_GCLEARSCREEN);

    printf ("PROGRAM 13: ");
    printf ("Nonrecursive filter design by Fourier\n");
    printf ("Transform method. Impulse response ");
    printf ("truncated to\n(2M+1) terms\n\n");

    printf ("Enter center-frequency (in degrees) :");
    scanf ("%f", &fA);
    printf ("Enter filter bandwidth (in degrees) :");
    scanf ("%f", &fB);
    printf ("Enter (integer) value of M :");
    scanf ("%d", &iM);

    fW0 = fA * 3.141593 / 180.0;
    fW1 = fB * 0.5 * 3.141593 / 180.0;

    _clearscreen (_GCLEARSCREEN);

    printf ("Impulse response values H(0) to H(M) are:\n\n");

    fH0 = fW1 / 3.141593;
    printf ("%10.5f", fH0);

    for (iCount = 1; iCount <= iM; iCount++)
        {
        fH[iCount] = (1.0 / (((float)iCount) * 3.141593)) *
                     sin (((float)iCount) * fW1) *
                     cos (((float)iCount) * fW0);
        printf ("%10.5f", fH[iCount]);
        }

    printf ("\nPress any key to plot frequency response...\n");
    getch();

    _setvideomode (_MRES16COLOR);

    for (iCount = 1; iCount <= 320; iCount++)
        {
        fW = 3.141593 * (float)(iCount - 1) / 320.0;
        fHF = fH0;

        for (iCount2 = 1; iCount2 <= iM; iCount2++)
            fHF = fHF + 2.0 * fH[iCount2] *
            cos (((float)iCount2) * fW);

        _moveto (iCount, 100);
        _lineto (iCount, (int)(100 - 70.0 * fabs (fHF) + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
