(************  PROGRAM NO.5    DIGITAL CONVOLUTION  ************)
program DSP05;
uses graph3;
var X: array[1..320] of real;
var Y: array[1..320] of real;
var H: array[1..60]  of real;
var N,K: integer;
var MX,MY: real;
(***********  CLEAR ARRAYS AND DEFINE INPUT SIGNAL  ************)
begin
  for N:=1 to 320 do
    begin
      X[N]:=0; Y[N]:=0;
    end;
  for N:=60 to 320 do
    begin
      X[N]:=sin(2*3.141593*N/60)+sin(2*3.141593*N/10);
    end;
(*******  DEFINE IMPULSE RESPONSE (MAX NO. OF TERMS=60)  *******)
  for N:=1 to 60 do
    begin
      H[N]:=0;
    end;
  for N:=1 TO 10 do
    begin
      H[N]:=0.1;
    end;
(************  CONVOLVE INPUT AND IMPULSE RESPONSE  ************)
  for N:=61 to 320 do
    begin
      for K:=1 to 60 do
        begin
          Y[N]:=Y[N]+H[K]*X[N-K];
        end;
    end;
(******  NORMALISE SIGNALS TO MAX VALUE OF UNITY FOR PLOT ******)
  MX:=0;
  MY:=0;
  for N:=1 to 320 do
    begin
      if abs(X[N])>MX then MX:=abs(X[N]);
      if abs(Y[N])>MY then MY:=abs(Y[N]);
    end;
  for N:=1 to 320 do
    begin
      X[N]:=X[N]/MX;Y[N]:=Y[N]/MY;
    end;
(***********  PLOT HORIZONTAL AXIS AND INPUT SIGNAL  ***********)
  graphmode;
  draw(0,50,320,50,1);
  for N:=1 to 320 do
    begin
      draw(N,50,N,round(50-X[N]*30),1);
    end;
(***********  PLOT HORIZONTAL AXIS AND OUTPUT SIGNAL  **********)
  draw(0,150,320,150,1);
  for n:=1 to 320 do
    begin
      draw(N,150,N,round(150-Y[N]*30),1);
    end;
end.
(***************************************************************)