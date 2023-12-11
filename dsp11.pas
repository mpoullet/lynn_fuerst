(****  PROGRAM NO.11  CHARACTERISTICS OF 2ND-ORDER SYSTEMS  ****)
program DSP11;
uses graph3;
var I: array[1..320] of real;
var F: array[1..320] of real;
var R,THETA,T,A,B,GAIN,C,D,W,M: real;
var N: integer;
(***  I=IMPULSE RESPONSE, F=FREQUENCY RESPONSE (MAGNITUDE)  ****)
begin
  writeln('ENTER RADIUS, ANGLE (DEGREES) OF Z-PLANE POLES ');
  readln(R,THETA);
  T:=THETA*3.141593/180;
(******  LOAD IMPULSE RESPONSE, STARTING AT LOCATION I(2)  *****)
  I[1]:=0; I[2]:=1;
  for N:=3 TO 320 do
    begin
      I[N]:=2*R*cos(T)*I[N-1]-R*R*I[N-2];
    end;
(*******  NORMALISE TO PEAK VALUE OF UNITY, THEN  PLOT  ********)
  M:=0;
  for N:=1 to 320 do
    begin
      if abs(I[N])>M then M:=abs(I[N]);
    end;
  for N:=1 to 320 do
    begin
      I[N]:=I[N]/M;
    end;
  graphmode;
  for N:=1 to 320 do
    begin
      draw(N,70,N,round(70-I[N]*30),1);
    end;
(*********************  ESTIMATE PEAK GAIN  ********************)
  A:=1-2*R*cos(T)*cos(T)+R*R*cos(2*T);
  B:=2*R*cos(T)*sin(T)-R*R*sin(2*T);
  GAIN:=1/sqrt(A*A+B*B);
(******  FIND FREQUENCY RESPONSE (NORMALISED), THEN PLOT  ******)
  for N:=1 to 320 do
    begin
      W:=(N-1)*3.141593/320;
      C:=1-2*R*cos(T)*cos(W)+R*R*cos(2*W);
      D:=2*R*cos(T)*sin(W)-R*R*sin(2*W);
      F[N]:=1/(sqrt(C*C+D*D)*GAIN);
    end;
  for N:=1 to 320 do
    begin
      draw(N,170,N,round(170-F[N]*60),1);
    end;
end.
(***************************************************************)