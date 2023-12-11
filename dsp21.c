#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRDIM     50
#define PIDIM     50

double fPR[PRDIM + 1], fPI[PIDIM + 1];

void main (void)
    {
    /*
     ******** PROGRAM NO. 21    POLES AND ZEROS OF *************
     ****** BUTTERWORTH AND CHEBYSHEV DIGITAL FILTERS **********
     */
    int    iCount, iFF, iFT, iN, iIN, iN1, iN2, iM, iST;
    double  fF1, fF2, fF3, fF4, fF5, fW1, fB1, fB2,
           fC1, fC2, fC3, fC4, fC5, fD, fE, fY, fX, fA, fB, fT,
           fR, fI, fSI, fB3, fGR, fAR, fFR, fSR, fFI, fAI, fGI,
           fH1, fH2, fP1I, fP2I, fP1R, fP2R, fTH;

    _clearscreen  (_GCLEARSCREEN);
    printf ("\n\nPROGRAM 21: Poles and zeros of Butterworth and\n");
    printf ("  Chebyshev digital filters\n\n");

    printf ("Choose filter family: 1 = Butterworth, ");
    printf ("2 = Chebyshev :");
    scanf ("%d", &iFF);

    printf ("\nChoose filter type: 1 = Lowpass, 2 = Highpass, ");
    printf ("3 = Bandpass :");
    scanf ("%d", &iFT);

    printf ("\nFilter order :");
    scanf ("%d", &iN);

       switch (iFT)
        {
        case 1 :
        case 2 :
            printf ("\nCut-off frequency (degrees) :");
            scanf ("%lf", &fF1);
            iST = 2;

            if (iFT == 2)
                fF1 = 180.0 - fF1;

            break;

        case 3 :
            iN /= 2;
            printf ("\nLower, Upper cut-off frequencies ");
            printf ("(degrees) :");
            scanf ("%lf, %lf", &fF2, &fF3);
            fF1 = fF3 - fF2;
            iST = 1;
        }

    if (iFF == 2)
        {
        printf ("\n\nPassband ripple (fraction) :");
        scanf ("%lf", &fD);
        }

    /*
     *********** FIND BUTTERWORTH/CHEBYSHEV PARAMETERS *********
     */
    iIN = iN % 2;
    iN1 = iN + iIN;
    iN2 = (3 * iN + iIN) / 2 - 1;
    fW1 = 3.141593 * fF1 / 360.0;
    fC1 = sin (fW1) / cos (fW1);
    fB1 = 2.0 * fC1;
    fC2 = fC1 * fC1;
    fB2 = 0.25 * fB1 * fB1;

    if (iFF == 2)
        {
        fE = 1.0 / sqrt (1.0 / ((1.0 - fD) * (1.0 - fD)) - 1.0);
        fX = pow (sqrt (fE * fE + 1.0) + fE, 1.0 / (double)iN);
        fY = 1.0 / fX;
        fA = 0.5 * (fX - fY);
        fB = 0.5 * (fX + fY);
        }

    /*
     **** FIND REAL AND IMAGINARY PARTS OF LOW-PASS POLES ******
     */
    for (iCount = iN1; iCount <= iN2; iCount++)
        {
        fT = 3.141593 * (2.0 * (double)iCount + 1.0 -
             (double) iIN) / (2.0 * iN);

        if (iFF == 2)
            {
            fC3 = fA * fC1 * cos (fT);
            fC4 = fB * fC1 * sin (fT);
            fC5 = pow ((1.0 - fC3), 2.0) + (fC4 * fC4);
            fR = 2.0 * (1.0 - fC3) / fC5 - 1.0;
            fI = 2.0 * fC4 / fC5;
            }
        else
            {
            fB3 = 1.0 - fB1 * cos (fT) + fB2;
            fR = (1.0 - fB2) / fB3;
            fI = fB1 * sin (fT) / fB3;
            }

        iM = (iN2 - iCount) * 2 + 1;

        fPR[iM + iIN] = fR;
        fPI[iM + iIN] = fI;
        fPR[iM + iIN + 1] = fR;
        fPI[iM + iIN + 1] = (0.0 - fI);
        }

    if (iIN != 0)
        {
        if (iFF == 1)
            fR = (1.0 - fB2) / (1.0 + fB1 + fB2);
        else
            fR = 2.0 / (1.0 + fA * fC1) - 1.0;

        fPR[1] = fR;
        fPI[1] = 0.0;
        }

    switch (iFT)
        {
        /*
         *********** PRINT OUT Z-PLANE ZERO LOCATIONS **********
         */
        case 1 :
            printf ("\nReal zero, of order %d at z= -1\n", iN);
            break;

        case 2 :
            printf ("\nReal zero, of order %d at z = 1\n", iN);
            for (iCount = 1; iCount <= iN; iCount++)
                fPR[iCount] = 0.0 - fPR[iCount];
            break;

        case 3 :
            printf ("\nReal zeros, of order %d at z = 1 and ", iN);
            printf ("z = -1\n");

            /*
             ******* LOW-PASS TO BANDPASS TRANSFORMATION *******
             */
            fF4 = fF2 * 3.141593 / 360.0;
            fF5 = fF3 * 3.141593 / 360.0;
            fA = cos (fF4 + fF5) / cos (fF5 - fF4);
            for (iCount = 1; iCount <= 50; iCount += 2)
                {
                fAR = fPR[iCount];
                fAI = fPI[iCount];
                if (fabs (fAI) >= 0.0001)
                    {
                    fFR = fA * 0.5 * (1.0 + fAR);
                    fFI = fA * 0.5 * fAI;
                    fGR = fFR * fFR - fFI * fFI - fAR;
                    fGI = 2.0 * fFR * fFI - fAI;
                    fSR = pow (fabs (fGR +
                           pow ((fGR * fGR + fGI * fGI),
                           0.5)) / 2.0, 0.5);
                    fSI = fGI / (2.0 * fSR);
                    fP1R = fFR + fSR;
                    fP1I = fFI + fSI;
                    fP2R = fFR - fSR;
                    fP2I = fFI - fSI;
                    }
                else
                    {
                    fH1 = fA * (1.0 + fAR) / 2.0;
                    fH2 = fH1 * fH1 - fAR;
                    if (fH2 > 0)
                        {
                        fP1R = fH1 + pow (fH2, 0.5);
                        fP2R = fH1 - pow (fH2, 0.5);
                        fP1I = 0;
                        fP2I = 0;
                        }
                    else
                        {
                        fP1R = fH1;
                        fP2R = fH1;
                        fP1I = pow (fabs (fH2), 0.5);
                        fP2I = -1.0 * fP1I;
                        }
                    }

                fPR[iCount] = fP1R;
                fPR[iCount + 1] = fP2R;
                fPI[iCount] = fP1I;
                fPI[iCount + 1] = fP2I;
                }
        }
    /*
     ************ PRINT OUT Z-PLANE POLE LOCATIONS *************
     */
    printf ("\nRadii, angles of z-plane poles:\n\n");
    printf ("\n    R      THETA\n\n");

    for (iCount = 1; iCount <= iN; iCount += iST)
        {
        iM = iCount;
        if (iIN != 0)
            if (iCount == 2)
                iM = iN + 1;

        fR = pow (fPR[iM] * fPR[iM] + fPI[iM] * fPI[iM], 0.5);
        fTH = atan (fabs (fPI[iM]) / fabs (fPR[iM])) *
              (180.0 / 3.141593);
        if (fPR[iM] < 0.0)
            fTH = 180 - fTH;
        printf ("%lf %lf\n", fR, fTH);
        }

    /*
     ***********************************************************
     */
    }
