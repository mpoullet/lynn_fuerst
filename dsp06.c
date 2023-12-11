#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define XDIM 320
#define YDIM 320

float   fX[XDIM + 1], fY[YDIM + 1];

void main (void)
    {
    /*
     *****  PROGRAM NO.6     START-UP AND STOP TRANSIENTS  *****
     */
    int    iCount;
    float  fMaxX, fMaxY;

    _clearscreen  (_GCLEARSCREEN);

    printf ("PROGRAM 6: Start-up and stop transients\n");
    printf ("Press any key to start...\n");
    getch();

    /*
     ***************** DEFINE INPUT SIGNAL *********************
     */
    for (iCount = 20; iCount <= 200; iCount++)
       fX[iCount] = cos (2.0 * 3.141593 * (float)iCount / 20.0);

    /*
     *********** ESTIMATE OUTPUT FROM BANDSTOP FILTER **********
     */
    for (iCount = 3; iCount <= YDIM; iCount++)
        fY[iCount] = 1.8523 * fY[iCount - 1] - 0.94833 *
                     fY[iCount - 2] + fX[iCount] -
                     1.9021 * fX[iCount - 1] + fX[iCount - 2];

    /*
     ** NORMALISE SIGNALS TO MAXIMUM VALUE OF UNITY FOR PLOT ***
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
     ********** PLOT HORIZONTAL AXIS AND INPUT SIGNAL  *********
     */

    _moveto (0, 50);
    _lineto (XDIM, 50);

    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        _moveto (iCount, 50);
        _lineto (iCount, (int)(50 - fX[iCount] * 35.0 + 0.5));
        }

    /*
     ********  PLOT HORIZONTAL AXIS AND OUTPUT SIGNAL **********
     */

    _moveto (0, 150);
    _lineto (YDIM, 150);

    for (iCount = 1; iCount <= YDIM; iCount++)
        {
        _moveto (iCount, 150);
        _lineto (iCount, (int)(150 - fY[iCount] * 35.0 + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
