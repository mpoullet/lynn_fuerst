(***********************  PROGRAM NO.16  ***********************)
(*****  SPECTRAL PROPERTIES OF VON HANN & HAMMING WINDOWS ******)
program DSP16;
uses graph3;
var SEE: array[1..200] of real;
var W: array[1..320] of real;
var A,B,C,DB,FREQ,PEAK: real;
var X,K,N,M: integer;
label 1,2;
begin
  writeln('SELECT WINDOW TYPE: 1= VON HANN; 2= HAMMING');
  readln(X);
  writeln('ENTER VALUE OF M'); readln(M);
(*****  LOAD ONE HALF OF WINDOW (EXCLUDING CENTRAL VALUE)  *****)
(***********************  INTO ARRAY SEE  **********************)
  if (X)=1  then goto 1;
      A:=0.54;B:=0.46;C:=M; goto 2;
    1: A:=0.5;B:=0.5;C:=M+1;
    2: for K:=1 to M do
         begin
           SEE[K]:=A+B*cos(K*3.141593/C);
         end;
(**************  DRAW RECTANGULAR GRID FOR PLOT  ***************)
  graphmode;
  for K:=0 to 5 do
    begin
      draw(0,30+20*K,320,30+20*K,1);
      draw(64*K,30,64*K,130,1)
    end;
  draw(319,30,319,130,1);
(*********************  ESTIMATE SPECTRUM  *********************)
  for N:=1 to 320 do
    begin
      FREQ:=3.141593*(N-1)/320;W[N]:=1;
        for K:=1 to M do
          begin
            W[N]:=W[N]+2*SEE[K]*cos(K*FREQ);
          end;
(***  NORMALISE TO PEAK VALUE, CONVERT TO DECIBELS, AND PLOT  **)
            if (N)=1 then PEAK:=W[N];
            W[N]:=W[N]/PEAK;
            DB:=20*ln(abs(W[N]))*0.4343;
            if (DB)<-50 then DB:=-50;
            draw(N,130,N,round(30-2*DB),1);
    end;
end.
(***************************************************************)