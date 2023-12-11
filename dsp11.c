#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define IDIM     320
#define FDIM     320

float   fI[IDIM + 1], fF[FDIM + 1];

void main (void)
    {
    /*
     *** PROGRAM NO.11  CHARACTERISTICS OF 2ND-ORDER SYSTEMS ***
     */
    int    iCount;
    float  fR, fTHETA, fT, fW, fGAIN, fMax, fA, fB, fC, fD;

    _clearscreen  (_GCLEARSCREEN);

    printf ("PROGRAM 11: ");
    printf ("Characteristics of 2nd-order systems\n");

    /*
     * fI=IMPULSE RESPONSE, fF=FREQUENCY RESPONSE (MAGNITUDE) **
     */
    printf ("Enter RADIUS, ANGLE (degrees) of z-plane poles :");
    scanf ("%f, %f", &fR, &fTHETA);

    fT = fTHETA * 3.141593 / 180.0;

    /*
     ***** LOAD IMPULSE RESPONSE, STARTING AT LOCATION fI[2] ***
     */
    fI[1] = 0.0;
    fI[2] = 1.0;

    for (iCount = 3; iCount <= IDIM; iCount++)
        fI[iCount] = 2.0 * fR * cos (fT) * fI[iCount-1] -
                     fR * fR * fI[iCount-2];

    /*
     ******* NORMALISE TO PEAK VALUE OF UNITY, THEN PLOT *******
     */
    fMax = 0.0;

    for (iCount = 1; iCount <= IDIM; iCount++)
        if (fabs (fI[iCount]) > fMax)
            fMax = fabs (fI[iCount]);

    for (iCount = 1; iCount <= IDIM; iCount++)
        fI[iCount] /= fMax;

    _setvideomode( _MRES16COLOR );

    for (iCount = 1; iCount <= IDIM; iCount++)
        {
        _moveto (iCount, 70);
        _lineto (iCount, (int)(70 - fI[iCount] * 30.0 + 0.5));
        }

    /*
     *****************  ESTIMATE PEAK GAIN  ********************
     */
    fA = 1.0 - 2.0 * fR * cos (fT) * cos (fT) +
          fR * fR * cos (2.0 * fT);
    fB = 2.0 * fR * cos (fT) * sin (fT) -
          fR * fR * sin (2.0 * fT);
    fGAIN = 1.0 / pow (fA * fA + fB * fB, 0.5);

    /*
     ****** FIND FREQUENCY RESPONSE (NORMALISED), THEN PLOT ****
     */
    for (iCount = 1; iCount <= IDIM; iCount++)
        {
        fW = (float)(iCount - 1) * 3.141593 / (float)IDIM;
        fC = 1.0 - 2.0 * fR * cos (fT) * cos (fW) +
              fR * fR * cos (2.0 * fW);
        fD = 2.0 * fR * cos (fT) * sin (fW) -
              fR * fR * sin (2.0 * fW);
        fF[iCount] = 1.0/(pow(fC * fC + fD * fD, 0.5) * fGAIN);
        }

    for (iCount = 1; iCount <= IDIM; iCount++)
        {
        _moveto (iCount, 170);
        _lineto (iCount, (int)(170 - fF[iCount] * 60.0 + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
