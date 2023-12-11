#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define XDIM  320
#define YDIM  320

float   fX[XDIM + 1], fY[YDIM + 1];

void main (void)
    {
    /*
     **********  PROGRAM NO.10   INVERSE Z-TRANSFORM  **********
     */
    int    iCount;

    _clearscreen  (_GCLEARSCREEN);

    printf ("PROGRAM 10: Inverse z-transform\n");
    printf ("Press any key to start...\n");
    getch();

    fX[5] = 1.0;

    _setvideomode( _MRES16COLOR );

    for (iCount = 5; iCount <= XDIM; iCount++)
        {
        fY[iCount] = -0.54048 * fY[iCount-1] +
                      0.62519 * fY[iCount-2] +
                      0.66354 * fY[iCount-3] -
                      0.60317 * fY[iCount-4] -
                      0.69341 * fY[iCount-5] +
                      fX[iCount] - fX[iCount-1] +
                      fX[iCount-2] - fX[iCount-3];

        _moveto (iCount, 100);
        _lineto (iCount, (int)(100 - 20.0 * fY[iCount] + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
