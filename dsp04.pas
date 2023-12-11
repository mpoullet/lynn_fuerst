(******  PROGRAM NO.4  IMPULSE RESPONSE OF LTI PROCESSOR  ******)
program DSP04;
uses graph3;
var H: array[1..120] of real;
var X: array[1..120] of real;
var N: integer;
var A1,A2,A3,B0,B1,B2,M: real;
begin
(***************  LOAD IMPULSE INTO INPUT ARRAY  ***************)
  for N:=1 to 120 do
    begin
      X[N]:=0;H[N]:=0
    end;
  X[10]:=1.0;
  writeln('ENTER 3 RECURSIVE MULTIPLIERS');
  readln(A1,A2,A3);
  writeln('ENTER 3 NONRECURSIVE MULTIPLIERS');
  readln(B0,B1,B2);
(*****  FIND IMPULSE RESPONSE, TAKING N=10 AS TIME ORIGIN ******)
  for N:=10 TO 120 do
    begin
      H[N]:= A1*H[N-1]+A2*H[N-2]+A3*H[N-3]+B0*X[N]+B1*X[N-1]
                                                      +B2*X[N-2];
    end;
(*********  NORMALISE H[N] TO A MAXIMUM VALUE OF UNITY  ********)
  M:=0;
  for N:=1 to 120 do
    begin
      if abs(H[N])>M then M:=abs(H[N]);
    end;
  for N:=1 TO 120 do
    begin
      H[N]:=H[N]/M;
    end;
(***********  PLOT HORIZONTAL AXIS AND IMPULSE INPUT  **********)
  graphmode;
  draw(0,50,300,50,1);
  for N:=1 to 100 do
    begin
      draw(3*N,50,3*N,round(50-X[N+9]*25),1);
    end;
(*********  PLOT HORIZONTAL AXIS AND IMPULSE RESPONSE  *********)
  draw (0,120,300,120,1);
  for N:=1 to 100 do
    begin
      draw(3*N,120,3*N,round(120-H[N+9]*60),1);
    end;
end.
(***************************************************************)