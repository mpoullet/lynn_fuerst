(****  PROGRAM NO.9  FREQUENCY RESPONSE OF BANDPASS FILTER *****)
program DSP09;
uses graph3;
var N: integer;
var W,A,B,MAG,PHASE: real;
begin
  graphmode;
  for N:=1 to 320 do
    begin
      W:=3.141593*(N-1)/320;
      A:=1-1.5*cos(W)+0.85*cos(2*W);
      B:=1.5*sin(W)-0.85*sin(2*W);
      MAG:=1/sqrt(A*A+B*B);
      PHASE:=arctan(B/A);
      draw(N,100,N,round(100-5*MAG),1);
      draw(N,160,N,round(160-8*PHASE),1);
    end;
end.
(***************************************************************)