(*********  PROGRAM NO.20    FILTER MAGNITUDE RESPONSE *********)
(***********  FROM Z-PLANE POLE AND ZERO LOCATIONS  ************)
program DSP20;
uses graph3;
var RP: array[1..20,1..2] of real;
var RZ: array[1..20,1..2] of real;
var CP: array[1..20,1..2] of real;
var CZ: array[1..20,1..2] of real;
var H: array[1..320] of real;
var A,B,W,C1,C2,S1,S2,D,R,T,E,MAX,DB,BASE,EX: real;
var NRP,NRZ,N,NCP,NCZ,K: integer;
label 1,2,3,4,5,6,7,8;
begin
    writeln('NO. OF SEPARATE REAL POLES'); readln(NRP);
      if NRP=0 then goto 1;
    writeln('ENTER VALUE, ORDER, OF EACH IN TURN');
    writeln('   FOLLOWED BY <RETURN>');
      for N:=1 to NRP do begin
        readln(RP[N,1],RP[N,2]); end;
 1: writeln('NO. OF SEPARATE REAL ZEROS'); readln(NRZ);
      if NRZ=0 then goto 2;
    writeln('ENTER VALUE, ORDER, OF EACH IN TURN');
    writeln('   FOLLOWED BY <RETURN>');
      for N:=1 to NRZ do begin
        readln(RZ[N,1],RZ[N,2]); end;
 2: writeln('NO. OF COMPLEX-CONJUGATE POLE PAIRS'); readln(NCP);
      if NCP=0 then goto 3;
    writeln('ENTER RADIUS, ANGLE (DEGREES), OF EACH');
    writeln('   IN TURN, FOLLOWED BY <RETURN>');
      for N:=1 to NCP do begin
        readln(CP[N,1],CP[N,2]); end;
 3: writeln('NO. OF COMPLEX-CONJUGATE ZERO PAIRS'); readln(NCZ);
      if NCZ=0 then goto 4;
    writeln('ENTER RADIUS, ANGLE (DEGREES), OF EACH');
    writeln('   IN TURN, FOLLOWED BY <RETURN>');
      for N:=1 to NCZ do begin
        readln(CZ[N,1],CZ[N,2]);end;
(************  COMPUTE FREQUENCY RESPONSE MAGNITUDE  ***********)
 4: for N:=1 to 320 do begin
      W:=3.141593*(N-1)/320;
      C1:=cos(W);C2:=cos(2*W);S1:=sin(W);S2:=sin(2*W);H[N]:=1;
        if NRP=0 then goto 5;
          for K:=1 to NRP do begin
            A:=RP[K,1];B:=RP[K,2];BASE:=1-2*A*C1+A*A;EX:=B/2;
            H[N]:=H[N]/(exp(EX*ln(BASE))); end;
 5:     if NRZ=0 then goto 6;
          for K:=1 to NRZ do begin
            A:=RZ[K,1];B:=RZ[K,2];BASE:=1-2*A*C1+A*A;EX:=B/2;
            H[N]:=H[N]*(exp(EX*ln(BASE))); end;
 6:      if NCP=0 then goto 7;
          for K:=1 to NCP do begin
            R:=CP[K,1];T:=CP[K,2]*3.141593/180;
            D:=C2-2*R*cos(T)*C1+R*R;E:=S2-2*R*cos(T)*S1;
            H[N]:=H[N]/(exp(0.5*ln(D*D+E*E))); end;
 7:      if NCZ=0 then goto 8;
          for K:=1 to NCZ do begin
            R:=CZ[K,1];T:=CZ[K,2]*3.141593/180;
            D:=C2-2*R*cos(T)*C1+R*R;E:=S2-2*R*cos(T)*S1;
            H[N]:=H[N]*(exp(0.5*ln(D*D+E*E))); end;
 8: end;
(*************  FIND MAXIMUM VALUE AND PRINT OUT  **************)
  graphmode;
  MAX:=0;
  for N:=1 to 320 do begin
    if abs(H[N])>MAX then MAX:=abs(H[N]); end;
  writeln('MAXIMUM GAIN=',20*ln(MAX)*0.4343,' dB');
(***************  DRAW RECTANGULAR GRID FOR PLOT  **************)
  for K:=0 to 5 do begin
   draw(0,30+20*K,320,30+20*K,1);
   draw(64*K,30,64*K,130,1);end;  draw(319,30,319,130,1);
(****  NORMALISE RESPONSE TO UNITY, CONVERT TO DB, AND PLOT  ***)
  for N:=1 to 320 do begin
    if abs(H[N])<0.000001 then H[N]:=0.000001;
    DB:=20*ln(abs(H[N])/MAX)*0.4343;if DB<-50 then DB:=-50;
    draw(N,130,N,round(30-2*DB),1); end;
end.
(***************************************************************)