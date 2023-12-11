(********  PROGRAM NO.7   DISCRETE-TIME FOURIER SERIES  ********)
(**************  FOR SIGNAL WITH 7 SAMPLE VALUES  **************)
program DSP07;
var X: array[1..7] of real;
var AR: array[1..7] of real;
var AI: array[1..7] of real;
var N,K: integer;
begin
  for N:=1 to 7 do
    begin
      AR[N]:=0; AI[N]:=0;
    end;
  X[1]:=2; X[2]:=1; X[3]:=-2; X[4]:=3;
  X[5]:=-1; X[6]:=-1; X[7]:=1;
  for K:=1 to 7 do
    begin
      for N:=1 to 7 do
        begin
          AR[K]:=AR[K]+(1/7)*X[N]*cos(2*3.141593*(K-1)*(N-1)/7);
          AI[K]:=AI[K]-(1/7)*X[N]*sin(2*3.141593*(K-1)*(N-1)/7);
        end;
    end;
  for N:=1 to 7 do
    begin
      writeln(AR[N],AI[N]);
    end;
end.
(***************************************************************)