#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define XDIM     320
#define YDIM     320
#define HDIM      21

float   fX[XDIM + 1], fY[YDIM + 1];
float   fH[HDIM] = {-0.007958, -0.025009, -0.017229,  0.021962,
                     0.053052,  0.030746, -0.034458, -0.075026,
                    -0.039789,  0.041192,  0.083333,  0.041192,
                    -0.039789, -0.075026, -0.034458,    0.030746,
                     0.053052,  0.021962, -0.017229, -0.025009,
                    -0.007958};

void main (void)
    {
    /*
     ********************  PROGRAM NO.14  **********************
     **************  TIME-DOMAIN PERFORMANCE OF  ***************
     *********  21-TERM LINEAR-PHASE BANDPASS FILTER  **********
     */
    int    iCount, iCount2;

    _clearscreen (_GCLEARSCREEN);

    printf ("PROGRAM 14: Time-domain performance of 21-term\n");
    printf ("linear-phase bandpass filter\n");
    printf ("Press any key to start...\n");
    getch();

    /*
     ******* LOAD INPUT ARRAY WITH TWO SIGNAL COMPONENTS *******
     */
    for (iCount = 108; iCount <= 180; iCount++)
        fX[iCount] = cos ((float)iCount * 5.0 * 3.141593 / 18.0) +
                     cos ((float)iCount * 7.0 * 3.141593 / 18.0);

    /*
     ************************* PLOT ****************************
     */
    _setvideomode (_MRES16COLOR);

    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        _moveto (iCount, 30);
        _lineto (iCount, (int)(30 - 10.0 * fX[iCount] + 0.5));
        }

    /*
     ***** ADD TWO OUT-OF-BAND COMPONENTS TO INPUT SIGNAL ******
     */
    for (iCount = 1; iCount <= XDIM; iCount++)
        fX[iCount] += sin ((float)iCount * 3.141593 / 8.0) +
                      sin ((float)iCount * 3.141593 / 1.8);

    /*
     ************************* PLOT ****************************
     */
    for (iCount = 1; iCount <= XDIM; iCount++)
        {
        _moveto (iCount, 90);
        _lineto (iCount, (int)(90 - 10.0 * fX[iCount] + 0.5));
        }

    /*
     ** CONVOLVE INPUT SIGNAL AND IMPULSE RESPONSE AND PLOT ****
     */
    for (iCount = 22; iCount <= YDIM; iCount++)
        {
        fY[iCount] = 0;
        for (iCount2 = 0; iCount2 <= 20; iCount2++)
            fY[iCount] += fH[iCount2] * fX[iCount - iCount2];

        _moveto (iCount, 150);
        _lineto (iCount, (int)(150 - 25.0 * fY[iCount] + 0.5));
        }

    getch();
    _setvideomode (_DEFAULTMODE);

    /*
     ***********************************************************
     */
    }
