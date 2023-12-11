(*******  PROGRAM NO.3   AMBIGUITY IN DIGITAL SINUSOIDS  *******)
program DSP03;
uses graph3;
var X: array[1..320] of real;
var N,M,K: integer;
begin
(****  GENERATE SIGNAL WITH TEN EQUAL FREQUENCY INCREMENTS  ****)
  for M:=0 to 9 do
    begin
      for K:=1 to 32 do
        begin
          N:=K+32*M;
          X[N]:=cos(N*2*3.141593*M/8);
        end;
    end;
(**************************  PLOT  *****************************)
  graphmode;
  for N:=1 to 320 do
    begin
      draw(N,50,N,round(50-X[N]*25),1);
    end;
end.
(***************************************************************)

