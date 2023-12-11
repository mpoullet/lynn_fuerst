(*********  PROGRAM NO.26   PROBABILITY MASS FUNCTIONS  ********)
program DSP26;
uses graph3;
var X: array[0..300] of real;
var Y: array[0..300] of real;
var K,N,B,D: integer;
var C: real;
(********************  UNIFORM DISTRIBUTION  *******************)
begin
  for K:=0 to 300 do begin
    X[K]:=0;Y[K]:=0;end;
  randomize;graphmode;
    for K:=1 to 3000 do begin
      B:=trunc(random*300);X[B]:=X[B]+1;
      draw(B,50,B,round(50-X[B]),1);end;
(************  GAUSSIAN DISTRIBUTION (APPROXIMATE)  ************)
  for K:=1 to 3000 do begin
    C:=0;for N:=1 to 30 do begin
           C:=C+random;end;
    D:=trunc(C*10);Y[D]:=Y[D]+1;
    draw(D,180,D,round(180-Y[D]),1);end;
end.
(***************************************************************)
