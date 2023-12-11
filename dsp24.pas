(*******  PROGRAM NO.24       FAST FOURIER TRANSFORM  **********)
program DSP24;
uses graph3;
var XR: array[1..512] of real;
var XI: array[1..512] of real;
var LIM1,LIM2,LIM3,L,R,M,K,N,Y,I,J: integer;
var T,D,X1,X2,PI,B1,B2,C1,C2,ARG,SIN1,COS1,MAG,MAX: real;
label 1,2,3,4,5;
(*******  DEFINE TRANSFORM LENGTH AND ENTER INPUT DATA  ********)
begin
   N:=512;M:=9;
   for K:=1 to N do begin
     XR[K]:=0;XI[K]:=0;end;
   for K:=1 to 32 do begin
     XR[K]:=1;end;
(******  PLOT INPUT DATA USING HIGH RESOLUTION GRAPHICS  *******)
   hires;
   Y:=60; for K:=1 to N do begin
     draw(K,Y,K,round(Y-XR[K]*40),1);end;
(*****  SELECT TRANSFORM/INVERSE TRANSFORM AND PLOT OFFSET  ****)
    T:=1;D:=1;
 1: Y:=Y+60;IF T<0 THEN D:=N;
(*********************  SHUFFLE INPUT DATA  ********************)
    LIM1:=N-1;LIM2:=trunc(N/2);J:=1;
    for I:=1 to LIM1 do begin
      if I>J-1 then goto 2;
        X1:=XR[J];X2:=XI[J];
        XR[J]:=XR[I];XI[J]:=XI[I];XR[I]:=X1;XI[I]:=X2;
 2: L:=LIM2;
 3: if L>J-1 then goto 4;
    J:=J-L;L:=trunc(L/2);goto 3;
 4: J:=J+L; end;
(******************  IN-PLACE TRANSFORMATION  ******************)
    PI:=3.141593;
    for I:=1 to M do begin
      LIM1:=trunc(exp((I-1)*ln(2)));
      LIM2:=trunc(exp((M-I)*ln(2)));
        for L:=1 to LIM2 do begin
          for R:=1 to LIM1 do begin
            LIM3:=(R-1)+(L-1)*2*LIM1+1;
            B1:=XR[LIM3];B2:=XI[LIM3];C1:=XR[LIM3+LIM1];
            C2:=XI[LIM3+LIM1];
            ARG:=2*PI*(R-1)*LIM2/N;COS1:=cos(ARG);SIN1:=sin(ARG);
            X1:=C1*COS1+C2*SIN1*T;X2:=-C1*SIN1*T+C2*COS1;
            XR[LIM3]:=B1+X1;XI[LIM3]:=B2+X2;
            XR[LIM3+LIM1]:=B1-X1;XI[LIM3+LIM1]:=B2-X2;
  end;end;end;
  for K:=1 to N do begin
    XR[K]:=XR[K]/D;XI[K]:=XI[K]/D;end;
(******************  PLOT OUTPUT (MAGNITUDE)  ******************)
  MAX:=0;
    for K:=1 to N do begin
      MAG:=sqrt(XR[K]*XR[K]+XI[K]*XI[K]);
      if MAG>MAX then MAX:=MAG;end;
  for K:=1 to N do begin
    draw(K,Y,K,round(Y-sqrt(XR[K]*XR[K]+XI[K]*XI[K])*40/MAX),1);
  end;
  if T<0 then GOTO 5;
  T:=-1;goto 1;
 5: end.
(***************************************************************)