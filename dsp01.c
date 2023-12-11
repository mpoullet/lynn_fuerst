#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

#define XDIM 320
#define YDIM 320

float   fX[XDIM + 1], fY[YDIM + 1];

void main (void)
    {
    /*
     ********  PROGRAM NO.1    DIGITAL BANDPASS FILTER  ********
     */
    int    iCount;

    _clearscreen  (_GCLEARSCREEN);
    printf ("PROGRAM 1: Digital bandpass filter\n");
    printf ("Press any key to start...\n\n");
    getch();

    /*
     *****  GENERATE INPUT SIGNAL,  AND LOAD INTO ARRAY X  *****
     */
    for (iCount = 1; iCount <= XDIM; iCount++)
        fX[iCount] = sin (3.141593 *
                         (float)iCount *
                         (0.05 + 0.0005 * (float)iCount));

    /*
     ******  ESTIMATE OUTPUT SIGNAL OF RECURSIVE FILTER  *******
     */
    fY[1] = 0.0;
    fY[2] = 0.0;

    for (iCount = 3; iCount <= YDIM; iCount++)
        fY[iCount] = 1.5 *
        fY[iCount - 1] - 0.85 *
        fY[iCount - 2] + fX[iCount];

    /*
     *******  PLOT INPUT AND OUTPUT SIGNALS ON SCREEN  *********
     */

    _setvideomode( _MRES16COLOR );


    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        _moveto (iCount, 50);
        _lineto (iCount, (int)(50.0 - fX[iCount] * 25.0 + 0.5));

        _moveto (iCount, 150);
        _lineto (iCount, (int)(150.0 - fY[iCount] * 4.0 + 0.5));
        }

    getch();

    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
