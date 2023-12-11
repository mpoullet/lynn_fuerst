#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main (void)
    {
    /*
     ********************** PROGRAM NO.15 **********************
     ** SPECTRAL PROPERTIES OF RECTANGULAR WINDOW (LOG PLOT) ***
     */
    int    iCount, iCount2, iM;
    float  fFREQ, fH, fDB;

    _clearscreen  (_GCLEARSCREEN);
    
    printf ("PROGRAM 15: Spectral properties of rectangular\n");
    printf ("window (log plot)\n\n");

    printf ("Enter (integer) value of M :");
    scanf ("%d", &iM);

    _setvideomode( _MRES16COLOR );

    /*
     ************** DRAW RECTANGULAR GRID FOR PLOT *************
     */
    for (iCount = 0; iCount <= 5; iCount++)
        {
        _moveto (0, 30 + 20 * iCount);
        _lineto (320, 30 + 20 * iCount);
        _moveto (64 * iCount, 30);
        _lineto (64 * iCount, 130);
        }

    _moveto (319, 30);
    _lineto (319, 130);

    /*
     ***** ESTIMATE SPECTRUM, CONVERT TO DECIBELS AND PLOT *****
     */
    for (iCount = 1; iCount <= 320; iCount++)
        {
        fFREQ = 3.141593 * (float)(iCount - 1) / 320.0;
        fH = 1.0;
        for (iCount2 = 1; iCount2 <= iM; iCount2++)
            fH += 2.0 * cos ((float)iCount2 * fFREQ);

        fH /= (1.0 + 2.0 * (float)iM);
        fDB = 20.0 * (float) log (fabs (fH)) * 0.4343;

        if (fDB < -50.0)
            fDB = -50.0;

        _moveto (iCount, 130);
        _lineto (iCount, (int)(30 - 2.0 * fDB + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );

    /*
     ***********************************************************
     */
    }
