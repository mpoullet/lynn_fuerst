(*****  PROGRAM NO.2    SAMPLED EXPONENTIALS AND SINUSOIDS  ****)
program DSP02;
uses graph3;
var X: array[1..100] of real;
var N: integer;
var B,W: real;
begin
  writeln('Value of beta-zero?');
  readln(B);
  writeln('Value of omega?');
  readln(W);
    begin
     for N:=1 to 100 do
       begin
         X[N]:=exp(B*N)*cos(W*N);
       end;
(**************  DRAW AXES, THEN SIGNAL SAMPLES  ***************)
     graphmode;
     draw(1,100,300,100,1);
     draw(1,0,1,200,1);
     for N:=1 to 100 do
       begin
         draw(3*N,100,3*N,round(100-X[N]*30),1);
       end;
    end;
end.
(***************************************************************)