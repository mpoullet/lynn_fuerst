(**********  PROGRAM NO.1    DIGITAL BANDPASS FILTER  **********)
program DSP01;
uses graph3;
var X: array[1..320] of real;
var Y: array[1..320] of real;
var N: integer;
(*******  GENERATE INPUT SIGNAL, AND LOAD INTO ARRAY X  ********)
begin
  for N:=1 to 320 do
    begin
      X[N]:=sin(3.141593*N*(0.05+(0.0005*N)));
    end;
(********  ESTIMATE OUTPUT SIGNAL OF RECURSIVE FILTER  *********)
  Y[1]:=0;
  Y[2]:=0;
    for N:=3 to 320 do
      begin
        Y[N]:=1.5*Y[N-1]-0.85*Y[N-2]+X[N];
      end;
(**********  PLOT INPUT AND OUTPUT SIGNALS ON SCREEN  **********)
  graphmode;
    for N:=1 to 320 do
      begin
        draw(N,50,N,round(50-X[N]*25),1);
        draw(N,150,N,round(150-Y[N]*4),1);
      end;
end.
(***************************************************************)