(***********  PROGRAM NO.10     INVERSE Z-TRANSFORM  ***********)
program DSP10;
uses graph3;
var X: array[1..320] of real;
var Y: array[1..320] of real;
var N: integer;
begin
  for N:=1 to 320 do
    begin
      X[N]:=0;Y[N]:=0;
    end;
  X[5]:=1;
  graphmode;
  for N:=5 to 320 do
    begin
      Y[N]:=-0.54048*Y[N-1]+0.62519*Y[N-2]+0.66354*Y[N-3]
            -0.60317*Y[N-4]-0.69341*Y[N-5]
            +X[N]-X[N-1]+X[N-2]-X[N-3];
      draw(N,100,N,round(100-20*Y[N]),1);
    end;
end.
(***************************************************************)

