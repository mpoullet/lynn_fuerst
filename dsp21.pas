(************  PROGRAM NO.21    POLES AND ZEROS OF  ************)
(*********  BUTTERWORTH AND CHEBYSHEV DIGITAL FILTERS  *********)
program DSP21;
var PR: array[1..50] of real;
var PI: array[1..50] of real;
var FF,FT,N,K,J,IR,M,M1,N1,N2,ST: integer;
var F1,D,W1,C1,C2,B1,B2,E,X,A,Y,B: real;
var T,C3,C4,C5,R,I,B3,F2,F3,F4,F5,FR,FI,GR,AR: real;
var GI,AI,SR,SI,H1,H2,P1R,P2R,P1I,P2I,TH: real;
label 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16;
begin
    for K:=1 to 50 do begin PR[K]:=0;PI[K]:=0;end;
    writeln('CHOOSE FILTER FAMILY: 1=BUTTERWORTH; 2=CHEBYSHEV');
    readln(FF);
    writeln('CHOOSE FILTER TYPE:');
    writeln('  1=LOWPASS; 2=HIGHPASS; 3=BANDPASS'); readln(FT);
    writeln('FILTER ORDER');readln(N);if FT=3 then begin
      N:=trunc(N/2);goto 1 end;
    writeln('CUT-OFF FREQUENCY (DEGREES)');readln(F1);ST:=2;
      if FT>1 then F1:=180-F1;goto 2;
 1: writeln('LOWER,UPPER CUT-OFF FREQUENCIES (DEGREES)');
    readln(F2,F3);F1:=F3-F2;ST:=1;
 2: if FF=2 then begin writeln('PASSBAND RIPPLE (FRACTION)');
      readln(D) end;
(***********  FIND BUTTERWORTH/CHEBYSHEV PARAMETERS  ***********)
    IR:=N mod 2;N1:=N+IR;N2:=trunc((3*N+IR)/2-1);
    W1:=3.141593*F1/360;C1:=sin(W1)/cos(W1);B1:=2*C1;C2:=C1*C1;
    B2:=0.25*B1*B1; if FF=1 then goto 3;
    E:=1/sqrt(1/((1-D)*(1-D))-1);
    X:=exp(1/N*ln(sqrt(E*E+1)+E));
    Y:=1/X;A:=0.5*(X-Y);B:=0.5*(X+Y);
(******  FIND REAL AND IMAGINARY PARTS OF LOW-PASS POLES  ******)
 3: for K:=N1 to N2 do begin
      T:=3.141593*(2*K+1-IR)/(2*N);if FF=1 then goto 4;
      C3:=A*C1*COS(T);C4:=B*C1*SIN(T);C5:=(1-C3)*(1-C3)+C4*C4;
      R:=2*(1-C3)/C5-1;I:=2*C4/C5; goto 5;
 4:   B3:=1-B1*cos(T)+B2;R:=(1-B2)/B3;I:=B1*sin(T)/B3;
 5:   M:=(N2-K)*2+1;
      PR[M+IR]:=R;PI[M+IR]:=I;PR[M+IR+1]:=R;PI[M+IR+1]:=-I;end;
    if IR=0 then goto 8;
      if FF=1 then goto 6;
        R:=2/(1+A*C1)-1;goto 7;
 6:     R:=(1-B2)/(1+B1+B2);
 7:     PR[1]:=R;PI[1]:=0;
 8:       if FT=3 then goto 10;
(*************  PRINT OUT Z-PLANE ZERO LOCATIONS  **************)
    if FT>1 then goto 9;
    writeln('REAL ZERO, OF ORDER ',N,', AT Z=-1');goto 13;
 9: writeln('REAL ZERO, OF ORDER ',N,', AT Z=1');
    for M:=1 to N do begin
      PR[M]:=-PR[M];end;goto 13;
10: writeln('REAL ZEROS, OF ORDER ',N,', AT Z=1 AND AT Z=-1');
(***********  LOW-PASS TO BANDPASS TRANSFORMATION  *************)
    F4:=F2*3.141593/360;F5:=F3*3.141593/360;
    A:=cos(F4+F5)/cos(F5-F4);
      for M1:=0 to 24 do begin M:=1+2*M1;
        AR:=PR[M];AI:=PI[M];
          if abs(AI)<0.0001 then goto 11;
            FR:=A*0.5*(1+AR);FI:=A*0.5*AI;
            GR:=FR*FR-FI*FI-AR;GI:=2*FR*FI-AI;
            SR:=sqrt(abs(GR+sqrt(GR*GR+GI*GI))/2);SI:=GI/(2*SR);
            P1R:=FR+SR;P1I:=FI+SI;P2R:=FR-SR;P2I:=FI-SI;goto 12;
11: H1:=A*(1+AR)/2;H2:=H1*H1-AR;
      if H2>0 then begin P1R:=H1+sqrt(H2);P2R:=H1-sqrt(H2);
       P1I:=0;P2I:=0;goto 12 end;
    P1R:=H1;P2R:=H1;P1I:=sqrt(abs(H2));P2I:=-P1I;
12: PR[M]:=P1R;PR[M+1]:=P2R;PI[M]:=P1I;PI[M+1]:=P2I;end;
(**************  PRINT OUT Z-PLANE POLE LOCATIONS  *************)
13: writeln('RADII, ANGLES OF Z-PLANE POLES:');
    writeln('       R','              THETA');
      for J:=1 to N do begin
        if ST=1 then goto 14;
        if J mod ST=0 then goto 16;
14: M:=J;if IR=0 then goto 15;
         if J=2 then M:=N+1;
15: R:=sqrt(PR[M]*PR[M]+PI[M]*PI[M]);
    TH:=arctan(abs(PI[M])/abs(PR[M]))*180/3.141593;
      if PR[M]<0 then TH:=180-TH;writeln(R,TH);
16:   end;
end.
(***************************************************************)