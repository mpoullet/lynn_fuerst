(********  PROGRAM NO.8   DISCRETE-TIME FOURIER SERIES  ********)
(*****  64 REAL SAMPLE VALUES, SPECTRAL MAGNITUDE & PHASE  *****)
program DSP08;
uses graph3;
var X: array[1..64] of real;
var AR: array[1..64] of real;
var AI: array[1..64] of real;
var MAG: array[1..64] of real;
var PHASE: array[1..64] of real;
var N,K: integer;
var B,M1,M2,M3: real;
begin
  for N:=1 to 64 do
    begin
      AR[N]:=0;AI[N]:=0;
      B:=2*3.141593*(N-1);
      X[N]:=sin(B/64)+cos(B/16)+0.6*cos(B/8)+0.5*sin(B/4);
    end;
  for K:=1 to 64 do
    begin
      for N:=1 to 64 do
        begin
         AR[K]:=AR[K]+(1/64)*X[N]*cos(2*3.141593*(K-1)*(N-1)/64);
         AI[K]:=AI[K]-(1/64)*X[N]*sin(2*3.141593*(K-1)*(N-1)/64);
        end;
    end;
(***********  CONVERT TO SPECTRAL MAGNITUDE & PHASE  ***********)
  for K:=1 to 64 do
    begin
      if abs(AI[K])<0.001 then AI[K]:=0;
      if abs(AR[K])<0.00001 then AR[K]:=0.00001;
      MAG[K]:=sqrt(AR[K]*AR[K]+AI[K]*AI[K]);
      PHASE[K]:=arctan(AI[K]/AR[K]);
    end;
(*******  NORMALISE TO MAXIMUM VALUE OF UNITY FOR PLOT  ********)
  M1:=0.001;M2:=0.001;M3:=0.001;
    for N:=1 to 64 do
      begin
        if abs(X[N])>M1 then M1:=abs(X[N]);
        if abs(MAG[N])>M2 then M2:=abs(MAG[N]);
        if abs(PHASE[N])>M3 then M3:=abs(PHASE[N]);
      end;
  for N:=1 to 64 do
    begin
      X[N]:=X[N]/M1;MAG[N]:=MAG[N]/M2;
      PHASE[N]:=PHASE[N]/M3;
    end;
(********  PLOT SIGNAL, SPECTRAL MAGNITUDE, AND PHASE  *********)
  graphmode;
  for N:=1 to 64 do
    begin
      draw(5*(N-1),50,5*(N-1),round(50-X[N]*25),1);
      draw(5*(N-1),120,5*(N-1),round(120-MAG[N]*30),1);
      draw(5*(N-1),160,5*(N-1),round(160-PHASE[N]*20),1);
    end;
end.
(***************************************************************)