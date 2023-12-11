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
     ***************** PROGRAM NO.17 *************************
     * NONRECURSIVE FILTER DESIGN BY FOURIER TRANSFORM METHOD
     ***** WITH RECTANGULAR, VON HANN, OR HAMMING WINDOW *****
     *** AND DECIBEL PLOT OF FREQUENCY RESPONSE MAGNITUDE ****
     *********** IMPULSE RESPONSE HAS (2M+1) TERMS ***********
     */
    int    iCount, iCount2, iX, iM;
    float  fA, fB, fH0, fW0, fW1, fC, fFREQ, fMax, fDB;

    _clearscreen  (_GCLEARSCREEN);
    
    printf ("PROGRAM 17: Nonrecursive filter design by ");
    printf ("Fourier\nTransform method with rectangular, ");
    printf ("von Hann or\nHamming window and decibel plot ");
    printf ("of frequency response\nmagnitude. Impulse ");
    printf ("response has (2M+1) terms\n\n");
    printf ("Enter center-frequency (in degrees) :");
    scanf ("%f", &fA);

    printf ("\nEnter filter bandwidth (in degrees) :");
    scanf ("%f", &fB);

    printf ("\nEnter (integer) value of M :");
    scanf ("%d", &iM);

    printf ("\nSelect window:\n");
    printf ("0 = Rectangular; 1 = von Hann; 2 = Hamming :");
    scanf ("%d", &iX);

    fW0 = fA * 3.141593 / 180.0;
    fW1 = fB * 0.5 * 3.141593 / 180.0;

    /*
     ****************** COMPUTE WINDOW VALUES ******************
     */
    switch (iX)
        {
        case 0 :
            fA = 1; fB = 0;
            fC = 1;
            break;

        case 1 :
            fA = 0.5; fB = 0.5;
            fC = (float)iM + 1.0;
            break;

        case 2 :
            fA = 0.54; fB = 0.46;
            fC = (float)iM;
            break;
        }

    for (iCount = 1; iCount <= iM; iCount++)
        fSEE[iCount] = fA + fB * cos ((float)iCount *
                    3.141593 / fC);

    /*
     ************ COMPUTE IMPULSE RESPONSE VALUES **************
     */
    fH0 = fW1 / 3.141593;

    for (iCount = 1; iCount <= iM; iCount++)
        fH[iCount] = (1.0 / ((float)iCount *   3.141593)) *
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
     ***************** COMPUTE FREQUENCY RESPONSE **************
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
     ***** NORMALISE TO UNITY, CONVERT TO DECIBELS & PLOT ******
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

    for (iCount = 1; iCount <= iM; iCount++)
        printf (", %18.5f", (fH[iCount] / fMax));

    printf("\n");
    
    /*
     ***********************************************************
     */
    }
