#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define XDIM 320
#define YDIM 320
#define HDIM 60

float   fX[XDIM + 1], fY[YDIM + 1], fH[HDIM + 1];

void main (void)
    {
    /*
     **********  PROGRAM NO.5    DIGITAL CONVOLUTION  **********
     */
    int    iCount, iCount2;
    float  fMaxX, fMaxY;

    printf ("PROGRAM 5: Digital convolution\n");
    printf ("Press any key to start...\n");
    getch();

    /*
     ******************  DEFINE INPUT SIGNAL  ******************
     */
    for (iCount = 60; iCount <= XDIM; iCount++)
      fX[iCount] = sin (2.0 * 3.141593 * (float)iCount / 60.0) +
                sin (2.0 * 3.141593 * (float)iCount / 10.0);

    /*
     ***** DEFINE IMPULSE RESPONSE (MAX NO. OF TERMS = 60) *****
     */

    for (iCount = 1; iCount <= 10; iCount++)
        fH[iCount] = 0.1;

    /*
     *********** CONVOLVE INPUT AND IMPULSE RESPONSE ***********
     */
    for (iCount = HDIM + 1; iCount <= YDIM; iCount++)
        for (iCount2 = 1; iCount2 <= HDIM; iCount2++)
            fY[iCount] = fY[iCount] + fH[iCount2] *
                         fX[iCount - iCount2];

    /*
     ** NORMALISE SIGNALS TO A MAXIMUM VALUE OF UNITY FOR PLOT *
     */
    fMaxX = 0.0;
    fMaxY = 0.0;

    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        if (fabs (fX[iCount]) > fMaxX)
            fMaxX = fabs (fX[iCount]);
        if (fabs (fY[iCount]) > fMaxY)
            fMaxY = fabs (fY[iCount]);
        }

    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        fX[iCount] /= fMaxX;
        fY[iCount] /= fMaxY;
        }

    _setvideomode( _MRES16COLOR );

    /*
     ********** PLOT HORIZONTAL AXIS AND INPUT SIGNAL **********
     */
    _moveto (0, 50);
    _lineto (XDIM, 50);

    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        _moveto (iCount, 50);
        _lineto (iCount, (int)(50 - fX[iCount] * 30.0 + 0.5));
        }

    /*
     ********* PLOT HORIZONTAL AXIS AND OUTPUT SIGNAL **********
     */
    _moveto (0, 150);
    _lineto (YDIM, 150);

    for (iCount = 1; iCount <= YDIM; iCount++)
        {
        _moveto (iCount, 150);
        _lineto (iCount, (int)(150 - fY[iCount] * 30.0 + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
