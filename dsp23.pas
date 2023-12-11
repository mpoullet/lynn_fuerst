(*****  PROGRAM NO.23    DISCRETE FOURIER TRANSFORM (DFT)  *****)
(*******  BY DIRECT CALCULATION, AND WITH TABLE LOOKUP  ********)
(******  REAL SIGNAL, N=64, SPECTRAL MAGNITUDE & PHASE  ********)
program DSP23;
uses graph3;
var X: array[1..64] of real;
var S: array[1..64] of real;
var C: array[1..64] of real;
var XXR: array[1..64] of real;
var XXI: array[1..64] of real;
var MAG: array[1..64] of real;
var PHASE: array[1..64] of real;
var N,K,D,P,J,L,I: integer;
var B,W0,M1,M2,M3: real;
label 1,2;
(**********************  GENERATE SIGNAL  **********************)
begin
    for N:=1 to 64 do begin
      B:=2*3.141593*(N-1);
      X[N]:=sin(B/64)+cos(B/16)+0.6*cos(B/8)+0.5*sin(B/4);end;
  P:=1;
    for N:=1 to 64 do begin XXR[N]:=0;XXI[N]:=0;end;
   writeln('ENTER ANY INTEGER TO START FIRST DFT');readln(D);
     for K:=1 to 64 do begin
      for N:=1 to 64 do begin
       XXR[K]:=XXR[K]+X[N]*cos(2*3.141593*(K-1)*(N-1)/64);
       XXI[K]:=XXI[K]-X[N]*sin(2*3.141593*(K-1)*(N-1)/64);
     end;end;
  if P=1 then goto 2;
1:  for J:=1 to 64 do begin XXR[J]:=0;XXI[J]:=0;end;
    writeln('ENTER ANY INTEGER TO START SECOND DFT');readln(D);
(********************  FORM TABLE LOOKUP  **********************)
W0:=2*3.141593/64;
  for J:=1 to 64 do begin
    C[J]:=cos(W0*(J-1));S[J]:=sin(W0*(J-1));end;
      for K:=1 to 64 do begin
        for N:=1 to 64 do begin
          I:=(K-1)*(N-1);L:=I mod 64;
          XXR[K]:=XXR[K]+X[N]*C[L+1];
          XXI[K]:=XXI[K]-X[N]*S[L+1];
      end;end;
(************  CONVERT TO SPECTRAL MAGNITUDE & PHASE  **********)
2: for K:=1 to 64 do begin
     if abs(XXI[K])<0.001 then XXI[K]:=0;
     if abs(XXR[K])<0.00001 then XXR[K]:=0.00001;
     MAG[K]:=sqrt(XXR[K]*XXR[K] + XXI[K]*XXI[K]);
     PHASE[K]:=arctan(XXI[K]/XXR[K]);end;
(*******  NORMALISE TO MAXIMUM VALUE OF UNITY FOR PLOT  ********)
   M1:=0.001;M2:=0.001;M3:=0.001;
     for N:=1 to 64 do begin
       if abs(X[N])>M1 then M1:=abs(X[N]);
       if abs(MAG[N])>M2 then M2:=abs(MAG[N]);
       if abs(PHASE[N])>M3 then M3:=abs(PHASE[N]);end;
     for N:=1 to 64 do begin
       X[N]:=X[N]/M1;MAG[N]:=MAG[N]/M2;PHASE[N]:=PHASE[N]/M3;end;
(********  PLOT SIGNAL, SPECTRAL MAGNITUDE, AND PHASE  *********)
  graphmode;
    for N:=1 to 64 do begin
      draw (5*(N-1),50,5*(N-1),round(50-X[N]*25),1);
      draw (5*(N-1),120,5*(N-1),round(120-MAG[N]*30),1);
      draw (5*(N-1),160,5*(N-1),round(160-PHASE[N]*20),1);end;
  P:=P+1;if P=2 then goto 1;
end.
(***************************************************************)