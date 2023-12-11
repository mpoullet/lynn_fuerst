(*******  PROGRAM NO.6     START-UP AND STOP TRANSIENTS  *******)
program DSP06;
uses graph3;
var X: array[1..320] of real;
var Y: array[1..320] of real;
var N: integer;
var MX,MY: real;
(********************  DEFINE INPUT SIGNAL  ********************)
begin
  for N:=1 to 320 do
    begin
      X[N]:=0; Y[N]:=0;
    end;
  for N:=20 to 200 do
    begin
      X[N]:=cos(2*3.141593*N/20);
    end;
(***********  ESTIMATE OUTPUT FROM BANDSTOP FILTER  ************)
  for N:=3 TO 320 do
    begin
      Y[N]:=1.8523*Y[N-1]-0.94833*Y[N-2]+X[N]-1.9021*X[N-1]
                                                         +X[N-2];
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
      draw(N,50,N,round(50-X[N]*35),1);
    end;
(**********  PLOT HORIZONTAL AXIS AND OUTPUT SIGNAL  ***********)
  draw(0,150,320,150,1);
  for N:=1to 320 do
    begin
      draw(N,150,N,round(150-Y[N]*35),1);
    end;
end.
(***************************************************************)