#include <graph.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RPDIM     20
#define RZDIM     20
#define CPDIM     20
#define CZDIM     20
#define HDIM      320

float fH[HDIM + 1], fRP[RPDIM + 1][2], fRZ[RZDIM + 1][2],
      fCP[CPDIM + 1][2], fCZ[CZDIM + 1][2];

void main (void)
    {
    /*
     **** PROGRAM NO. 20  FILTER MAGNITUDE RESPONSE ************
     ****** FROM Z-PLANE POLE AND ZERO LOCATIONS ***************
     */
    int    iCount, iCount2, iNRP, iNRZ, iNCP, iNCZ;
    float  fW, fC1, fC2, fS1, fS2, fA, fB, fR, fT, fD, fE,
           fMAX, fDB;

    _clearscreen  (_GCLEARSCREEN);
    printf ("\n\nPROGRAM 20: Filter magnitude response from ");
    printf ("z-plane\npole and zero locations\n\n");

    printf ("Enter no. of SEPARATE real poles :");
    scanf ("%d", &iNRP);

    if (iNRP != 0)
        {
        printf ("\nEnter value, order of each in turn :\n");
        printf ("   Followed by <Return>.\n");

        for (iCount = 1; iCount <= iNRP; iCount++)
            scanf ("%f, %f", &fRP[iCount][0], &fRP[iCount][1]);
        }

    printf ("\nEnter no. of SEPARATE real zeros :");
    scanf ("%d", &iNRZ);

    if (iNRZ != 0)
        {
        printf ("\nEnter value, order of each in turn :\n");
        printf ("   Followed by <Return>.\n");

        for (iCount = 1; iCount <= iNRZ; iCount++)
            scanf ("%f, %f", &fRZ[iCount][0], &fRZ[iCount][1]);
        }

    printf ("\nEnter no. of complex-conjugate pole pairs :");
    scanf ("%d", &iNCP);

    if (iNCP != 0)
        {
        printf ("\nEnter radius, angle (in degrees) of ");
        printf ("each in turn :\n");
        printf ("   Followed by <Return>.\n");

        for (iCount = 1; iCount <= iNCP; iCount++)
            scanf ("%f, %f", &fCP[iCount][0], &fCP[iCount][1]);
        }

    printf ("\nEnter no. of complex-conjugate zero pairs :");
    scanf ("%d", &iNCZ);

    if (iNCZ != 0)
        {
        printf ("\nEnter radius, angle (in degrees) of ");
        printf ("each in turn :\n");
        printf ("   Followed by <Return>.\n");

        for (iCount = 1; iCount <= iNCZ; iCount++)
            scanf ("%f, %f", &fCZ[iCount][0], &fCZ[iCount][1]);
        }

    /*
     *********** COMPUTE FREQUENCY RESPONSE MAGNITUDE **********
     */
    for (iCount = 1; iCount <= HDIM; iCount++)
        {
        fW = 3.141593 * (float)(iCount - 1) / HDIM;
        fC1 = cos (fW);
        fC2 = cos (2.0 * fW);
        fS1 = sin (fW);
        fS2 = sin (2.0 * fW);
        fH[iCount] = 1.0;

        if (iNRP != 0)
            {
            for (iCount2 = 1; iCount2 <= iNRP; iCount2++)
                {
                fA = fRP[iCount2][0];
                fB = fRP[iCount2][1];
                fH[iCount] /= pow ((1.0 - 2.0 * fA * fC1 + fA * fA),
                                   (fB / 2.0));
                }
            }

        if (iNRZ != 0)
            {
            for (iCount2 = 1; iCount2 <= iNRZ; iCount2++)
                {
                fA = fRZ[iCount2][0];
                fB = fRZ[iCount2][1];
                fH[iCount] *= pow ((1.0 - 2.0 * fA * fC1 + fA * fA),
                                   (fB / 2.0));
                }
            }

        if (iNCP != 0)
            {
            for (iCount2 = 1; iCount2 <= iNCP; iCount2++)
                {
                fR = fCP[iCount2][0];
                fT = fCP[iCount2][1] * 3.141593 / 180.0;
                fD = fC2 - 2.0 * fR * cos (fT) * fC1 + fR * fR;
                fE = fS2 - 2.0 * fR * cos (fT) * fS1;

                fH[iCount] /= pow ((fD * fD + fE * fE), 0.5);
                }
            }

        if (iNCZ != 0)
            {
            for (iCount2 = 1; iCount2 <= iNCZ; iCount2++)
                {
                fR = fCZ[iCount2][0];
                fT = fCZ[iCount2][1] * 3.141593 / 180.0;
                fD = fC2 - 2.0 * fR * cos (fT) * fC1 + fR * fR;
                fE = fS2 - 2.0 * fR * cos (fT) * fS1;

                fH[iCount] *= pow ((fD * fD + fE * fE), 0.5);
                }
            }
        }

    /*
     ************** FIND MAXIMUM VALUE AND PRINT OUT ***********
     */
    fMAX = 0.0;

    for (iCount = 1; iCount <= HDIM; iCount++)
        if (fabs (fH[iCount] > fMAX))
            fMAX = fabs (fH[iCount]);

    printf ("\nMaximum gain = %f (%f DB)\n", fMAX,
            20.0 * log (fMAX) * 0.4343);

    printf ("Press any key to plot...");
    getch ();
    _setvideomode( _MRES16COLOR );

    /*
     ***************** DRAW RECTANGULAR GRID FOR PLOT **********
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
     * NORMALISE RESPONSE TO UNITY, CONVERT TO DECIBELS & PLOT *
     */
    for (iCount = 1; iCount <= HDIM; iCount++)
        {
        if (fabs (fH[iCount]) < 0.000001)
            fH[iCount] = 0.000001;

        fDB = 20.0 * log (fabs (fH[iCount]) / fMAX) * 0.4343;

        if (fDB < -50.0)
            fDB = -50.0;

        _moveto (iCount, 130);
        _lineto (iCount, (int)(30.0 - 2.0 * fDB + 0.5));
        }

    getch();
    _setvideomode( _DEFAULTMODE );
    
    /*
     ***********************************************************
     */
    }
