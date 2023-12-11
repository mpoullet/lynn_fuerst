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
     *** PROGRAM NO.9  FREQUENCY RESPONSE OF BANDPASS FILTER ***
     */
    int    iCount;
    float  fW, fA, fB, fMAG, fPHASE;

    _clearscreen  (_GCLEARSCREEN);
    printf ("PROGRAM 9: Frequency response of ");
    printf ("bandpass filter\n");

    printf ("Press any key to start...\n");
    getch();

    _setvideomode( _MRES16COLOR );

    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        fW = 3.141593 * (iCount - 1) / 320;
        fA = 1.0 - 1.5 * cos (fW) + 0.85 * cos (2.0 * fW);
        fB = 1.5 * sin (fW) - 0.85 * sin (2.0 * fW);
        fMAG = 1.0 / pow ((fA * fA) + (fB * fB), 0.5);
        fPHASE = atan (fB / fA);

        _moveto (iCount, 100);
        _lineto (iCount, (int)(100 - 5.0 * fMAG + 0.5));

        _moveto (iCount, 160);
        _lineto (iCount, (int)(160 - 8.0 * fPHASE + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
