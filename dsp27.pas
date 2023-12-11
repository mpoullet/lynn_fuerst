(*******  PROGRAM NO.27  ESTIMATES OF MEAN AND VARIANCE  *******)
program DSP27;
uses graph3;
var X: array[1..320] of real;
var M: array[1..16] of real;
var V: array[1..16] of real;
var J,K,N: integer;
var A,B,C,RM,RV,Z: real;
begin
  randomize;
  graphmode;
    for N:=1 to 16 do begin
    M[N]:=0;V[N]:=0;end;
(*******  FORM 320 VALUES OF GAUSSIAN SEQUENCE, AND PLOT  ******)
  for N:=1 to 320 do begin
    C:=0;for K:=1 to 12 do begin
         C:=C+random-0.5;end;
    X[N]:=C;draw(N,50,N,round(50-X[N]*10),1);
  end;
(************  ESTIMATE SAMPLE MEANS AND VARIANCES  ************)
  for J:=1 to 16 do begin
    for K:=1 to 20 do begin
      N:=K+20*(J-1)-1;M[J]:=M[J]+X[N]/20;
      V[J]:=V[J]+X[N]*X[N]/20;end;
  draw(N,100,N,round(100-M[J]*50),1);
  draw(N,160,N,round(160-V[J]*20),1);end;
    writeln('INPUT DUMMY VARIABLE');readln(Z);clearscreen;
(*************  ESTIMATE RUNNING MEAN AND VARIANCE  ************)
  A:=0;B:=0;
    for N:=1 to 320 do begin
    A:=A+X[N];RM:=A/N;B:=B+X[N]*X[N];RV:=B/N;
    draw(N,80,N,round(80-RM*50),1);
    draw(N,150,N,round(150-RV*20),1);end;
end.
(***************************************************************)

