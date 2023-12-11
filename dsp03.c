#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

#define XDIM 320

float   fX[XDIM + 1];

void main (void)
    {
    /*
     *****  PROGRAM NO.3   AMBIGUITY IN DIGITAL SINUSOIDS  *****
     */
    int    iCount, iM, iK;

    _clearscreen  (_GCLEARSCREEN);
    /*
     *** GENERATE SIGNAL WITH TEN EQUAL FREQUENCY INCREMENTS ***
     */
    printf ("PROGRAM 3: Ambiguity in digital sinusoids\n");
    printf ("Press any key to start...\n\n");
    getch();

    for (iM = 0; iM < 10; iM++)
        for (iK = 1; iK < 33; iK++)
            {
            iCount = iK + 32 * iM;
            fX[iCount] = cos ((float)iCount * 2.0 *
                         3.141593 * (float)iM / 8.0);
            }

    /*
     *********************  PLOT  ******************************
     */
    _setvideomode( _MRES16COLOR );

    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        _moveto (iCount, 50);
        _lineto (iCount, 50 - (int)(fX[iCount] * 25.0  + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
