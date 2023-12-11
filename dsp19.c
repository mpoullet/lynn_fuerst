#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEEDIM    200
#define HDIM      200

float fSEE[SEEDIM + 1], fH[HDIM + 1];

void main (void)
    {
    /*
     *********** PROGRAM NO. 19   DIGITAL DIFFERENTIATOR *******
     */
    int    iCount, iCount2, iX, iM;
    float  fA, fB, fC, fW, fHF;

    _clearscreen  (_GCLEARSCREEN);
    printf ("\n\nPROGRAM 19: Digital differentiator\n\n");

    printf ("Enter (integer) value of M :");
    scanf ("%d", &iM);

    printf ("Select window type: 1 Rectangular, 2 Hamming :");
    scanf ("%d", &iX);

    /*
     ******************** COMPUTE WINDOW VALUES ****************
     */
    if (iX == 1)
        {fA = 1.0; fB = 0; fC = 1.0;}
    else
        {fA = 0.54; fB = 0.46; fC = (float)iM;}

    for (iCount = 1; iCount <= iM; iCount++)
        fSEE[iCount] = fA + fB * cos ((float)iCount *
                 3.141593 / fC);

    /*
     ***************** COMPUTE IMPULSE RESPONSE ****************
     */
    for (iCount = 1; iCount <= iM; iCount++)
        fH[iCount] = (1.0 / (float)iCount) *
                     pow (-1.0, iCount) * fSEE[iCount];

    /*
     **** COMPUTE AND PLOT FREQUENCY RESPONSE (LINEAR SCALE) ***
     */
    _setvideomode( _MRES16COLOR );

    for (iCount = 1; iCount <= 320; iCount++)
        {
        fW = (float)(iCount - 1) * 3.141593 / 320.0;
        fHF = 0.0;
        for (iCount2 = 1; iCount2 <= iM; iCount2++)
            fHF -= 2.0 * fH[iCount2] *
                  sin ((float) iCount2 * fW);

        _moveto (iCount, 150);
        _lineto (iCount, (int)(150.0 - 20.0 * fHF +0.5));
        }

    printf ("Press any key to continue...");
    getch();

    _setvideomode( _DEFAULTMODE );

    printf ("Remember that h(0) is ZERO!\n\n");
    printf ("Values h(1) to h(M) are :\n\n");

    for (iCount = 1; iCount <= iM; iCount++)
        printf ("%18.5f, ", fH[iCount]);

    /*
     ***********************************************************
     */
    }
