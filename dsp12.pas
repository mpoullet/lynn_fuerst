(****  PROGRAM NO.12   F-RESPONSE OF MOVING-AVERAGE FILTER  ****)
program DSP12;
uses graph3;
var J,W,H: real;
var N,M,K: integer;
begin
  writeln('Enter value of M');
  readln(M);
  J:=1/(2*M+1);
  graphmode;
  for N:=1 to 320 do
    begin
      W:=3.141593*(N-1)/320;H:=J;
        for K:=1 to M do
          begin
            H:=H+2*J*cos(K*W);
          end;
        draw(N,100,N,round(100-50*abs(H)),1);
    end;
end.
(***************************************************************)