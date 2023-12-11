#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEEDIM    200
#define HDIM      200
#define WDIM      320

float fSEE[SEEDIM + 1], fH[HDIM + 1], fW[WDIM + 1];

void main (void)
    {
    /*
     ******************* PROGRAM NO.18 *************************
     **** NONRECURSIVE FILTER DESIGN WITH THE KAISER WINDOW ****
     */
    int    iCount, iCount2, iX, iM;
    float  fM, fP, fQ, fR, fS, fT, fA, fA0, fB, fC, fD,
           fALPHA, fBETA, fTEMP, fI,
           fH0, fW0, fW1, fFREQ, fMax, fDB;

    _clearscreen  (_GCLEARSCREEN);
    printf ("PROGRAM 18: Nonrecursive filter design with\n");
    printf ("the Kaiser window\n\n");

    while (1)
        {
        printf ("Enter center-frequency (in degrees) :");
        scanf ("%f", &fP);

        printf ("Enter filter bandwidth (in degrees) :");
        scanf ("%f", &fQ);

        printf ("Enter Kaiser design parameters\n");
        printf ("  Ripple (as a fraction) :");
        scanf ("%f", &fR);

        printf ("\nTransition width (in degrees) :");
        scanf ("%f", &fS);

        fW0 = fP * 3.141593 / 180.0;
        fW1 = fQ * 0.5 * 3.141593 / 180.0;
        fT = fS / 360.0;

        /*
         *************** ESTIMATE KAISER PARAMETERS ************
         */
        fA = -20.0 * log (fR) * 0.4343;
        fM = (fA - 7.95) / (28.72 * fT);
        iM = ((int)(fM+1));

        printf ("\n  No. of impulse response terms = %d\n",
                              2 * iM + 1);
        printf ("\n  Change Parameters, or continue? (0/1) :");
        scanf ("%d", &iX);

        if (iX)
            break;
        }

    if (fA > 49.0)
        fALPHA = 0.1102 * (fA - 8.7);
    else if (fA > 21)
        fALPHA = 0.5842 * pow((fA - 21.0), 0.4) +
                 (0.07886 * (fA - 21.0));
    else
        fALPHA = 0;

    printf ("\nFor this window, ALPHA = %f\n", fALPHA);
    printf ("Press any key to start...");
    getch();

    /*
     ******************* COMPUTE WINDOW VALUES *****************
     */
    for (iCount = 0; iCount <= iM; iCount++)
        {
        fTEMP = 1.0 - pow (((float) iCount / (float) iM), 2.0);
        fBETA = fALPHA * pow (fTEMP, 0.5);
        fI = fB = 1.0;

        for (iCount2 = 1; iCount2 <= 20; iCount2++)
            {
            fC = fB * fBETA * fBETA / 4.0;
            fD = fC / (float)(iCount2 * iCount2);
            fI += fD;
            fB = fD;
            }

        fSEE[iCount] = fI;
        }

    fA0 = fSEE[0];
    for (iCount = 0; iCount <= iM; iCount++)
        fSEE[iCount] /= fA0;

    /*
     *************** COMPUTE IMPULSE RESPONSE VALUES ***********
     */
    fH0 = fW1 / 3.141593;

    for (iCount = 1; iCount <= iM; iCount++)
        fH[iCount] = (1.0 / ((float)iCount * 3.141593)) *
                      sin ((float)iCount * fW1) *
                      cos ((float)iCount * fW0) *
                      fSEE[iCount];

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
     **************** COMPUTE FREQUENCY RESPONSE ***************
     */
    for (iCount = 1; iCount <= WDIM; iCount++)
        {
        fFREQ = 3.141593 * (float)(iCount - 1) / 320.0;
        fW[iCount] = fH0;
        for (iCount2 = 1; iCount2 <= iM; iCount2++)
            fW[iCount] += 2.0 * fH[iCount2] *
                         cos ((float)iCount2 * fFREQ);
        }

    /*
     ****** NORMALISE TO UNITY, CONVERT TO DECIBELS & PLOT *****
     */
    fMax = 0;

    for (iCount = 1; iCount <= WDIM; iCount++)
        if (fabs (fW[iCount]) > fMax)
            fMax = fabs (fW[iCount]);

    for (iCount = 1; iCount <= WDIM; iCount++)
        {
        fDB = 20.0 * log (fabs (fW[iCount]) / fMax) * 0.4343;

        if (fDB < -50.0)
            fDB = -50.0;

        _moveto (iCount, 130);
        _lineto (iCount, (int)(30 - 2.0 * fDB + 0.5));
        }

    printf ("Press any key to continue...");
    getch();

    _setvideomode( _DEFAULTMODE );

    printf ("Impulse response values h(0) to h(M)\n");
    printf ("(corrected for unity maximum gain) :\n\n");

    printf ("%18.5f", (fH0 / fMax));

    for (iCount = 0; iCount < iM; iCount++)
        printf (", %18.5f", (fH[iCount] / fMax));

    /*
     ***********************************************************
     */
    }
