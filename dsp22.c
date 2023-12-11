#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM     320

float fX[DIM + 1], fY[DIM + 1], fP[DIM + 1], fQ[DIM + 1],
      fR[DIM + 1], fS[DIM + 1], fT[DIM + 1], fU[DIM + 1],
      fV[DIM + 1], fW[DIM + 1];

void main (void)
    {
    /*
     *** PROGRAM NO. 22    FREQUENCY-SAMPLING FILTER ***********
     */
    int    iCount, iCount2, iM;
    float  fFREQ, fHI, fH, fHR;

    _clearscreen  (_GCLEARSCREEN);
    printf ("PROGRAM 22: Frequency sampling filter\n");

    fX[120] = 1.0;

    /*
     ************** LOAD IMPULSE INTO INPUT ARRAY **************
     */
    _setvideomode( _MRES16COLOR );

    for (iCount = 120; iCount <= 280; iCount++)
        {
        fW[iCount] = fX[iCount] - 0.886867 * fX[iCount-120];
        fP[iCount] = 0.5171211 * fP[iCount-1] - 0.998001 *
                     fP[iCount-2] + 0.5 * fW[iCount];
        fQ[iCount] = 0.415408 * fQ[iCount-1] - 0.998001 *
                     fQ[iCount-2] - fW[iCount];
        fR[iCount] = 0.312556 * fR[iCount-1] - 0.998001 *
                     fR[iCount-2] + fW[iCount];
        fS[iCount] = 0.208848 * fS[iCount-1] - 0.998001 *
                     fS[iCount-2] - fW[iCount];
        fT[iCount] = 0.104567 * fT[iCount-1] - 0.998001 *
                     fT[iCount-2] + fW[iCount];
        fU[iCount] = -0.998001 * fU[iCount-2] - 0.666667 *
                     fW[iCount];
        fV[iCount] = -0.104567 * fV[iCount-1] - 0.998001 *
                     fV[iCount-2] + 0.333333 * fW[iCount];
        fY[iCount] = fP[iCount] + fQ[iCount] + fR[iCount] +
                     fS[iCount] + fT[iCount] + fU[iCount] +
                     fV[iCount];

        /*
         *************** PLOT IMPULSE RESPONSE VALUE ***********
         */
        iM = (iCount - 120) * 2;
        _moveto (iM, 70);
        _lineto (iM, (int)(70 - fY[iCount] * 7.0 + 0.5));
        }

    for (iCount = 1; iCount <= 320; iCount++)
        {
        fFREQ = (float) (iCount - 1) * 3.141593 / 320.0;
        fHR = 0.0;
        fHI = 0.0;
        fH = 0.0;

        for (iCount2 = 1; iCount2 <= 120; iCount2++)
            {
            fHR += fY[119 + iCount2] * cos ((float) iCount2 *
                fFREQ);
            fHI += fY[119 + iCount2] * sin ((float) iCount2 *
                fFREQ);
            }

        fH = pow ((fHR * fHR + fHI * fHI), 0.5);

        /*
         ************* PLOT FREQUENCY RESPONSE VALUE ***********
         */
        _moveto (iCount, 170);
        _lineto (iCount, (int)(170 - 0.75 * fH + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );
    
    /*
     ***********************************************************
     */
    }
