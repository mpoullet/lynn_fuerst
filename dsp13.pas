(***********************  PROGRAM NO.13  ***********************)
(***  NONRECURSIVE FILTER DESIGN BY FOURIER TRANSFORM METHOD  **)
(********  IMPULSE RESPONSE TRUNCATED TO (2M+1) TERMS  *********)
program DSP13;
uses graph3;
var H: array[1..320] of real;
var A,B,W,W0,W1,H0,HF: real;
var M,N,K,X: integer;
begin
  writeln('ENTER CENTER-FREQUENCY (IN DEGREES)');readln(A);
  W0:=A*3.141593/180;
  writeln('ENTER FILTER BANDWIDTH (IN DEGREES)');readln(B);
  W1:=B*0.5*3.141593/180;
  writeln('ENTER VALUE OF M');readln(M);
  writeln('IMPULSE RESPONSE VALUES H(0) TO H(M) ARE');
  H0:=W1/3.141593;writeln(H0);
  for N:=1 to M do
    begin
      H[N]:=(1/(N*3.141593))*sin(N*W1)*cos(N*W0);
      writeln(H[N]);
    end;
  writeln('ENTER ANY INTEGER TO BEGIN F-RESPONSE PLOT');
  readln(X);
  graphmode;
  for N:=1 to 320 do
    begin
      W:=3.141593*(N-1)/320;HF:=H0;
        for K:=1 to M do
          begin
            HF:=HF+2*H[K]*cos(K*W);
          end;
        draw(N,100,N,round(100-70*abs(HF)),1);
    end;
end.
(***************************************************************)