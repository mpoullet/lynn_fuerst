#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main (void)
    {
    /*
     *** PROGRAM NO.12  F-RESPONSE OF MOVING-AVERAGE FILTER ****
     */
    int    iCount, iCount2, iM;
    float  fH, fJ, fW;

    _clearscreen  (_GCLEARSCREEN);
    printf ("PROGRAM 12: F-response of moving-average filter\n");

    printf ("Enter (integer) value of M :");
    scanf ("%d", &iM);

    fJ = 1.0 / (2.0 * (float)iM + 1.0);

    _setvideomode( _MRES16COLOR );
    
    for (iCount = 1; iCount <= 320; iCount++)
        {
        fW = 3.141593 * (float)(iCount - 1) / 320.0;
        fH = fJ;
        for (iCount2 = 1; iCount2 <= iM; iCount2++)
            fH = fH + 2.0 * fJ * cos ((float)iCount2 * fW);

        _moveto (iCount, 100);
        _lineto (iCount, (int)(100 - 50.0 * fabs (fH) + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
