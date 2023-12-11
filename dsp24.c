#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM     512

float   fXR[DIM + 1], fXI[DIM + 1];

/*
*** WHEN COMPARING WITH THE TEXT, NOTE THAT IN THE C PROGRAMS **
******* FLOATING-POINT VARIABLES ARE PREFIXED WITH AN f, *******
************** INTEGER VARIABLES WITH AN i *********************
*/

void main (void)
    {
    /*
     ********* PROGRAM NO. 24   FAST FOURIER TRANSFORM (FFT) ***
     */
    int    iCount, iCount2, iCount3, iN = DIM, iM = 9,
           iT, iLim1, iLim2, iLim3, iJ, iL, iY;
    float  fMax, fMag, fB1, fB2, fC1, fC2, fD,
           fPI = 3.141593, fX1, fX2, fARG, fCos1, fSin1;

    _clearscreen  (_GCLEARSCREEN);
    printf ("\n\nPROGRAM 24: Fast Fourier Transform (FFT)\n\n");
    printf ("Press any key to start...\n\n");
    getch();

    for (iCount = 1; iCount <= iN; iCount++)
        fXR[iCount] = fXI[iCount] = 0.0;

    for (iCount = 1; iCount <= 32; iCount++)
        fXR[iCount] = 1.0;

    /*
     ******************** PLOT INPUT DATA **********************
     */
     (iY=1,iY=1);
     _setvideomode( _MAXRESMODE );

    iY = 60;
    for (iCount = 1; iCount <= iN; iCount++)
        {
        _moveto (iCount, iY);
        _lineto (iCount, (int)(iY - fXR[iCount] * 40.0 + 0.5));
        }

    /*
     **** SELECT TRANSFORM/INVERSE TRANSFORM AND PLOT OFFSET ***
     */
    for (iT = 1; iT > -2; iT -= 2)
        {
        iY += 60;
        if (iT < 0)
            fD = (float) iN;
        else
            fD = 1.0;

        /*
         ***************** SHUFFLE INPUT DATA ******************
         */
        iLim1 = iN - 1;
        iLim2 = iN / 2;
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
         ************* IN PLACE TRANSFORMATION *****************
         */
        for (iCount = 1; iCount <= iM; iCount++)
            {
            iLim1 = (int) pow (2, iCount-1);
            iLim2 = (int) pow (2, (iM - iCount));

            for (iCount2 = 1; iCount2 <= iLim2; iCount2++)
                {
                for (iCount3 = 1; iCount3 <= iLim1; iCount3++)
                    {
                    iLim3 = (iCount3 - 1) + (iCount2 - 1) *
                        2 * iLim1 + 1;
                    fB1 = fXR[iLim3];
                    fB2 = fXI[iLim3];
                    fC1 = fXR[iLim3 + iLim1];
                    fC2 = fXI[iLim3 + iLim1];

                    fARG = 2.0 * fPI * (float) (iCount3 - 1) *
                           (float) iLim2 / (float) iN;
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

        for (iCount = 1; iCount <= iN; iCount++)
            {
            fXR[iCount] /= fD;
            fXI[iCount] /= fD;
            }

        /*
         *********** PLOT OUTPUT MAGNITUDE *********************
         */
        fMax = 0.0;
        for (iCount = 1; iCount <= 512 /* iN */; iCount++)
            {
            fMag = sqrt (pow (fXR[iCount], 2) +
                pow (fXI[iCount], 2));
            if (fMag > fMax)
                fMax = fMag;
            }

        for (iCount = 1; iCount <= 512 /*iN*/; iCount++)
            {
            _moveto (iCount+1, iY);
            _lineto (iCount+1, (int)(iY -
                (sqrt (pow (fXR[iCount], 2) +
                pow (fXI[iCount], 2)) * 40.0 / fMax + 0.5)));
            }
        }

    getch();
    _setvideomode( _DEFAULTMODE );
    
    /*
     ***********************************************************
     */
    }
