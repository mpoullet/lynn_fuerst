#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM     128

float   fXR[DIM + 1], fXI[DIM + 1], fVR[DIM + 1], fVI[DIM + 1],
        fWR[DIM + 1], fWI[DIM + 1], fX[DIM + 1], fH[DIM + 1],
        fY[DIM + 1];

/*
*** WHEN COMPARING WITH THE TEXT, NOTE THAT IN THE C PROGRAMS **
******* FLOATING-POINT VARIABLES ARE PREFIXED WITH AN f, *******
************** INTEGER VARIABLES WITH AN i *********************
*/

void main (void)
    {
    /*
     **** PROGRAM NO. 25    FAST CONVOLUTION *******************
     */
    int    iCount, iCount2, iCount3, iXX, iYY, iM = 7,
           iP, iT, iLim1, iLim2, iLim3, iJ, iL;
    float  fMax, fXHMAG, fMag, fXT, fB1, fB2, fC1, fC2, fD,
           fPI = 3.141593, fX1, fX2, fARG, fCos1, fSin1;

    _clearscreen  (_GCLEARSCREEN);
    printf ("\n\nPROGRAM 25: Fast convolution\n\n");
    printf ("Press any key to start...\n\n");
    getch();

    /*
     *** DEFINE AND PLOT INPUT SIGNAL AND IMPULSE RESPONSE *****
     */
    for (iCount = 1; iCount <= 64; iCount++)
        fX[iCount] = 1.0;

    fH[1] = 1.0;
    fH[2] = 1.5;

    for (iCount = 3; iCount <= 64; iCount++)
        fH[iCount] = 1.5 * fH[iCount-1] - 0.85 * fH[iCount-2];

    _setvideomode( _MRES16COLOR );

    for (iCount = 1; iCount <= DIM; iCount++)
        {
        _moveto (iCount + 1, 70);
        _lineto (iCount + 1, (int)(70 - fX[iCount] * 25.0 + 0.5));
        }

    for (iCount = 1; iCount < DIM; iCount++)
        {
        _moveto (iCount + 190, 70);
        _lineto (iCount + 190, (int)(70 - fH[iCount] * 25.0 + 0.5));
        }

    /*
     *********** CONVOLVE IN TIME DOMAIN THEN PLOT *************
     */
    for (iCount = 1; iCount <= DIM; iCount++)
        for (iCount2 = 1; iCount2 < iCount; iCount2++)
            fY[iCount] += fX[iCount2] * fH[iCount - iCount2 + 1];

    for (iCount = 1; iCount <= DIM; iCount++)
        {
        _moveto (iCount + 100, 160);
        _lineto (iCount + 100, (int)(160 - fY[iCount] * 8.0 + 0.5));
        }

    printf ("Press any key to start fast convolution");
    getch();

    _clearscreen  (_GCLEARSCREEN);
    _setvideomode( _MRES16COLOR );

    for (iP = 1; iP <= 3; iP++)
        {
        if (iP == 1)
            {
            iT = 1;
            fD = 1.0;
            for (iCount = 1; iCount <= DIM; iCount++)
                {
                fXR[iCount] = fX[iCount];
                fXI[iCount] = 0.0;
                }
            }

        if (iP == 2)
            {
            iT = 1;
            fD = 1.0;
            for (iCount = 1; iCount <= DIM; iCount++)
                {
                fXR[iCount] = fH[iCount];
                fXI[iCount] = 0.0;
                }
            }

        if (iP == 3)
            {
            iT = -1;
            fD = (float) DIM;
            for (iCount = 1; iCount <= DIM; iCount++)
                {
                fXR[iCount] = fVR[iCount] * fWR[iCount] -
                                fVI[iCount] * fWI[iCount];
                fXI[iCount] = fVI[iCount] * fWR[iCount] +
                                fVR[iCount] * fWI[iCount];
                fXHMAG = pow ((pow (fVR[iCount], 2) +
                               pow (fVI[iCount], 2)) *
                               (pow (fWR[iCount], 2) +
                               pow (fWI[iCount], 2)), 0.5);
                _moveto (iCount, 160);
                _lineto (iCount, (int)(160 - fXHMAG / 4.0 + 0.5));
                }
            }
        /*
         **************** SHUFFLE INPUT DATA *******************
         */
        iLim1 = DIM - 1;
        iLim2 = DIM / 2;
        iJ = 1;

        for (iCount = 1; iCount <= iLim1; iCount++)
            {
            if ((float) iCount <= ((float) iJ - 0.01))
                {
                fX1 = fXR[iJ];
                fX2 = fXI[iJ];
                fXR[iJ] = fXR[iCount];
                fXI[iJ] = fXI[iCount];
                fXR[iCount] = fX1;
                fXI[iCount] = fX2;
                }
            iL = iLim2;
            while (1)
                {
                if ((float)iL > ((float)(iJ) - 0.01))
                    break;
                iJ -= iL;
                iL /= 2;
                }
            iJ += iL;
            }

        /*
         **************** IN PLACE TRANSFORMATION **************
         */
        for (iCount = 1; iCount <= iM; iCount++)
            {
            iLim1 = (int) pow (2, iCount - 1);
            iLim2 = (int) pow (2, (iM - iCount));

            for (iCount2 = 1; iCount2 <= iLim2; iCount2++)
                {
                for (iCount3 = 1; iCount3 <= iLim1; iCount3++)
                    {
                    iLim3 = (iCount3 - 1) + (iCount2 - 1) * 2 *
                        iLim1 + 1;
                    fB1 = fXR[iLim3];
                    fB2 = fXI[iLim3];
                    fC1 = fXR[iLim3 + iLim1];
                    fC2 = fXI[iLim3 + iLim1];

                    fARG = 2.0 * fPI * (float) (iCount3 - 1) *
                           (float) iLim2 / (float) DIM;
                    fCos1 = cosl (fARG);
                    fSin1 = sinl (fARG);
                    fX1 = fC1 * fCos1 + fC2 * fSin1 *
                        (float) iT;
                    fX2 = (0.0 - fC1) * fSin1 * (float) iT +
                        fC2 * fCos1;
                    fXR[iLim3] = fB1 + fX1;
                    fXI[iLim3] = fB2 + fX2;
                    fXR[iLim3 + iLim1] = fB1 - fX1;
                    fXI[iLim3 + iLim1] = fB2 - fX2;
                    }
                }
            }

        for (iCount = 1; iCount <= DIM; iCount++)
            {
            fXR[iCount] /= fD;
            fXI[iCount] /= fD;
            }

        /*
         * SAVE TRANSFORMS OF INPUT SIGNAL & IMPULSE RESPONSE **
         */
        if (iP == 1)
            {
            for (iCount = 1; iCount <= DIM; iCount++)
                {
                fVR[iCount] = fXR[iCount];
                fVI[iCount] = fXI[iCount];
                }
            }

        if (iP == 2)
            {
            for (iCount = 1; iCount <= DIM; iCount++)
                {
                fWR[iCount] = fXR[iCount];
                fWI[iCount] = fXI[iCount];
                }
            }

        /*
         ************** FIND PEAK VALUE FOR PLOT ***************
         */
        fMax = 0.0;
        for (iCount = 1; iCount <= DIM; iCount++)
            {
            fMag = pow (pow (fXR[iCount], 2) +
                pow (fXI[iCount], 2), 0.5);
            if (fMag > fMax)
                fMax = fMag;
            }

        /*
         ***************** SET PLOT OFFSETS ********************
         */
        switch (iP)
            {
            case 1 :
                iXX = 0;
                iYY = 70;
                break;

            case 2 :
                iXX = 190;
                iYY = 70;
                break;

            case 3 :
                iXX = 190;
                iYY = 160;
                break;
            }

        for (iCount = 1; iCount <= DIM; iCount++)
            {
            if (iP == 3)
                fXT = fXR[iCount];
            else
                fXT = pow (pow (fXR[iCount], 2) +
                    pow (fXI[iCount], 2), 0.5);

            _moveto (iCount + iXX, iYY);
            _lineto (iCount + iXX, (int)(iYY -
                fXT * 40.0 / fMax + 0.5));
            }
        }

    getch();
    _setvideomode( _DEFAULTMODE );
    
    /*
     ***********************************************************
     */
    }
