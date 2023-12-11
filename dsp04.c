#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HDIM 120
#define XDIM 120

float   fH[HDIM + 1], fX[XDIM + 1];

void main (void)
    {
    /*
     ***** PROGRAM NO.4  IMPULSE RESPONSE OF LTI PROCESSOR *****
     */
    int    iCount;
    float  fA1, fA2, fA3, fB0, fB1, fB2, fMax;

    _clearscreen  (_GCLEARSCREEN);
    printf ("PROGRAM 4: Impulse response of LTI processor\n");

    /*
     ****************** LOAD IMPULSE INTO INPUT ARRAY **********
     */
    printf ("Enter 3 recursive multipliers :");
    scanf ("%f, %f, %f", &fA1, &fA2, &fA3);

    printf ("\nEnter 3 nonrecursive multipliers :");
    scanf ("%f, %f, %f", &fB0, &fB1, &fB2);

    fX[10] = 1.0;

    /*
     **** FIND IMPULSE RESPONSE, TAKING N=10 AS TIME ORIGIN ****
     */

    printf ("Press any key to start...\n\n");
    getch();

    for (iCount = 10; iCount <= HDIM; iCount++)
        fH[iCount] = (fA1 * fH[iCount-1] +
                      fA2 * fH[iCount-2] +
                      fA3 * fH[iCount-3] +
                      fB0 * fX[iCount] +
                      fB1 * fX[iCount-1] +
                      fB2 * fX[iCount-2]);

    /*
     **** NORMALISE fH[iCount] TO A MAXIMUM VALUE OF UNITY *****
     */
    fMax = 0.0;
    for (iCount = 1; iCount <= HDIM; iCount++)
        if (fabs (fH[iCount]) > fMax)
            fMax = fabs (fH[iCount]);

    for (iCount = 1; iCount <= HDIM; iCount++)
        fH[iCount] /= fMax;

    _setvideomode( _MRES16COLOR );

    /*
     ********* PLOT HORIZONTAL AXIS AND IMPULSE INPUT **********
     */
    _moveto (0, 50);
    _lineto (300, 50);

    for (iCount = 1; iCount <= 100; iCount++)
        {
        _moveto (iCount * 3, 50);
        _lineto (iCount * 3, (int)(50.0 - fX[iCount+9] * 25.0 + 0.5));
        }

    /*
     ******* PLOT HORIZONTAL AXIS AND IMPULSE RESPONSE *********
     */
    _moveto (0, 120);
    _lineto (300, 120);

    for (iCount = 1; iCount <= 100; iCount++)
        {
        _moveto (iCount * 3, 120);
        _lineto (iCount * 3, (int)(120 - (fH[iCount+9] * 60.0) + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
